#include "gpio.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QThread>
#include <QProcess>
#include <QVariant>
#ifdef Q_WS_QWS
#include <linux/mcc_config.h>
#include <linux/mcc_common.h>
#include <linux/mcc_linux.h>
extern "C" {
#include <mcc_api.h>
}
#include <stdint.h>


#define MCC_NODE_A5 1
#define MCC_NODE_M4 2

#define SERVO_STATE_INVALID     (0)
#define SERVO_STATE_CW          (1)
#define SERVO_STATE_CCW         (2)
#define SERVO_STATE_END         (3)


MCC_ENDPOINT endpoint_a5 = {0,0,MCC_NODE_A5};
MCC_ENDPOINT endpoint_m4 = {1,0,MCC_NODE_M4};

// GPIO 38 => SO-DIMM 63 => Viola X9, Pin 18
#define PWM_GPIO    "38"


int send_msg(msg_t *msg)
{
    int retval;

    retval = mcc_send(&endpoint_m4, msg, sizeof(msg_t), 0xffffffff);
    if(retval)
        qDebug("mcc_send failed, result = 0x%x", retval);

    return retval;
}

int receive_msg(msg_t *msg, int timeout)
{
    int retval, num_of_received_bytes;

    retval = mcc_recv_copy(&endpoint_a5, msg, sizeof(msg_t), (MCC_MEM_SIZE *)&num_of_received_bytes, timeout);
    if(retval)
        qDebug("mcc_recv_copy failed, result = 0x%x",  retval);
    return retval;
}

int GpioOnOff::initmcc()
{
    MCC_INFO_STRUCT info_data;
    int retval = 0;
    uint32_t node_num = endpoint_a5.node;

    retval = mcc_initialize(node_num);
    if(retval)
        return retval;

    retval = mcc_get_info(node_num, &info_data);
    if(retval)
        return retval;

    qDebug("mcc version: %s", info_data.version_string);

    return 0;
}
#else

int GpioOnOff::initmcc()
{
    qDebug("no mcc");

    return 0;
}
#endif


void GpioOnOff::usleep(long iSleepTime)
{
    QThread::usleep(iSleepTime);
}

void GpioOnOff::msleep(long iSleepTime)
{
    QThread::msleep(iSleepTime);
}

void GpioOnOff::sleep(long iSleepTime)
{
    QThread::sleep(iSleepTime);
}

void GpioOnOff::schedprio(int val)
{
    struct sched_param param;
    param.sched_priority = 80;
    if(sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        qWarning() << "Schedule setzten";
        return;
    }
}

void GpioOnOff::mccsendstart()
{
    int retval;

    msg.data = SERVO_STATE_CW;
    retval = send_msg(&msg);
    if (retval)
        qDebug() << "Error on mcc send start";
}


void GpioOnOff::run()
{
    int retval;
    qDebug("Servo GPIO-PWM thread");

    qDebug("Loading eCos firmware...");
    QProcess processMqx;
    processMqx.start("mqxboot /home/root/servo.bin 0x8f000400 0x0f000411");
    if (!processMqx.waitForFinished())
        qWarning() << "mqxboot failed";

    retval = initmcc();
    if (retval) {
        qDebug("Error during mcc_get_info, result = %d", retval);
    }

    /* Set realtime priority for the GPIO PWM thread */
    schedprio(80);

    QFile gpio_export_file("/sys/class/gpio/export");
    gpio_export_file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&gpio_export_file);
    out << PWM_GPIO;
    gpio_export_file.close();

    QFile gpio_direction("/sys/class/gpio/gpio" PWM_GPIO "/direction");
    gpio_direction.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outGpio_Direction(&gpio_direction);
    outGpio_Direction << "out";
    gpio_direction.close();


    QFile gpio_value("/sys/class/gpio/gpio" PWM_GPIO "/value");
    gpio_value.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream st_gpio_value(&gpio_value);
    st_gpio_value << "1";

    int deg = 0;
    int count = 0;

    int usperdeg = 11;
    int period = 20000;

    int minduty = 1000;
    int maxduty = 2000;
    int duty = minduty;


    servo_state = SERVO_STATE_END;

    while(1)
    {
        count++;

        duty = minduty + deg * usperdeg;
        if (duty > maxduty)
            duty = maxduty;

        if (servo_state != SERVO_STATE_END)
        {
            st_gpio_value << "1";
            st_gpio_value.flush();
            usleep(duty);
            st_gpio_value << "0";
            st_gpio_value.flush();
            usleep(period-duty);
        }
        else
            usleep(period);


        switch (servo_state)
        {
        case SERVO_STATE_CW:
            /* Next step every 200ms */
            if (count % 20)
                break;

            deg += 5;
            if (deg >= 90) {
                count = 0;
                servo_state = SERVO_STATE_CCW;
            }

            break;

        case SERVO_STATE_CCW:
            deg = 0;
            /* Wait for 0.2 seconds */
            if (count > 10)
                servo_state = SERVO_STATE_END;

            break;
        case SERVO_STATE_END:
            /* Wait for two seconds */
            if (count > 100)
            {
                mccsendstart();
                servo_state = SERVO_STATE_CW;
            }
            break;
        default:
            /* Auto restart... */
            servo_state = SERVO_STATE_END;
            break;
        }
    }
}

#include "gpio.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QThread>
#include <QProcess>
#include <QVariant>


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




void GpioOnOff::run()
{
    qDebug("Loading firmware...");
    QProcess processMqx;
    processMqx.start("mqxboot /home/root/plotter.bin 0x8f000400 0x0f000411");
    processMqx.waitForFinished();


    qDebug() << "GPIO1";
    QFile file("/sys/class/gpio/export");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "66";
    file.close();
    qDebug() << "GPIO2";

    QFile gpio49_direction("/sys/class/gpio/gpio66/direction");
    gpio49_direction.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outGpio_Direction(&gpio49_direction);
    outGpio_Direction << "out";
    gpio49_direction.close();

    qDebug() << "GPIO3";

    QFile gpio_value("/sys/class/gpio/gpio66/value");
    gpio_value.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream St_gpio_value(&gpio_value);
    St_gpio_value << "1";
    gpio_value.close();
    qDebug() << "GPIO4";

    int count = 0;
    int x = 1000;
    int total = 40000;
    int y = total - x;



    QVariant varX(x);
    QString stringX = varX.toString();
    qDebug() << "x :"+stringX;


    while(1)
    {

        y=total-x;

        //Liga
        QFile gpio_value4("/sys/class/gpio/gpio66/value");
        gpio_value4.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream St_gpio_value4(&gpio_value4);
        St_gpio_value4 << "1";
        gpio_value4.close();
        usleep(x);
        //Desliga
        QFile gpio_value5("/sys/class/gpio/gpio66/value");
        gpio_value5.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream St_gpio_value5(&gpio_value5);
        St_gpio_value5 << "0";
        gpio_value5.close();
        usleep(y);

        count++;
        if(count >=60)
        {
            count=0;
            x= x + 1000;
        }
        if(x>2000)
        {
            x=1000 ;
        }
    }
//        if(count <= periodo)
//        {
//            QFile gpio_value2("/sys/class/gpio/gpio66/value");
//            gpio_value2.open(QIODevice::WriteOnly | QIODevice::Text);
//            QTextStream St_gpio_value1(&gpio_value2);
//            St_gpio_value1 << "1";
//            gpio_value2.close();
//        }
//        else
//        {
//            QFile gpio_value3("/sys/class/gpio/gpio66/value");
//            gpio_value3.open(QIODevice::WriteOnly | QIODevice::Text);
//            QTextStream St_gpio_value3(&gpio_value3);
//            St_gpio_value3 << "0";
//            gpio_value3.close();
//        }
//        if(count >= duty)
//        {
//            count = 0;
//        }
//        else
//        {
//            count++;
//        }
//        if(change >= 1000)
//        {
//            change = 0;
//            periodo++;
//            periodo++;
//            if(periodo >= 60)
//            {
//                periodo = 10;
//                msleep(1000);
//            }
//        }
//        else
//        {
//            change++;
//        }
//        msleep(1);
//    }
//    qDebug() << "CpuLoad Ended!";
}

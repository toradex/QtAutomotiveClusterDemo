#ifndef GPIOONOFF_H
#define GPIOONOFF_H
#include <QThread>
#include <stdint.h>

typedef struct msg_s
{
   uint32_t     data;
   uint32_t     status;
} msg_t;

class GpioOnOff : public QThread
{
    Q_OBJECT
public:

    /* Is this accepted in C++? Probably not :-) */
private:
    msg_t msg, rcv_msg;
    int servo_state;

    bool end;
    int initmcc();
    void run();
    void mccsendstart();
    void schedprio(int val);
    void msleep(long iSleepTime);
    void usleep(long iSleepTime);
    void sleep(long iSleepTime);
signals:

public slots:
};

#endif // GPIOONOFF_H

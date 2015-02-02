#ifndef GPIOONOFF_H
#define GPIOONOFF_H


#include <QThread>


class GpioOnOff : public QThread
{
    Q_OBJECT
public:

    /* Is this accepted in C++? Probably not :-) */
private:
    bool end;
    void run();
    void msleep(long iSleepTime);
    void usleep(long iSleepTime);
    void sleep(long iSleepTime);
signals:

public slots:
};

#endif // GPIOONOFF_H

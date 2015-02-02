#ifndef CPUINFO_H
#define CPUINFO_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "cpuloadworker.h"

class CpuInfo : public QTimer
{
    Q_OBJECT
public:
    CpuInfo(QObject *parent = 0);
    Q_INVOKABLE void setCpuLoadActive(bool load);
    Q_INVOKABLE float getCpuLoad();
    Q_INVOKABLE void shutdown();

private:
    void refreshCpuTicks();

    long totalTicks;
    long idle;
    float cpuLoad;

    QThread *workerThread;
    CpuLoadWorker *worker;

private slots:
    void tick();
};

#endif // CPUINFO_H

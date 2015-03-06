#include "cpuinfo.h"

#include <iostream>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QProcess>
#include <QTimer>

#define CPU_INFO_FILE "/proc/stat"

CpuInfo::CpuInfo(QObject *parent)
    : QTimer(parent)
{

    refreshCpuTicks();
    connect(this, SIGNAL(timeout()), this, SLOT(tick()));
    setInterval(1000);
    start();
}

void CpuInfo::tick()
{
    long totalTicksOld = totalTicks;
    long idleOld = idle;
    refreshCpuTicks();

    cpuLoad = (float)(idle - idleOld) * 100 / (totalTicks - totalTicksOld);
    cpuLoad = 100 - cpuLoad;
}

void CpuInfo::refreshCpuTicks( )
{
    QFile file(CPU_INFO_FILE);
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly))
        return;

    QString line = in.readLine();
    file.close();

    QStringList query = line.split(" ", QString::SkipEmptyParts);

    // Parse cpu stats, these are cpu ticks
    // in this order: user, nice, system, idle, iowait, irq, softirq
    totalTicks = 0;
    for (int i = 0; i < query.size(); i++) {
        totalTicks += query.at(i).toInt();
    }
    idle = query.at(4).toInt();
}


float CpuInfo::getCpuLoad()
{
    return cpuLoad;
}

void CpuInfo::shutdown()
{
    QProcess *process = new QProcess(this);
    process->start("halt");
}

void CpuInfo::setCpuLoadActive(bool load)
{
    qDebug() << "Called generateCpuLoad" << load;
    if (load)
    {
        worker = new CpuLoadWorker;
        workerThread = new QThread;
        worker->moveToThread(workerThread);
        QMetaObject::invokeMethod(worker, "doCpuLoad", Qt::QueuedConnection);
        worker->setEnd(false);
        workerThread->start();
    }
    else
    {
        worker->setEnd(true);
    }

}


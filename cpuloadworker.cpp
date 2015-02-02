#include "cpuloadworker.h"
#include <QDebug>
#include <QCoreApplication>

CpuLoadWorker::CpuLoadWorker(QObject *parent) :
    QObject(parent)
{
    end = false;
}

void CpuLoadWorker::setEnd(bool end)
{
    this->end = end;
}

void CpuLoadWorker::doCpuLoad()
{
    qDebug() << "CpuLoad Started!";
    while(!this->end)
    {
        asm ( "nop" );
        // Trigger threads message loop
        QCoreApplication::processEvents();
    }
    qDebug() << "CpuLoad Ended!";
}

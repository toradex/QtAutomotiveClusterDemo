#ifndef CPULOADWORKER_H
#define CPULOADWORKER_H

#include <QObject>

class CpuLoadWorker : public QObject
{
    Q_OBJECT
public:
    explicit CpuLoadWorker(QObject *parent = 0);
    void setEnd(bool end);

    /* Is this accepted in C++? Probably not :-) */
private:
    bool end;

signals:

public slots:
    void doCpuLoad();
};

#endif // CPULOADWORKER_H

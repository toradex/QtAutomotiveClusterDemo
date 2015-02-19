#include <unistd.h>
#include "QtAutomotiveClusterDemo.h"
#include <QtGui/QApplication>
#include <QTextStream>
#include <QtGui/QApplication>
#include <QDebug>
#include <QTimer>
#include <QProcess>
#include <QTime>
#include "cpuinfo.h"
#include "gpio.h"

//#define RESOLUTION_1024x600

int main(int argc, char *argv[])
{
    int ret;

	QApplication a(argc, argv);
	QDeclarativeView view, graphView;

    CpuInfo cpuInfo;
    view.rootContext()->setContextProperty("cpuInfo", &cpuInfo);

    GpioOnOff gpio;
    gpio.start();

    QString branch = qApp->applicationDirPath();
    QtAutomotiveClusterDemo w;
    view.rootContext()->setContextProperty("myObject", &w);							// set the myObject to communicate between qml and c++
//#define RESOLUTION_1024x600
#ifdef RESOLUTION_1024x600
    QTextStream(stdout) << branch.toLatin1() + "/QtAutomotiveClusterDemoDesign/qml_1024x600.qml" << endl;
    view.setSource(QUrl::fromLocalFile(branch.toLatin1() + "/QtAutomotiveClusterDemoDesign/qml_1024x600.qml"));	// qml.qml is main page
#else
    QTextStream(stdout) << branch.toLatin1() + "/QtAutomotiveClusterDemoDesign/qml_800x480.qml" << endl;
    view.setSource(QUrl::fromLocalFile(branch.toLatin1() + "/QtAutomotiveClusterDemoDesign/qml_800x480.qml"));	// qml.qml is main page

#endif
	//view.setWindowFlags(Qt::FramelessWindowHint | Qt::Window);					// this statement can make the window frameless
    view.showFullScreen();
	//w.showMaximized();
    ret = a.exec();

    gpio.terminate();

    return ret;
}

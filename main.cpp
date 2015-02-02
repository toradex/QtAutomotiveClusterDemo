
#include "stdafx.h"
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
#include "xypenplottercontroller.h"

//#define RESOLUTION_1024x600

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QDeclarativeView view, graphView;

    CpuInfo cpuInfo;
    view.rootContext()->setContextProperty("cpuInfo", &cpuInfo);

    GpioOnOff gpio;
    gpio.start();


//    XYPenPlotterController ppController;
//    view.rootContext()->setContextProperty("ppController", &ppController);

    sleep(3);

    QProcess process2;
    process2.start("export QWS_DISPLAY=\"LinuxFb:/dev/fb:genericcolors\"");
    process2.waitForFinished();

    QProcess process3;
    process3.start("export QWS_KEYBOARD=\"USB:/dev/input/event-keyboard\"");
    process3.waitForFinished();

    QProcess process4;
    process4.start("export QWS_MOUSE_PROTO=\"USB:/dev/input/event-mouse\"");
    process4.waitForFinished();

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
    //view.isFullScreen();
    view.showFullScreen();
	//w.showMaximized();
    return a.exec();
}

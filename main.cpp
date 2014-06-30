
#include "stdafx.h"
#include "QtAutomotiveClusterDemo.h"
#include <QtGui/QApplication>
#include <QTextStream>
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QDeclarativeView view, graphView;


    QString branch = qApp->applicationDirPath();
    QtAutomotiveClusterDemo w;
    view.rootContext()->setContextProperty("myObject", &w);							// set the myObject to communicate between qml and c++

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

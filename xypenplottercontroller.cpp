#include "xypenplottercontroller.h"
#include <QDebug>
#include <QTimer>
#include <QProcess>
#include <QTime>
#ifdef Q_WS_QWS
#include <linux/mcc_config.h>
#include <linux/mcc_common.h>
#include <linux/mcc_linux.h>
extern "C" {
#include <mcc_api.h>
}
#include <stdint.h>


#define MCC_NODE_A5 1
#define MCC_NODE_M4 2

#define PLOTTER_STOP    0 /* Plotter is in Stopped mode */
#define PLOTTER_START   1 /* Plotter is in Started mode */
#define PLOTTER_DRAW    2 /* Start to draw, from the beginning */
#define PLOTTER_UNPAUSE 9 /* Continue drawing, at last point */
#define PLOTTER_PAUSE   10 /* Pause drawing */
#define PLOTTER_HOME    11
#define PLOTTER_WELCOME 12


MCC_ENDPOINT endpoint_a5 = {0,0,MCC_NODE_A5};
MCC_ENDPOINT endpoint_m4 = {1,0,MCC_NODE_M4};


int send_msg(msg_t *msg)
{
    int retval;

    retval = mcc_send(&endpoint_m4, msg, sizeof(msg_t), 0xffffffff);
    if(retval)
        qDebug("mcc_send failed, result = 0x%x", retval);

    return retval;
}

int receive_msg(msg_t *msg, int timeout)
{
    int retval, num_of_received_bytes;

    retval = mcc_recv_copy(&endpoint_a5, msg, sizeof(msg_t), (MCC_MEM_SIZE *)&num_of_received_bytes, timeout);
    if(retval)
        qDebug("mcc_recv_copy failed, result = 0x%x",  retval);
    return retval;
}



XYPenPlotterController::XYPenPlotterController(QObject *parent) :
    QObject(parent)
{
//    MCC_INFO_STRUCT info_data;
//    int retval = 0;
//    uint32_t node_num = endpoint_a5.node;

//    retval = mcc_initialize(node_num);
//    if(retval)
//    {
//        qDebug("Error during mcc_initialize, result = %d", retval);
//        return;
//    }

//    retval = mcc_get_info(node_num, &info_data);
//    if(retval)
//    {
//        qDebug("Error during mcc_get_info, result = %d", retval);
//        return;
//    }

    qDebug("Plotter app");
//    qDebug("mcc version: %s", info_data.version_string);

//    retval = mcc_create_endpoint(&endpoint_a5, endpoint_a5.port);
//    if(retval)
//    {
//        qDebug("mcc_create_endpoint failes, result = 0x%x", retval);
//        mcc_destroy(node_num);
//        return;
//    }

//    qDebug("Connecting to plotter...");
//    msg.data = PLOTTER_WELCOME;

//    do {
//        retval = send_msg(&msg);

//        if(retval == MCC_ERR_ENDPOINT)
//        {
//            // Firmware is not loaded!? Load the plotter firmware...
//            qDebug("Loading firmware...");
//            QProcess *process = new QProcess(this);
//            process->start("mqxboot /var/cache/xyplotter/plotter.bin 0x8f000400 0x0f000411");
//            process->waitForFinished();

//            // Wait until its ready...
//            QTime dieTime= QTime::currentTime().addMSecs(100);
//            while( QTime::currentTime() < dieTime );
//        }
//    } while (retval != MCC_SUCCESS);

//    qDebug("Welocme message sent! Waiting for response...");
//    if(receive_msg(&rcv_msg, 1000000))
//        return;

//    if(rcv_msg.status != PLOTTER_WELCOME)
//    {
//        qDebug("Oops! Something went wrong! Plotter response = 0x%x\n", rcv_msg.status);
//        return;
//    }
//    else
//    {
//        qDebug("Greeting received. Connected to ploter!\n");
//    }

//    qDebug("Homing plotter");
//    fflush(stdout);
//    msg.data = PLOTTER_HOME;
//    if(send_msg(&msg))
//        return;

//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(receivePlotterMessages()));
//    timer->start(100);
}


//void XYPenPlotterController::handleMessage(msg_t *rcv_msg)
//{
//    if(rcv_msg->status == PLOTTER_DRAW)
//    {
//        qDebug("Plotter start draw!");
//        setCurrentState("RUNNING");
//    }
//    else if(rcv_msg->status == PLOTTER_START)
//    {
//        // Update progress bar...
//        setProgress(rcv_msg->data);
//    }
//    else if(rcv_msg->status == PLOTTER_UNPAUSE)
//    {
//        setCurrentState("RUNNING");
//    }
//    else if(rcv_msg->status == PLOTTER_PAUSE)
//    {
//        setCurrentState("PAUSED");
//    }
//    else if(rcv_msg->status == PLOTTER_HOME)
//    {
//        setCurrentState("WORKING");
//    }
//    else if(rcv_msg->status == PLOTTER_STOP)
//    {
//        if(currentState != "STOPPED")
//            setCurrentState("STOPPED");
//        // Reset progress bar...
//        setProgress(0);
//    }
//    else
//    {
//        qDebug("Something went wrong! Plotter status = 0x%x", rcv_msg->status);
//    }
//}

//void XYPenPlotterController::receivePlotterMessages()
//{
//    if(receive_msg(&rcv_msg, 100) == 0)
//        handleMessage(&rcv_msg);

//    if (!commandSent) {
//        msg.data = 0xff;
//        if(send_msg(&msg))
//            return;
//    }
//    commandSent = false;
//}


/*
 * User requests new state by pressing button
 */
void XYPenPlotterController::pressStart()
{
    qDebug() << "pressStart";

    if(currentState == "STOPPED")
    {
        // We set state imeaditly..
        setCurrentState("RUNNING");
        timer->start();
    }
    else if(currentState == "RUNNING")
    {
        timer->stop();
        setCurrentState("PAUSED");
    }
    else if(currentState == "PAUSED")
    {
        timer->start();
        setCurrentState("RUNNING");
    }
}

void XYPenPlotterController::home()
{
    qDebug() << "Home...";
    msg.data = PLOTTER_HOME;
    if(send_msg(&msg))
        return;
    commandSent = true;
}

#else /* Q_WS_QWS => Desktop... */

XYPenPlotterController::XYPenPlotterController(QObject *parent) :
    QObject(parent)
{
    setCurrentState("STOPPED");
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(setStoppedState()));
}

void XYPenPlotterController::pressStart()
{
    qDebug() << "pressStart";

    if(currentState == "STOPPED")
    {
        // We set state imeaditly..
        setCurrentState("RUNNING");
        counter = 0;

        timer->start();
    }
    else if(currentState == "RUNNING")
    {
        timer->stop();
        setCurrentState("PAUSED");
    }
    else if(currentState == "PAUSED")
    {
        timer->start();
        setCurrentState("RUNNING");
    }
}

void XYPenPlotterController::setStoppedState()
{
    counter++;

    /* After 5 seconds, we stop simulated printing... */
    if(counter >= 50)
    {
        qDebug() << "setStoppedState";
        setCurrentState("STOPPED");
        timer->stop();
    }

    setProgress(counter * 2);
}

void XYPenPlotterController::home()
{
    qDebug() << "Home...";
}
#endif

bool XYPenPlotterController::isStopped()
{
    return currentState == "STOPPED";
}
void XYPenPlotterController::selectImage(QString image)
{
    selectedImage = image;

    int lastPoint = selectedImage.lastIndexOf(".");
    binaryFile = selectedImage.left(lastPoint) + ".bin";
    // Remove "file://"
    binaryFile.remove(0, 7);
}

/*
 * Printer says which state it is in...
 */
void XYPenPlotterController::setCurrentState(QString newState)
{
    if (currentState != newState) {
        qDebug() << "printer is in new state:" << newState;
        currentState = newState;
        emit stateChanged(newState);
    }
}

/*
 * Update current progress
 */
void XYPenPlotterController::setProgress(int progress)
{
    if(progress > 100)
        emit progressUpdate(100);
    else
        emit progressUpdate(progress);
}

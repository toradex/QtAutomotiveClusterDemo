# Project Options
TEMPLATE = app
TARGET = QtAutomotiveClusterDemo

nomcc {
} else {
    LIBS += -lmcc
}

DEPENDPATH += .
MOC_DIR = .build
OBJECTS_DIR = .build
RCC_DIR = .build
UI_DIR = .build
QT = core \
    gui \
    svg \
    network \
    xml \
    declarative

# use OpenGL where available
contains(QT_CONFIG, opengl)|contains(QT_CONFIG, opengles1)|contains(QT_CONFIG, opengles2) {
    QT += opengl
}

# QtAutomotiveClusterDemo input files
include(QtAutomotiveClusterDemo.pri)


# Installation path
#target.path = /usr/bin

OTHER_FILES += \
    QtAutomotiveClusterDemoDesign/RpmDial.qml \
    QtAutomotiveClusterDemoDesign/SpeedDial.qml \
    QtAutomotiveClusterDemoDesign/FuelMeter.qml \
    QtAutomotiveClusterDemoDesign/qml.qml \
    QtAutomotiveClusterDemoDesign/qml_800x480.qml \
    QtAutomotiveClusterDemoDesign/qml_1024x600.qml \
    QtAutomotiveClusterDemoDesign/SmallRoundButton.qml \
    QtAutomotiveClusterDemoDesign/RoundButton.qml \
    QtAutomotiveClusterDemoDesign/ProgressBar.qml \
    QtAutomotiveClusterDemoDesign/ProgressBarLabel.qml


#OTHER_FOLDER += QtAutomotiveClusterDemoDesign

#QMAKE_POST_LINK += $$quote(cp -r $${PWD}/$${OTHER_FOLDER} $${OUT_PWD})

#for(FILE, OTHER_FILES){
# QMAKE_POST_LINK += $$quote(cp $${PWD}/$${FILE} $${OUT_PWD})
#}


# deployment on Linux
unix {
    target.path = /usr/bin/
    qml.path = /usr/bin/QtAutomotiveClusterDemoDesign
    qml.files = QtAutomotiveClusterDemoDesign/*
    INSTALLS += target \
        qml \
}

HEADERS +=

SOURCES +=

######################################################################
# Automatically generated by qmake (3.1) Mon Jun 19 00:40:37 2023
######################################################################

TEMPLATE = app
TARGET = LogicGates
INCLUDEPATH += .
QT += widgets

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += 2dForwardList.h \
           button.h \
           component.h \
           componentObserverInterface.h \
           componentVisitorInterface.h \
           dataPersistance.h \
           lamp.h \
           logicGate.h \
           View/componentInfo.h \
           View/componentInfoBar.h \
           View/componentInfoVisitor.h \
           View/componentView.h \
           View/componentViewVisitor.h \
           View/mainwindow.h \
           View/pinView.h \
           View/sideBar.h \
           View/standardComponentInfo.h \
           View/standardComponentsBar.h \
           View/wire.h \
           View/workBench.h
SOURCES += 2dForwardList.cpp \
           button.cpp \
           component.cpp \
           dataPersistance.cpp \
           lamp.cpp \
           logicGate.cpp \
           main.cpp \
           View/componentInfo.cpp \
           View/componentInfoBar.cpp \
           View/componentInfoVisitor.cpp \
           View/componentView.cpp \
           View/componentViewVisitor.cpp \
           View/mainwindow.cpp \
           View/pinView.cpp \
           View/sideBar.cpp \
           View/standardComponentInfo.cpp \
           View/standardComponentsBar.cpp \
           View/wire.cpp \
           View/workBench.cpp
RESOURCES +=

DISTFILES += \
    ../build-LogicGates-Desktop_Qt_5_12_12_GCC_64bit-Debug/savedComponents.json

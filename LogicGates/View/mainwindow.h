#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "sideBar.h"
#include "../2dForwardList.h"
#include "workBench.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(twoDForwardList& dataStructure);
};

#endif // MAINWINDOW_H

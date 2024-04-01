#include "mainwindow.h"

MainWindow::MainWindow(twoDForwardList& dataStructure){
   //centralWidget
   workbench* mainWorkBenchScene= new workbench(dataStructure,this);
   QGraphicsView* mainWorkBenchView= new QGraphicsView(mainWorkBenchScene);
   mainWorkBenchView->setMouseTracking(true);
   mainWorkBenchView->setDragMode(QGraphicsView::ScrollHandDrag);
   setCentralWidget(mainWorkBenchView);

   //left sideBar
   sideBar* leftSideBar= new sideBar(dataStructure,true,this);
   connect(leftSideBar,SIGNAL(componentInfoPressed(component&)),mainWorkBenchScene,SLOT(onComponentInfoPressed(component&)));
   QDockWidget* leftDock = new QDockWidget(this);
   leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
   leftDock->setWidget(leftSideBar);
   addDockWidget(Qt::LeftDockWidgetArea, leftDock);


   //right sideBar
   sideBar* rightSideBar = new sideBar(dataStructure,false,this);
   connect(mainWorkBenchScene,SIGNAL(connectComponentToSideBar(componentView&)),rightSideBar,SLOT(onComponentPressed(componentView&)));
   connect(rightSideBar,SIGNAL(componentViewDelete(componentView*)),mainWorkBenchScene,SLOT(onComponentViewDelete(componentView*)));
   connect(mainWorkBenchScene,SIGNAL(backSpaceClicked()),rightSideBar,SLOT(backSpaceClicked()));
   connect(mainWorkBenchScene,SIGNAL(updateInfo(component*)),rightSideBar,SIGNAL(updateInfo(component*)));
   QDockWidget* rightDock = new QDockWidget(this);
   rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
   rightDock->setWidget(rightSideBar);
   addDockWidget(Qt::RightDockWidgetArea, rightDock);
}

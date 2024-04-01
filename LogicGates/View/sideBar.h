#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QLabel>
#include "../2dForwardList.h"
#include "standardComponentsBar.h"
#include "componentInfoBar.h"
#include "componentView.h"


class sideBar : public QWidget{
    Q_OBJECT
private:
    twoDForwardList& dataStructure;
    int shownBarWidth = 300;
    int hiddenBarWidth = 30;
    bool isOnLeftSide;
    bool isShown;
    QWidget* bar;
    QPushButton* arrowButton;
    componentView* showedComponentView;
    component* showedCoreComponent;
public:
    sideBar(twoDForwardList& dataStructure, bool isOnLeftSide,QWidget* parent = 0,bool isShown = true,componentView* showedComponent = nullptr);

signals:
    void componentInfoPressed(component&);
    void componentViewDelete(componentView*);
    void updateInfo(component*);

public slots:
    void onArrowButtonPressed();
    void backSpaceClicked();
    void onDeleteButtonPressed();
    void onComponentPressed(componentView& compView);
};

#endif // SIDEBAR_H

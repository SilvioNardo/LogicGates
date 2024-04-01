#ifndef COMPONENTINFOBAR_H
#define COMPONENTINFOBAR_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSizePolicy>
#include "../component.h"
#include "componentInfo.h"
#include "../2dForwardList.h"

class componentInfoBar: public QWidget{
    Q_OBJECT
private:
    twoDForwardList& dataStructure;
    component* coreComponent;
    componentInfo* info;
public:
    componentInfoBar(twoDForwardList& dataStructure , component* coreComponent,QWidget* parent = 0);
signals:
    void deleteButtonClick();
public slots:
    void onDeleteButtonPressed();
    void onUpdateInfo(component*);
};

#endif // COMPONENTINFOBAR_H

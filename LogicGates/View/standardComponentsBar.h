#ifndef STANDARDCOMPONENTSBAR_H
#define STANDARDCOMPONENTSBAR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "standardComponentInfo.h"
#include "../2dForwardList.h"

class standardComponentsBar: public QWidget{
    Q_OBJECT
public:
    standardComponentsBar(twoDForwardList& dataStructure,QWidget* parent = 0);
signals:
    void componentInfoPressed(component&);
};

#endif // STANDARDCOMPONENTSBAR_H

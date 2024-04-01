#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QCursor>
#include "componentView.h"
#include "../2dForwardList.h"
#include "wire.h"

class workbench: public QGraphicsScene{
    Q_OBJECT;
private:
    qreal sceneWidth;
    qreal sceneHeight;
    QGraphicsItem *currentDraggedItem;
    twoDForwardList& dataStructure;
    pinView* pinConnected;
public:
    workbench(twoDForwardList& dataStructure,QWidget* parent = 0, qreal sceneWidth = 3000,qreal sceneHeight= 2000,qreal x=0,qreal y=0);
    void insertComponent(component& coreComponent);
    QPointF cursorScenePos()const;
    void updateLamp(componentView*);
    void deleteWires(pinView*);
protected:
    virtual void keyPressEvent(QKeyEvent *event)override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void connectComponentToSideBar(componentView&);
    void backSpaceClicked();
    void updateInfo(component*);

public slots:
    void onComponentInfoPressed(component&);
    void onComponentViewDelete(componentView*);
    void onPinPressed(pinView&);
    void updateLamps();
};

#endif // WORKBENCH_H

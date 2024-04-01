#ifndef COMPONENTVIEW_H
#define COMPONENTVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QColor>
#include <QRectF>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QList>
#include "componentViewVisitor.h"
#include "../component.h"
#include "pinView.h"

class componentView : public QObject, public QGraphicsItemGroup{
    Q_OBJECT;
private:
    QColor color;
    component& coreComponent;
    qreal mainItemWidth;
    qreal mainItemHeigth;
    QPointF mousePos;
    QList<pinView*> pinConnected;
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
public:
    componentView(component& coreComponent, QColor color = Qt::gray,QGraphicsItem * parent = 0);
    qreal getMainItemWidth() const;
    qreal getMainItemHeigth() const;
    QList<pinView*> getPinConnected()const;
    component* getCoreComponent()const;
    void checkCollisions();
    bool isLamp()const;
    bool isLampOn()const;
signals:
    void componentSelected(componentView& coreComponent);
    void updateInfo(component*);
    void pinPressed(pinView&);
    void updateLamps();
};

#endif // COMPONENTVIEW_H

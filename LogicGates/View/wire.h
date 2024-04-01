#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QPointF>
#include <QColor>
#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>


class pinView;
class wire: public QGraphicsLineItem{
private:
    //QPair<pinView*,pinView*> connectedPins;
    std::pair<pinView*,pinView*> connectedPins;
    QPointF startPoint;
    QPointF endPoint;
    QColor color;
    qreal width;
public:
    wire(QPointF startPoint,QPointF endPoint,QColor color = QColor(60,60,60,255),qreal width = 3,QGraphicsItem * parent = nullptr);
    QPointF getStartPoint()const;
    QPointF getEndPoint()const;
    std::pair<pinView*,pinView*> getConnectedPins()const;
    void setConnectedPins(std::pair<pinView*,pinView*>);
    void setStartPoint(const QPointF&);
    void setEndPoint(const QPointF&);
};

#endif // WIRE_H

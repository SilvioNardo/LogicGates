#include "wire.h"

wire::wire(QPointF startPoint,QPointF endPoint,QColor color ,qreal width,QGraphicsItem * parent):QGraphicsLineItem(parent),startPoint(startPoint),endPoint(endPoint),color(color),width(width){
    setLine(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());
    setPen(QPen(QBrush(color),width));
}

QPointF wire::getStartPoint()const{
    return startPoint;
}

QPointF wire::getEndPoint()const{
    return endPoint;
}

std::pair<pinView*,pinView*> wire::getConnectedPins() const{
    return connectedPins;
}

void wire::setConnectedPins(std::pair<pinView*,pinView*> pair){
    connectedPins = pair;
}

void wire::setStartPoint(const QPointF& sp){
    startPoint = sp;
}

void wire::setEndPoint(const QPointF& ep){
    endPoint = ep;
}

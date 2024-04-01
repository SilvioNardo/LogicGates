#include "pinView.h"

pinView::pinView(component::pin& corePin,qreal x, qreal y, qreal width , QColor color,QGraphicsRectItem* parent):QGraphicsRectItem(x,y,width,width,parent),color(color),corePin(corePin),width(width){
    setBrush(color);
}

qreal pinView::getWidth() const{
    return width;
}

bool pinView::getIsInput()const{
    return corePin.isInput;
}

bool pinView::isPinConnected() const{
    return !corePin.getPinConnected().empty();
}

component* pinView::getComponentConnected()const{
    return corePin.componentConnected;
}

bool pinView::getState()const{
    return corePin.getState();
}

void pinView::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::LeftButton){
      emit pinPressed(*this);
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void pinView::disconnect(){
    component::disconnect(&corePin);
}

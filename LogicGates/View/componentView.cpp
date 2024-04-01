#include "componentView.h"

componentView::componentView(component& coreComponent, QColor color,QGraphicsItem * parent): QGraphicsItemGroup(parent),color(color),coreComponent(coreComponent){
    setCursor(Qt::PointingHandCursor);
    setHandlesChildEvents(false);
    //core component:
    componentViewVisitor visitor;
    coreComponent.accept(visitor);
    auto mainItem = visitor.getItem();
    QRectF mainItemRec = mainItem->boundingRect();
    mainItemWidth = mainItemRec.width();
    mainItemHeigth = mainItemRec.height();
    addToGroup(mainItem);

    //input pins:
    qreal spaceBetweenPins = mainItemHeigth/(coreComponent.getNumberOfInputs() + 1);
    auto input = coreComponent.getInput();
    int pinNumber = 1;
    for(auto it = input.begin(); it != input.end(); ++it){
        pinView* pin = new pinView(*(*it),mainItem->boundingRect().x(),mainItem->boundingRect().y() + spaceBetweenPins * pinNumber);
        pinConnected.push_back(pin);
        connect(pin,SIGNAL(pinPressed(pinView&)),this,SIGNAL(pinPressed(pinView&)));
        pin->moveBy(- pin->getWidth()/2,-pin->getWidth()/2);
        addToGroup(pin);
        ++pinNumber;
    }

    //output pins:
    spaceBetweenPins = mainItemHeigth/(coreComponent.getNumberOfOutputs() + 1);
    auto output = coreComponent.getOutput();
    pinNumber = 1;
    for(auto it = output.begin(); it != output.end(); ++it){
        pinView* pin = new pinView(*(*it),mainItem->boundingRect().x() + mainItemWidth, mainItem->boundingRect().y() + spaceBetweenPins * pinNumber);
        pinConnected.push_back(pin);
        connect(pin,SIGNAL(pinPressed(pinView&)),this,SIGNAL(pinPressed(pinView&)));
        pin->moveBy(-pin->getWidth()/2,-pin->getWidth()/2);
        addToGroup(pin);
        ++pinNumber;
    }
}

qreal componentView::getMainItemWidth() const{
    return mainItemWidth;
}
qreal componentView::getMainItemHeigth() const{
    return mainItemHeigth;
}

QList<pinView*> componentView::getPinConnected() const{
    return pinConnected;
}

component* componentView::getCoreComponent() const{
    return &coreComponent;
}

void componentView::checkCollisions(){
    auto collidingItemList = collidingItems();
    for(auto it = collidingItemList.begin();it != collidingItemList.end();++it){
        if(dynamic_cast<componentView*>(*it)){
            moveBy(0,20);
            checkCollisions();
        }
    }
}

bool componentView::isLamp()const{
    return (dynamic_cast<lamp*>(&coreComponent))?(true):(false);
}

bool componentView::isLampOn()const{
    return (dynamic_cast<lamp*>(&coreComponent))->getState();
}

void componentView::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        setCursor(Qt::ClosedHandCursor);
        setZValue(1);
        mousePos = event->scenePos();
    }
    QGraphicsItemGroup::mousePressEvent(event);
}

void componentView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        setCursor(Qt::PointingHandCursor);
        setZValue(0);
        if(event->scenePos() == mousePos){
            emit componentSelected(*this);
        }
        checkCollisions();
    }
    QGraphicsItemGroup::mouseReleaseEvent(event);
}

void componentView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        button* b = dynamic_cast<button*>(&(this->coreComponent));
        if(b){
            //update item info
            b->pressButton();
            emit updateLamps();
            emit updateInfo(b);

            //change item color
            QColor color;
            if(b->getIsPressed()){
                color = QColor(245,190,70,255);
            }
            else{
                color = QColor(90,90,90,255);
            }
            auto list = this->childItems();
            QGraphicsItem * mainItem = list.first();
            dynamic_cast<QGraphicsRectItem*>(mainItem)->setBrush(color);
        }
    }
    QGraphicsItemGroup::mouseDoubleClickEvent(event);
}

void componentView::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    for(auto it = pinConnected.begin(); it != pinConnected.end();++it){
        if(!((*it)->wiresConnected.empty())){
            QPointF thisPinPoint = (*it)->mapToScene((*it)->boundingRect().center());
            for(auto it2 = (*it)->wiresConnected.begin() ;it2 != (*it)->wiresConnected.end();++it2){
                //cambio lo startPoint della linea di wire
                QPointF startPoint = (*it2)->getStartPoint();
                QPointF endPoint = (*it2)->getEndPoint();
                QPointF otherPoint = (endPoint == thisPinPoint)?(startPoint):(endPoint);
                (*it2)->setStartPoint(thisPinPoint);
                (*it2)->setEndPoint(otherPoint);
                (*it2)->setLine(thisPinPoint.x(),thisPinPoint.y(),otherPoint.x(),otherPoint.y());
            }
        }
    }
    QGraphicsItemGroup::mouseMoveEvent(event);
}

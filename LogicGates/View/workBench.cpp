#include "workBench.h"

workbench::workbench(twoDForwardList& dataStructure,QWidget* parent, qreal sceneWidth, qreal sceneHeight, qreal x,qreal y):QGraphicsScene(x,y,sceneWidth,sceneHeight,parent),sceneWidth(sceneWidth),sceneHeight(sceneHeight),dataStructure(dataStructure),pinConnected(nullptr){
    // background:
    QColor backgroundColor = QColor(215, 213, 196, 100);
    QColor lineColor = QColor(116, 128, 135, 50);
    setBackgroundBrush(QBrush(backgroundColor));
    qreal spaceBetweenLines = 15;
    qreal lineWidth = 1;
    QPen backgroundLinesPen(lineColor,lineWidth);

    qreal x1 = spaceBetweenLines;
    qreal y1 = sceneHeight;
    qreal x2 = x1;
    qreal y2 = 0;
    while(x1 < sceneWidth){
        addLine(x1,y1,x2,y2,backgroundLinesPen);
        x1 += lineWidth + spaceBetweenLines;
        x2 = x1;
    }

    x1 = 0;
    y1 = spaceBetweenLines;
    x2 = sceneWidth;
    y2 = y1;
    while(y1 < sceneHeight){
        addLine(x1,y1,x2,y2,backgroundLinesPen);
        y1 += lineWidth + spaceBetweenLines;
        y2 = y1;
    }
}


void workbench::insertComponent(component& coreComponent){
    componentView* componentWidget = new componentView(coreComponent);
    connect(componentWidget,SIGNAL(componentSelected(componentView&)),this,SIGNAL(connectComponentToSideBar(componentView&)));
    connect(componentWidget,SIGNAL(updateInfo(component*)),this,SIGNAL(updateInfo(component*)));
    connect(componentWidget,SIGNAL(pinPressed(pinView&)),this,SLOT(onPinPressed(pinView&)));
    connect(componentWidget,SIGNAL(updateLamps()),this,SLOT(updateLamps()));
    componentWidget->setFlag(QGraphicsItem::ItemIsMovable);
    componentWidget->setAcceptDrops(true);

    auto listOfViews = views();
    QGraphicsView * mainView = listOfViews.first();
    QRect exposedRect(mainView->mapToScene(0,0).toPoint(),mainView->viewport()->rect().size());
    componentWidget->setPos(exposedRect.x()+(exposedRect.width() - componentWidget->getMainItemWidth())/2,exposedRect.y()+(exposedRect.height() - componentWidget->getMainItemHeigth())/2);
    addItem(componentWidget);
    componentWidget->checkCollisions();
}

QPointF workbench::cursorScenePos()const{
    auto viewsList = views();
    auto view = viewsList.first();
    auto globalCoordinates = QCursor::pos();
    auto viewCoordinates = view->mapFromGlobal(globalCoordinates);
    auto sceneCoordinates = view->mapToScene(viewCoordinates);
    return sceneCoordinates;
}

void workbench::deleteWires(pinView* pin){
    // elimino tutti i cavi collegati a pin
    auto start = pin->wiresConnected.begin();
    auto end = pin->wiresConnected.end();
    for(auto thisPinWireConnected = start; thisPinWireConnected != end;++thisPinWireConnected){
        std::pair<pinView*,pinView*> pinsConnected = (*thisPinWireConnected)->getConnectedPins();
        pinView* otherPin = (pinsConnected.first == pin)?(pinsConnected.second):(pinsConnected.first);
        if(otherPin){
            otherPin->wiresConnected.removeOne(*thisPinWireConnected);
            otherPin->pinConnected.removeOne(pin);
            pin->pinConnected.removeOne(otherPin);
        }
        else{
            //caso in cui di elimini un cavo collegato solo ad una estremità
            pinConnected = nullptr;
        }
        pin->wiresConnected.removeOne(*thisPinWireConnected);
        delete (*thisPinWireConnected);
    }
    pin->disconnect(); //deleteWires viene chiamata solo se pin è input oppure se il componente di pin viene eliminato quindi va bene la disconnect
    updateLamps();
}

void workbench::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Backspace){
        emit backSpaceClicked();
    }
    QGraphicsScene::keyPressEvent(event);
}

void workbench::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(pinConnected){
        auto grabbedWire = pinConnected->wiresConnected.last();
        auto line= grabbedWire->line();
        auto mousePos = cursorScenePos();
        grabbedWire->setLine(line.x1(),line.y1(),mousePos.x(),mousePos.y());
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void workbench::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        if(pinConnected){
            QList<QGraphicsItem *> itemsPressed = items(event->scenePos());
            for(auto it = itemsPressed.begin(); it!= itemsPressed.end();++it){
                if(dynamic_cast<pinView*>(*it)) {
                    QGraphicsScene::mousePressEvent(event);
                    return;
                }
            }
            delete pinConnected->wiresConnected.last();
            pinConnected->wiresConnected.pop_back();
            pinConnected = nullptr;
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void workbench::onComponentInfoPressed(component& coreComponent){
    insertComponent(coreComponent.instantiate(dataStructure));
}

void workbench::onComponentViewDelete(componentView* compView){
    auto compViewPinList = compView->getPinConnected();
    for(auto it = compViewPinList.begin();it != compViewPinList.end();++it){
        deleteWires((*it));
    }
    dataStructure.erase(compView->getCoreComponent());
    compView->deleteLater();
}

void workbench::onPinPressed(pinView& pin){
    if(pinConnected){
        //il mouse è già attaccato a un cavo
        if(pinConnected->getIsInput() == pin.getIsInput()){
            //caso in cui si provi a collegere un cavo tra due input o tra due output
            //ELIMINA CAVO
            delete pinConnected->wiresConnected.last();
            pinConnected->wiresConnected.pop_back();
            pinConnected = nullptr;

        }
        else{
            if((pin.getIsInput()) && (pin.isPinConnected())){
                //il pin è un input (può avere solo un cavo collegato) && ha qualcosa di collegato ad esso
                //SCOLLEGA
                deleteWires(&pin);
            }
            //STACCA IL CAVO DAL MOUSE E COLLEGALO AL PIN
            pin.wiresConnected.push_back(pinConnected->wiresConnected.last());
            pin.pinConnected.push_back(pinConnected);
            pinConnected->pinConnected.push_back(&pin);

            QPointF startPoint = pinConnected->wiresConnected.last()->getStartPoint();
            QPointF endPoint = pin.mapToScene(pin.boundingRect().center());
            pin.wiresConnected.last()->setEndPoint(endPoint);
            pin.wiresConnected.last()->setLine(startPoint.x(),startPoint.y(),endPoint.x(),endPoint.y());

            //CREA L'EFFETTIVO COLLEGAMENTO BACKEND
            pinView::connect(pinConnected,&pin);
            std::pair<pinView*,pinView*> pinsConnected(pinConnected,&pin);
            pin.wiresConnected.last()->setConnectedPins(pinsConnected);
            updateLamps();
            pinConnected = nullptr;
        }
    }
    else{
        //il mouse non è già attaccato a un cavo
        pinConnected = &pin;
        if((pin.getIsInput()) && (pin.isPinConnected())){
            //il pin è un input (può avere solo un cavo collegato) && ha qualcosa di collegato ad esso
            //SCOLLEGA
            deleteWires(&pin);
        }
        // CREA UN CAVO E ATTACCALO AL PIN E AL MOUSE
        QPointF startPoint = pin.mapToScene(pin.boundingRect().center());
        wire* newWire = new wire(startPoint,cursorScenePos());
        pinConnected->wiresConnected.push_back(newWire);
        std::pair<pinView*,pinView*> pinsConnected(pinConnected,nullptr);
        pin.wiresConnected.last()->setConnectedPins(pinsConnected);
        addItem(newWire);
   }
}

void workbench::updateLamp(componentView* lampView){
    QColor color;
    if(lampView->isLampOn()){
        color = QColor(245,190,70,255);
    }
    else{
        color = QColor(121,184,220,255);
    }
    auto list = lampView->childItems();
    QGraphicsItem * mainItem = list.first();
    dynamic_cast<QGraphicsEllipseItem*>(mainItem)->setBrush(color);

}

void workbench::updateLamps(){
    auto componentList = items();
    for(auto it = componentList.begin(); it!= componentList.end();++it){
        componentView* compView = dynamic_cast<componentView*>(*it);
        if(compView && compView->isLamp()){
            updateLamp(compView);
        }
    }

}

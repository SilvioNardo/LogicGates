#include "componentViewVisitor.h"

QGraphicsItem* componentViewVisitor::getItem(){
    return item;
}

void componentViewVisitor::visitLamp(lamp& l){
    qreal lampWidth = 35;
    auto lampView = new QGraphicsEllipseItem(0,0,lampWidth,lampWidth);
    QColor lampBorderColor = QColor(120,120,120,255);
    qreal lampBorderWidth = 5;
    lampView->setPen(QPen(lampBorderColor,lampBorderWidth));
    QColor lampColor = QColor(121,184,220,255);
    lampView->setBrush(QBrush(lampColor));
    item = lampView;
}

void componentViewVisitor::visitLogicGate(logicGate& lg){
    qreal logicGateWidth = 70;
    qreal spaceBetweenPins = 20;
    int maxPins = std::max(lg.getNumberOfInputs(),lg.getNumberOfOutputs());
    qreal logicGateHight = spaceBetweenPins + maxPins*spaceBetweenPins;
    auto logicGateView = new QGraphicsRectItem(0,0,logicGateWidth,logicGateHight);
    QColor logicGateBorderColor = QColor(90,90,90,255);
    qreal logicGateBorderWidth = 2;
    logicGateView->setPen(QPen(logicGateBorderColor,logicGateBorderWidth));
    QColor logicGateColor = QColor(158,178,185,255);
    logicGateView->setBrush(QBrush(logicGateColor));

    // text:
    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::fromStdString(lg.getName()),logicGateView);
    text->setBrush(QBrush(Qt::black));
    QFont font;
    qreal pointSize = 12;
    font.setPointSize(pointSize);
    text->setFont(font);
    while(text->boundingRect().width() >= logicGateWidth - 5){
        pointSize -= 0.5;
        font.setPointSizeF(pointSize);
        text->setFont(font);
    }
    text->setX(logicGateWidth/2 - text->boundingRect().width()/2);
    text->setY(logicGateHight/2 - text->boundingRect().height()/2);

    item = logicGateView;
}

void componentViewVisitor::visitButton(button& b){
   qreal ButtonWidth = 30;
   auto buttonView = new QGraphicsRectItem(0,0,ButtonWidth,ButtonWidth);
   QColor buttonBorderColor = QColor(140,140,140,255);
   qreal buttonBorderWidth = 10;
   buttonView->setPen(QPen(buttonBorderColor,buttonBorderWidth));
   QColor buttonColor = QColor(90,90,90,255);
   buttonView->setBrush(QBrush(buttonColor));
   item = buttonView;
}

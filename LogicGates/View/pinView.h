#ifndef PINVIEW_H
#define PINVIEW_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include "../component.h"
#include "wire.h"

class pinView: public QObject,public QGraphicsRectItem{
    Q_OBJECT;
    friend class componentView;
private:
    QColor color;
    component::pin& corePin;
    qreal width;
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
public:
    QList<wire*> wiresConnected;
    QList<pinView*> pinConnected;
    pinView(component::pin& corePin,qreal x = 0, qreal y = 0, qreal width = 10 , QColor color = Qt::black,QGraphicsRectItem* parent = 0);
    qreal getWidth() const;
    bool getIsInput()const;
    bool isPinConnected()const;
    component* getComponentConnected()const;
    bool getState()const;
    void disconnect();
    static void connect(pinView* startPin,pinView* endPin){
        component::connect(&startPin->corePin,&endPin->corePin);
    }    
signals:
    void pinPressed(pinView&);
};

#endif // PINVIEW_H

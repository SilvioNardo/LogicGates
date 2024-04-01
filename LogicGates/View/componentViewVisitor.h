#ifndef COMPONENTVIEWVISITOR_H
#define COMPONENTVIEWVISITOR_H

#include <algorithm>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QGraphicsSimpleTextItem>
#include <QFont>
#include "../lamp.h"
#include "../button.h"
#include "../logicGate.h"
#include "../componentVisitorInterface.h"

class componentViewVisitor : public componentVisitorInterface{
private:
    QGraphicsItem* item;
public:
    QGraphicsItem* getItem();
    virtual void visitLamp(lamp& l) override;
    virtual void visitLogicGate(logicGate& lg) override;
    virtual void visitButton(button& b) override;
};

#endif // COMPONENTVIEWVISITOR_H

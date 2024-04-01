#ifndef COMPONENTINFOVISITOR_H
#define COMPONENTINFOVISITOR_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QTableWidget>
#include <cmath>
#include "../lamp.h"
#include "../button.h"
#include "../logicGate.h"
#include "../componentVisitorInterface.h"

class componentInfoVisitor : public componentVisitorInterface{
private:
    QWidget* widget;
public:
    QWidget* getWidget();
    virtual void visitLamp(lamp& l) override;
    virtual void visitLogicGate(logicGate& lg) override;
    virtual void visitButton(button& b) override;
};

#endif // COMPONENTINFOVISITOR_H

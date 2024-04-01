#ifndef COMPONENTVISITORINTERFACE_H
#define COMPONENTVISITORINTERFACE_H

class lamp;
class logicGate;
class button;

class componentVisitorInterface{
public:
    virtual ~componentVisitorInterface() = default;
    virtual void visitLamp(lamp& l) = 0;
    virtual void visitLogicGate(logicGate& lg) =0;
    virtual void visitButton(button& b) =0;
};

#endif // COMPONENTVISITORINTERFACE_H

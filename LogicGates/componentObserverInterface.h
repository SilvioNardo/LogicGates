#ifndef COMPONENTOBSERVERINTERFACE_H
#define COMPONENTOBSERVERINTERFACE_H

class component;

class componentObserverInterface{
public:
    virtual ~componentObserverInterface() = default;
    virtual void notify(component& character) = 0;
};

#endif // COMPONENTOBSERVERINTERFACE_H

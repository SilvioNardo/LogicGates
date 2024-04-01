#include "lamp.h"



int lamp::numberOfIstances=0;
lamp::lamp(twoDForwardList& tdfl,std::string name,std::string description):component(1,0,"Lampadina standard","Le Lampadine costituiscono l'output del circuito"),isOn(false),id(getComponentNumber(),0),name(name),description(description){
    tdfl.insert(this);
}
lamp::lamp(twoDForwardList& tdfl, const lamp& l):component(l),isOn(false),id(l.id.first,++numberOfIstances),name(l.name),description(l.description){
    tdfl.insert(this);
}

lamp::~lamp(){
    disconnectAll();
}

component& lamp::instantiate(twoDForwardList& tdfl)const{
    lamp* instantiatedLamp = new lamp(tdfl,*this);
    instantiatedLamp->setName(instantiatedLamp->getName() +" "+ std::to_string(instantiatedLamp->getNumberOfInstances()));
    instantiatedLamp->setDescription("istanza numero " + std::to_string(instantiatedLamp->getNumberOfInstances()) + " del componente " + instantiatedLamp->component::getName());
    return *instantiatedLamp;
}

QJsonObject lamp::toJson()const{
    QJsonObject json;
    json["type"] = 2;
    json["instanceName"] = QString::fromStdString(name);
    json["instanceDescription"] = QString::fromStdString(description);
    json["componentName"] = QString::fromStdString(component::getName());
    json["componentDescription"] = QString::fromStdString(component::getDescription());
    return json;
}

void lamp::setName(std::string s){
    name=s;
}
void lamp::setDescription(std::string s){
    description=s;
}
int lamp::getNumberOfInstances()const{
    return numberOfIstances;
}
const std::pair<int,int> lamp::getId()const{
    return id;
}
std::string lamp::getName() const{
    return name;
}
std::string lamp::getDescription() const{
    return description; 
}

bool lamp::getState()const{
    return isOn;
}

void lamp::updateState(){
    if(input[0]->state){
        isOn=true;
    }
    else{
        isOn=false;
    }
}
std::string lamp::printId()const{
    return "componente numero: "+std::to_string(id.first)+"  istanza numero: "+std::to_string(id.second);
}

void lamp::accept(componentVisitorInterface& visitor){
    visitor.visitLamp(*this);
}

std::ostream& operator<<(std::ostream& os,const lamp& l){
    os<<"\nCOMPONENT INFO:"<<std::endl;
    const component* c= &l;
    os<<*c<<std::endl;
    os<<"INSTANCE INFO:"<<std::endl;
    os<<"id= "<<l.printId()<<std::endl;
    os<<"number of instances of this type of component in total: "<<l.getNumberOfInstances()<<std::endl;
    os<<"name: "<<l.getName()<<std::endl;
    os<<"description: "<<l.getDescription()<<std::endl;
    os<<"state: "<<l.isOn<<"\n"<<std::endl;
    return os;
}

#include "button.h"

int button::numberOfIstances=0;
button::button(twoDForwardList& tdfl,std::string name,std::string description):component(0,1,"Interruttore standard","L'utente può cambiare lo stato dell'interruttore. Gli interruttori costituiscono l'input del circuito"),id(getComponentNumber(),0),isPressed(false),name(name),description(description){
    tdfl.insert(this);
}
button::button(twoDForwardList& tdfl, const button& b):component(b),id(b.id.first,++numberOfIstances),isPressed(false),name(b.name),description(b.description){
    tdfl.insert(this);
}

button::~button(){
    disconnectAll();
}

component& button::instantiate(twoDForwardList& tdfl)const{
    button* instantiatedButton = new button(tdfl,*this);
    instantiatedButton->setName(instantiatedButton->getName() +" "+ std::to_string(instantiatedButton->getNumberOfInstances()));
    instantiatedButton->setDescription("istanza numero " + std::to_string(instantiatedButton->getNumberOfInstances()) + " del componente " + instantiatedButton->component::getName());
    return *instantiatedButton;
}

QJsonObject button::toJson()const{
     QJsonObject json;
     json["type"] = 1;
     json["instanceName"] = QString::fromStdString(name);
     json["instanceDescription"] = QString::fromStdString(description);
     json["componentName"] = QString::fromStdString(component::getName());
     json["componentDescription"] = QString::fromStdString(component::getDescription());
     return json;
}

void button::setName(std::string s){
    name=s;
}
void button::setDescription(std::string s){
    description=s;
}
int button::getNumberOfInstances()const{
    return numberOfIstances;
}
const std::pair<int,int> button::getId()const{
    return id;
}
std::string button::getName() const{
    return name;
}
std::string button::getDescription() const{
    return description; 
}
bool button::getIsPressed()const{
    return isPressed;
}
void button::turnOn(){
    isPressed=true;
    // il pin di output si accende e di conseguenza anche i pin a esso collegati
    //richiama la updateState su tali componenti
    output[0]->state=true;
    updatePinStates(output[0]);
}

void button::turnOff(){
    isPressed=false;
    //come per turn on ma spegnendo l'output
    output[0]->state=false;
    updatePinStates(output[0]);
}

void button::pressButton(){
    if(!isPressed){
        turnOn();
    }
    else{
        turnOff();
    }
}
void button::updateState(){
    return; // this function should never occur in buttons
}
std::string button::printId()const{
    return "componente numero: "+std::to_string(id.first)+"  istanza numero: "+std::to_string(id.second);
}

void button::accept(componentVisitorInterface& visitor){
    visitor.visitButton(*this);
}

std::ostream& operator<<(std::ostream& os,const button& b){
    os<<"\nCOMPONENT INFO:"<<std::endl;
    const component* c= &b;
    os<<*c<<std::endl;
    os<<"INSTANCE INFO:"<<std::endl;
    os<<"id= "<<b.printId()<<std::endl;
    os<<"number of instances of this type of component in total: "<<b.getNumberOfInstances()<<std::endl;
    os<<"name: "<<b.getName()<<std::endl;
    os<<"description: "<<b.getDescription()<<std::endl;
    os<<"state: "<<b.isPressed<<"\n"<<std::endl;
    return os;
}

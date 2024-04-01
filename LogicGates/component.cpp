#include "component.h"

//pin
component::pin::pin(bool state):state(state){}
component::pin::~pin(){}
component* component::pin::getComponentConnected()const{
    return componentConnected;
}
bool component::pin::getState()const{
    return state;
}
bool component::pin::getIsInput()const{
    return isInput;
}
std::forward_list<component::pin*> component::pin::getPinConnected()const{
    return pinConnected;
}

//component
int component::numberOfComponents=0;
component::component(int numberOfInputs,int numberOfOutputs,std::string name,std::string description):numberOfInputs(numberOfInputs),numberOfOutputs(numberOfOutputs),name(name), componentNumber(++numberOfComponents),description(description){
    for(int i=0;i<numberOfInputs;++i){
        pin* p=new pin();
        p->isInput=true;
        p->componentConnected=this;
        input.push_back(p);
    }
    for(int i=0;i<numberOfOutputs;++i){
        pin* p=new pin();
        p->isInput=false;
        p->componentConnected=this;
        output.push_back(p);
    } 
}

component::~component(){
    for(int i=0;i<numberOfInputs;++i){
        pin* p = input[i];
        delete p;
    }
    for(int i=0;i<numberOfOutputs;++i){
        pin* o = output[i];
        delete o;
    }
}

component::component(const component& c):numberOfInputs(c.numberOfInputs),numberOfOutputs(c.numberOfOutputs),name(c.name),componentNumber(c.componentNumber),description(c.description){
    for(int i=0;i<numberOfInputs;++i){
        pin* p=new pin;
        p->isInput=true;
        p->componentConnected=this;
        input.push_back(p);
    }
    for(int i=0;i<numberOfOutputs;++i){
        pin* p=new pin;
        p->isInput=false;
        p->componentConnected=this;
        output.push_back(p);
    }
}

void component::disconnectAll(){
    for(int i=0;i<numberOfInputs;++i){
        disconnect(input[i]);
    }
    for(int i=0;i<numberOfOutputs;++i){
        disconnect(output[i]);
    }
}

//setter
void component::setName(std::string s){
    name=s;
}

void component::setDescription(std::string s){
    description=s;
}

//getter
void component::printStates() const{
    std::cout<< "inputs states: ";
    for(int i=0;i<numberOfInputs;++i){
        std::cout<< (*input[i]).getState() << " " <<std::endl;
    }
    std::cout<< "outputs states: ";
    for(int i=0;i<numberOfOutputs;++i){
        std::cout<< (*output[i]).getState() << " " <<std::endl;
    }
    
}
int component::getNumberOfInputs() const{
    return numberOfInputs;
}
int component::getNumberOfOutputs() const{
    return numberOfOutputs;
}

std::string component::getName() const{
    return name;
}
std::string component::getDescription() const{
    return description;
}
int component::getComponentNumber()const{
    return componentNumber;
}
std::vector<component::pin*> component::getInput() const{
    return input;
}
std::vector<component::pin*> component::getOutput() const{
    return output;
}
std::string component::IOtoString(const std::vector<pin*>& v) const{
    std::string s;
    for ( std::vector<pin*>::const_iterator i = v.begin();i != v.end();){
        if (*i==nullptr){
            s.append("null");
        }
        else{
            s.append("\nstate: "+std::to_string((**i).state)+"\ncomponents connected to this pin: ");
            for ( std::forward_list<pin*>::const_iterator j = (**i).pinConnected.begin();j != (**i).pinConnected.end();){
                s.append("id: "+(**j).componentConnected->printId());
                if (++j!=(**i).pinConnected.end()){
                    s.append(", ");
                }
            }
        }
        if (++i!=v.end()){
            s.append(", ");
        }
    }
    return s;
}

void component::registerObserver(componentObserverInterface* observer) {
    observers.push_back(observer);
}

std::ostream& operator<<(std::ostream& os,const component& c){
    os<<"number of components in total: "<<c.getNumberOfComponents()<<std::endl;
    
    //os<<"number of component: "<<c.getComponentNumber()<<std::endl;
    os<<"name: "<<c.getName()<<std::endl;
    os<<"number of inputs: "<<c.getNumberOfInputs()<<std::endl;
    os<<"number of outputs: "<<c.getNumberOfOutputs()<<std::endl;
    os<<"description: "<<c.getDescription()<<std::endl;
    if (c.input.size()!=0){
        os<<"input: "<<c.IOtoString(c.input)<<std::endl;
    }
    else{
        os<<"this component does not have any input"<<std::endl;
    }
    if (c.output.size()!=0){
        os<<"output: "<<c.IOtoString(c.output)<<std::endl;
    }
    else{
        os<<"this component does not have any output"<<std::endl;
    }
    
    return os;
}

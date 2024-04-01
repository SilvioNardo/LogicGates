#include "logicGate.h"

int logicGate::numberOfIstances=0;
std::forward_list<logicGate*> logicGate::logicGatesAlreadyUpdated;

logicGate::logicGate(twoDForwardList& tdfl, int numberOfInputs,int numberOfOutputs,std::vector<std::vector<bool>> truthTable,std::string name,std::string description):component(numberOfInputs,numberOfOutputs,"Porta logica","Le porte logiche implementano una particolare operazione logica di una o più variabili booleane."),id(getComponentNumber(),0),truthTable(truthTable),name(name),description(description){
    tdfl.insert(this);
}
logicGate::logicGate(twoDForwardList& tdfl, const logicGate& lg):component(lg),id(lg.id.first,++numberOfIstances),truthTable(lg.truthTable),name(lg.name),description(lg.description){
    tdfl.insert(this);
}

logicGate::~logicGate(){
    disconnectAll();
}

component& logicGate::instantiate(twoDForwardList& tdfl)const{
    logicGate* instantiatedLogicGate = new logicGate(tdfl,*this);
    instantiatedLogicGate->setName(instantiatedLogicGate->getName() +" "+ std::to_string(instantiatedLogicGate->getNumberOfInstances()));
    instantiatedLogicGate->setDescription("istanza numero " + std::to_string(instantiatedLogicGate->getNumberOfInstances()) + " del componente " + instantiatedLogicGate->component::getName());
    return *instantiatedLogicGate;
}

QJsonObject logicGate::toJson()const{
    QJsonObject json;
    json["type"] = 3;
    json["inputNumber"] = getNumberOfInputs();
    json["outputNumber"] = getNumberOfOutputs();
    QJsonArray jsonTruthTable;
    for(auto row = truthTable.begin(); row != truthTable.end(); ++row){
        QJsonArray rows;
        for(auto column = row->begin(); column != row->end(); ++column){
            rows.append(*column);
        }
        jsonTruthTable.append(rows);
    }
    json["truthTable"] = jsonTruthTable;
    json["instanceName"] = QString::fromStdString(name);
    json["instanceDescription"] = QString::fromStdString(description);
    json["componentName"] = QString::fromStdString(component::getName());
    json["componentDescription"] = QString::fromStdString(component::getDescription());
    return json;
}

void logicGate::setName(std::string s){
    name=s;
}
void logicGate::setDescription(std::string s){
    description=s;
}

int logicGate::getNumberOfInstances()const{
    return numberOfIstances;
}
std::vector<std::vector<bool>> logicGate::getTruthTable()const{
    return truthTable;
}
std::string logicGate::getName() const{
    return name;
}
const std::pair<int,int>  logicGate::getId() const{
    return id;
}
std::string logicGate::printId()const{
    return "componente numero: "+std::to_string(id.first)+"  istanza numero: "+std::to_string(id.second);
}
std::string logicGate::getDescription() const{
    return description;
}
void logicGate::updateState(){ 
    logicGatesAlreadyUpdated.clear();
    smartUpdateState();
}

void logicGate::smartUpdateState(){
    for(auto it = logicGatesAlreadyUpdated.begin(); it != logicGatesAlreadyUpdated.end(); ++it){
        if((*it) == this){
            return;
        }
    }    logicGatesAlreadyUpdated.push_front(this);
    for(std::vector<std::vector<bool>>::const_iterator it=truthTable.begin();it!=truthTable.end();++it){
        for(int i=0;i<getNumberOfInputs();++i){
            if((getInput()[i])->state!=((*it)[i])){
                break;
            }
            else{
                if(i+1==getNumberOfInputs()){
                    for(int j=0;j<getNumberOfOutputs();++j){
                        (getOutput()[j])->state=((*it)[++i]);
                        for(std::forward_list<pin*>::iterator p=(getOutput()[j])->pinConnected.begin();p!=(getOutput()[j])->pinConnected.end();++p){
                            (*p)->state=((*it)[i]);
                            logicGate* lg = dynamic_cast<logicGate*>((*p)->componentConnected);
                            if(lg){
                                lg->smartUpdateState();
                            }
                            else{
                                (*p)->componentConnected->updateState();
                            }
                        }
                    }
                    return;
                }
            }
        }
    }
}

std::string logicGate::TTtoString(const std::vector<std::vector<bool>>& tt)const{
    std::string s;
    for(std::vector<std::vector<bool>>::const_iterator it1=tt.begin();it1!=tt.end();){
        for(std::vector<bool>::const_iterator it2=(*it1).begin();it2!=(*it1).end();){
            s.append(std::to_string(*it2));
            if (++it2!=(*it1).end()){
            s.append(", ");
        }
        }
        if (++it1!=tt.end()){
            s.append("\n");
        }
    }
    return s;
}

void logicGate::accept(componentVisitorInterface& visitor){
    visitor.visitLogicGate(*this);
}

std::ostream& operator<<(std::ostream& os,const logicGate& lg){
    os<<"\nCOMPONENT INFO:"<<std::endl;
    const component* c= &lg;
    os<<*c<<std::endl;
    os<<"INSTANCE INFO:"<<std::endl;
    os<<"id= "<<lg.printId()<<std::endl;
    os<<"number of instances of this type of component in total: "<<lg.getNumberOfInstances()<<std::endl;
    os<<"name: "<<lg.getName()<<std::endl;
    os<<"description: "<<lg.getDescription()<<std::endl;
    os<<"truthTable: \n"<<lg.TTtoString(lg.getTruthTable())<<std::endl;
    return os;
}

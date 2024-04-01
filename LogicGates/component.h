#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <forward_list>
#include <QJsonObject>
#include "componentVisitorInterface.h"
#include "componentObserverInterface.h"

class twoDForwardList;
class component{
    friend class pinView;
    friend std::ostream& operator<<(std::ostream&,const component&);
    private:
        static int numberOfComponents;//start at 0
        const int numberOfInputs;
        const int numberOfOutputs;
        std::string name;
        const int componentNumber;
        std::string description;
        std::vector<componentObserverInterface*> observers;
    protected:
        class pin{
            public:
                friend class component;
                component* componentConnected;
                bool isInput;
                std::forward_list<pin*> pinConnected;
                bool state;      
                pin(bool state=false);
                ~pin();
                bool getState()const;
                bool getIsInput()const;
                component* getComponentConnected()const;
                std::forward_list<pin*> getPinConnected()const;
        };
        std::vector<pin*> input;
        std::vector<pin*> output;
    public:       
        component(int numberOfInputs=0,int numberOfOutputs=0,std::string name="",std::string description="");
        component(const component&);
        virtual component& instantiate( twoDForwardList&)const = 0;
        virtual QJsonObject toJson()const = 0;
        virtual ~component();
        //setter
        void disconnectAll();
        void setName(std::string);
        void setDescription(std::string);
        //getter
        void printStates() const;
        int getNumberOfInputs() const;
        int getNumberOfOutputs() const;
        static int getNumberOfComponents(){
            return numberOfComponents;
        }
        int getComponentNumber()const;
        std::string getName() const;
        std::string getDescription() const;
        std::vector<pin*> getInput() const;
        std::vector<pin*> getOutput() const;
        virtual void updateState() =0;
        std::string IOtoString(const std::vector<pin*>&) const;
        virtual std::string printId()const =0; 
        virtual const std::pair<int,int> getId()const=0;
        static void updatePinStates(pin* p){
            if (p->isInput){
                p->state=(*(p->pinConnected.begin()))->state;
            }
            else{
                for ( std::forward_list<component::pin*>::const_iterator i = p->pinConnected.begin();i != p->pinConnected.end();++i){
                    (*i)->state=p->state;
                    (*i)->componentConnected->updateState();
                }
            }
        }
        static void disconnect(pin* p){
            if (p->isInput){
                p->state=false;
                p->componentConnected->updateState();                
                if(!p->pinConnected.empty()) p->pinConnected.front()->pinConnected.remove(p);
            }
            else{
                for(std::forward_list<pin*>::iterator it = p->pinConnected.begin();it!=p->pinConnected.end();++it){
                    (*it)->state=false;
                    (*it)->componentConnected->updateState();
                    (*it)->pinConnected.clear();
                }
            }
            p->pinConnected.clear(); 
        }
        static void connect(pin* px,pin* py){
            if (py->isInput){ //px is an output
                px->pinConnected.push_front(py);
                if (!(py->pinConnected.empty())){
                    disconnect(py);
                }
                py->pinConnected.push_front(px);
                updatePinStates(py);
                py->componentConnected->updateState();
            }
            else{ //py is an output and px is an input
                py->pinConnected.push_front(px);
                if (!(px->pinConnected.empty())){
                    disconnect(px);
                }
                px->pinConnected.push_front(py);
                updatePinStates(px);
                px->componentConnected->updateState();
            }   
        }
        static std::string pairToString(const std::pair<int,int>& id){
            return "componente numero: "+std::to_string(id.first)+"  istanza numero: "+std::to_string(id.second);
        }
        virtual void accept(componentVisitorInterface& visitor) = 0;
        void registerObserver(componentObserverInterface* observer);
};
std::ostream& operator<<(std::ostream&,const component&);

#endif

#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <QJsonArray>
#include "component.h"
#include "2dForwardList.h"

class logicGate:public component{
    private:
        static int numberOfIstances;//start at 0
        static std::forward_list<logicGate*> logicGatesAlreadyUpdated;
        const std::pair<int,int> id;
        std::vector<std::vector<bool>> truthTable;
        std::string name;
        std::string description;      
    public:
        logicGate(twoDForwardList& tdfl, int numberOfInputs,int numberOfOutputs,std::vector<std::vector<bool>> trouthTable,std::string name="",std::string description="");
        logicGate(twoDForwardList& tdfl, const logicGate&);
        ~logicGate();
        virtual component& instantiate( twoDForwardList&)const override;
        virtual QJsonObject toJson()const override;
        logicGate(const logicGate&) = delete;
        virtual void updateState() override;
        void smartUpdateState();
        void setName(std::string);
        void setDescription(std::string);
        const std::pair<int,int>  getId() const override;
        virtual std::string printId()const override;
        int getNumberOfInstances()const;
        std::vector<std::vector<bool>> getTruthTable()const;
        std::string getName() const;
        std::string getDescription() const; 
        std::string TTtoString(const std::vector<std::vector<bool>>&)const;
        virtual void accept(componentVisitorInterface& visitor) override;
};
std::ostream& operator<<(std::ostream&,const logicGate&);

#endif

#ifndef LAMP_H
#define LAMP_H

#include "component.h"
#include "2dForwardList.h"

class lamp:public component{
    friend std::ostream& operator<<(std::ostream&,const lamp&);
    private:
        bool isOn;
        const std::pair<int,int> id;
        static int numberOfIstances;//start at 0
        std::string name;
        std::string description;
    public:
        lamp(twoDForwardList& tdfl,std::string name="",std::string description="");
        lamp(twoDForwardList& tdfl, const lamp&);
        ~lamp();
        virtual component& instantiate( twoDForwardList&)const override;
        virtual QJsonObject toJson()const override;
        lamp(const lamp&) = delete;
        virtual void updateState() override;
        void setName(std::string);
        void setDescription(std::string);
        int getNumberOfInstances()const;
        const std::pair<int,int> getId()const override;
        std::string getName() const;
        std::string getDescription() const;
        bool getState()const;
        virtual std::string printId()const override;
        virtual void accept(componentVisitorInterface& visitor) override;
};
std::ostream& operator<<(std::ostream&,const lamp&);

#endif

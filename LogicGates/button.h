#ifndef BUTTON_H
#define BUTTON_H
#include "component.h"
#include "2dForwardList.h"

class button:public component{
    friend std::ostream& operator<<(std::ostream&,const button&);
    private:
        static int numberOfIstances;//start at 0
        const std::pair<int,int> id;
        bool isPressed;
        std::string name;
        std::string description;
    public:
        button(twoDForwardList& tdfl,std::string name="",std::string description="");
        button(twoDForwardList& tdfl, const button&);
        ~button();
        virtual component& instantiate( twoDForwardList&)const override;
        virtual QJsonObject toJson()const override;
        button(const button&) = delete;
        void setName(std::string);
        void setDescription(std::string);
        virtual void updateState() override;
        int getNumberOfInstances()const;
        const std::pair<int,int> getId()const override;
        std::string getName() const;
        std::string getDescription() const;
        bool getIsPressed()const;
        virtual std::string printId()const override;
        void turnOn();
        void turnOff();
        void pressButton();
        virtual void accept(componentVisitorInterface& visitor) override;
};
std::ostream& operator<<(std::ostream&,const button&);

#endif

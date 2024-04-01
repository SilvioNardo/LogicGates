#ifndef TWODFORWARDLIST_H
#define TWODFORWARDLIST_H

#include "component.h"
#include <typeinfo>

class twoDForwardList{
    friend class dataPersistance;
private:
    class componentNode{
    public:
        component*  coreComponent; // è un puntatore polimorfo perchè component non è instanziabile
        componentNode* nextCopiedComponent;      
        componentNode(component* coreComponent,componentNode* nextCopiedComponent=nullptr);
        componentNode(const componentNode&) = delete;
        virtual void printNode() const;
        virtual ~componentNode();
    };

    class standardComponentNode: public componentNode{
    public:
        standardComponentNode* nextStandardComponent;
        standardComponentNode(component* coreComponent,componentNode* nextCopiedComponent=nullptr,standardComponentNode* nextStandardComponent=nullptr);
        standardComponentNode(const standardComponentNode&) = delete;
        virtual void printNode() const override;
    };

    standardComponentNode* first;

    static void destroy(standardComponentNode* scn) { 
        if(scn) {
            destroy(scn->nextStandardComponent);
            destroyCopiedNodes(scn);
        }
    }
    static void destroyCopiedNodes(componentNode* cn){
        if(cn){
            destroyCopiedNodes(cn->nextCopiedComponent); 
            delete cn;
        }
    }

public:
    twoDForwardList(standardComponentNode* first = nullptr);
    twoDForwardList(const twoDForwardList&) = delete;
    ~twoDForwardList();
    standardComponentNode* getFirst()const;
    void insert(component* coreComponent); //inserisce un elemento al posto giusto
    void erase(component* coreComponent);  //elimina un elemento
    componentNode* search(std::pair<int,int> id)const; // ritorna un puntatore al nodo relativo al componente dato il suo id 
    void printDataStructure()const;
};

#endif

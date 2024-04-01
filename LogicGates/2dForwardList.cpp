#include "2dForwardList.h"

twoDForwardList::componentNode::componentNode(component* coreComponent,componentNode* nextCopiedComponent):coreComponent(coreComponent),nextCopiedComponent(nextCopiedComponent){}
twoDForwardList::componentNode::~componentNode(){ 
    delete coreComponent;      //se nel main i componenti sono nello stack e faccio la delete, accade un segmentatio fault (perchè al termine del programma andrebbe a deallocare i componenti due volte), quindi i componenti VANNO NELLO HEAP PER FORZA!
} 

void twoDForwardList::componentNode::printNode() const{
    if(((*(this->coreComponent)).getId().second)==0){
         std::cout<<"Nodo standard:"<<std::endl;
    }
    else{
        std::cout<<"Nodo copiato:"<<std::endl;
    }
    std::cout<<"id: "<<(*(this->coreComponent)).printId()<<std::endl;
    std::cout<<"tipo dinamico: "<< typeid(*(this->coreComponent)).name() <<std::endl;
    std::cout<<"indirizzo: "<< this <<std::endl;
    std::cout<<"indirizzo next copied component: "<< this->nextCopiedComponent <<std::endl;
}

twoDForwardList::standardComponentNode::standardComponentNode(component* coreComponent,componentNode* nextCopiedComponent,standardComponentNode* nextStandardComponent):componentNode(coreComponent,nextCopiedComponent),nextStandardComponent(nextStandardComponent){}
void twoDForwardList::standardComponentNode::printNode() const{
    this->componentNode::printNode();
    std::cout<<"indirizzo next standard component: "<< this->nextStandardComponent <<std::endl;
}

twoDForwardList::twoDForwardList(standardComponentNode* first ):first(first){}
twoDForwardList::~twoDForwardList(){
    destroy(first);
}

twoDForwardList::standardComponentNode* twoDForwardList::getFirst()const{
    return first;
}

twoDForwardList::componentNode* twoDForwardList::search(std::pair<int,int> id)const{
    componentNode* punt=first;
    while(punt->coreComponent->getId().first <= id.first){
        if(punt->coreComponent->getId().first == id.first){
            //trovato lo standard
            while(punt->coreComponent->getId().second <= id.second){
                if(punt->coreComponent->getId().second == id.second){
                    //trovato il risultato
                    return punt;
                }
                else{
                    if(punt->nextCopiedComponent){
                        punt=punt->nextCopiedComponent;
                    }
                    else{
                        return punt;
                    }
                }
            }
            return punt=nullptr;
        }
        else{
            punt=(static_cast<standardComponentNode*>(punt))->nextStandardComponent;
        }
    }
    return punt=nullptr;
} // ritorna un puntatore al nodo relativo al componente dato il suo id 




void twoDForwardList::insert(component* coreComponent){
    std::pair<int,int> id = coreComponent->getId();
    if(id.second==0){
        //caso in cui si aggiunga alla struttura dati un elemento standard
        standardComponentNode* newNode = new standardComponentNode(coreComponent);
        if(id.first > 1){
            standardComponentNode* previousNode = static_cast<standardComponentNode*>(search({id.first - 1,0}));
            previousNode->nextStandardComponent = newNode;
        }
        else{
            first = newNode;
        }
    }
    else{
        //caso in cui si aggiunga alla struttura dati una copia di un elemento standard
        componentNode* newNode = new componentNode(coreComponent);
        int idSecond = id.second;
        componentNode* previousNode = nullptr;
        while((previousNode = search({id.first,idSecond - 1})) == nullptr){
            --idSecond;
        }
        previousNode->nextCopiedComponent = newNode;
    }
} //inserisce un elemento al posto giusto dato il suo id 

void twoDForwardList::erase(component* coreComponent){
    std::pair<int,int> id = coreComponent->getId();
    if(id.second==0){
        //caso in cui si elimini un elemento standard dalla struttura dati
        standardComponentNode* erasedNode = static_cast<standardComponentNode*>(search(id));
        if(erasedNode != first){
            standardComponentNode* previousNode = static_cast<standardComponentNode*>(search({id.first - 1,0}));
            previousNode->nextStandardComponent = erasedNode->nextStandardComponent;
        }
        else{
            first = erasedNode->nextStandardComponent;
        }
        destroyCopiedNodes(erasedNode);
    }
    else{
        //caso in cui si elimini elemento copiato da un elemento standard dalla struttura dati
        componentNode* erasedNode = search(id);
        int idSecond = id.second;
        componentNode* previousNode;
        while((previousNode = search({id.first,idSecond - 1})) == nullptr){
            --idSecond;
        }
        previousNode->nextCopiedComponent = erasedNode->nextCopiedComponent;
        delete erasedNode;
    }
}  //elimina un elemento dato il suo id 

void twoDForwardList::printDataStructure()const{
    std::cout<<"\nstampa struttura dati: "<<std::endl;
    standardComponentNode* standardNodePointer = this->first;
    while (standardNodePointer){
        componentNode* copiedNodePointer = standardNodePointer->nextCopiedComponent;
        standardNodePointer->printNode();
        standardNodePointer = standardNodePointer->nextStandardComponent;
        while(copiedNodePointer){
            copiedNodePointer->printNode();
            copiedNodePointer = copiedNodePointer->nextCopiedComponent;
        }
    }
}

#include "componentInfoBar.h"

class sideBar;
componentInfoBar::componentInfoBar(twoDForwardList& dataStructure, component* cc, QWidget* parent):QWidget(parent),dataStructure(dataStructure),coreComponent(cc){
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    if(coreComponent){
        QLabel* label= new QLabel("INFORMAZIONI COMPONENTE:");
        layout->addWidget(label);
        info = new componentInfo(*coreComponent);

        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(info);

        layout->addWidget(scrollArea);

        QPushButton* deleteButton = new QPushButton("ELIMINA COMPONENTE");
        layout->addWidget(deleteButton);
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(onDeleteButtonPressed()));
        connect(this,SIGNAL(deleteButtonClick()),parent,SLOT(onDeleteButtonPressed()));
    }
    else{
        QLabel* label = new QLabel("SELEZIONA UN COMPONENTE PER VISUALIZZARNE LE INFORMAZIONI");
        label->setWordWrap(true);
        layout->addWidget(label);
    }
}

void componentInfoBar::onDeleteButtonPressed(){
    emit this->deleteButtonClick();
}

void componentInfoBar::onUpdateInfo(component* coreComponent){
    info->updateInfo(*coreComponent);
}

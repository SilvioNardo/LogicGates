#include "sideBar.h"

sideBar::sideBar(twoDForwardList& dataStructure,bool isOnLeftSide,QWidget* parent,bool isShown,componentView* sc):QWidget(parent), dataStructure(dataStructure),isOnLeftSide(isOnLeftSide),isShown(isShown),showedComponentView(sc),showedCoreComponent((sc)?(sc->getCoreComponent()):(nullptr)){
    setMaximumWidth(shownBarWidth);
    setMinimumWidth(shownBarWidth);
    QHBoxLayout* horizzontalLayout = new QHBoxLayout(this);
    horizzontalLayout->setAlignment(Qt::AlignLeft);
    horizzontalLayout->setContentsMargins(0,0,0,0);
    arrowButton = new QPushButton();
    arrowButton->setMaximumWidth(20);
    arrowButton->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);

    if(isOnLeftSide){
        //left SideBar
        bar = new standardComponentsBar(dataStructure);
        connect(bar,SIGNAL(componentInfoPressed(component&)),this,SIGNAL(componentInfoPressed(component&)));
        horizzontalLayout->addWidget(bar);
        horizzontalLayout->addSpacing(10);
        if (isShown){
           arrowButton->setText(tr("<"));
        }
        else{
            arrowButton->setText(tr(">"));
        }
        horizzontalLayout->addWidget(arrowButton);
    }
    else{
        //right SideBar
        bar = new componentInfoBar(dataStructure,showedCoreComponent,this);
        connect(this,SIGNAL(updateInfo(component*)),bar,SLOT(onUpdateInfo(component*)));
        if(isShown){
            arrowButton->setText(tr(">"));
        }
        else{
            arrowButton->setText(tr("<"));
        }
        horizzontalLayout->addWidget(arrowButton);
        horizzontalLayout->addSpacing(-5);
        horizzontalLayout->addWidget(bar);
    }
    connect(arrowButton,SIGNAL(clicked()),this,SLOT(onArrowButtonPressed()));

    if(isShown == false){
        this->isShown = true;
        emit arrowButton->clicked();
    }
}

void sideBar::onArrowButtonPressed(){
    if(isShown){
        //deve chiudersi
        isShown = false;
        setMaximumWidth(hiddenBarWidth);
        setMinimumWidth(hiddenBarWidth);
        bar->hide();
        if(isOnLeftSide){
            arrowButton->setText(tr(">"));
        }
        else{
            arrowButton->setText(tr("<"));
        }
    }
    else{
        //deve aprirsi
        isShown = true;
        setMaximumWidth(shownBarWidth);
        setMinimumWidth(shownBarWidth);
        bar->show();
        if(isOnLeftSide){
            arrowButton->setText(tr("<"));
        }
        else{
            arrowButton->setText(tr(">"));
        }
    }
}

void sideBar::backSpaceClicked(){
    if(showedCoreComponent){
        onDeleteButtonPressed();
    }
}

void sideBar::onDeleteButtonPressed(){
    showedCoreComponent = nullptr;
    emit componentViewDelete(showedComponentView);
    showedComponentView = nullptr;
    auto newBar = new componentInfoBar(dataStructure,showedCoreComponent,this);
    QLayoutItem* oldLayout = this->layout()->replaceWidget(bar,newBar);
    delete bar;
    bar= newBar;
    delete oldLayout;
}

void sideBar::onComponentPressed(componentView& newCompView){
    component& newCoreComponent = *newCompView.getCoreComponent();
    if(showedCoreComponent != &newCoreComponent){
        showedComponentView = &newCompView;
        showedCoreComponent = &newCoreComponent;
        delete bar;
        bar = new componentInfoBar(dataStructure,&newCoreComponent,this);
        connect(this,SIGNAL(updateInfo(component*)),bar,SLOT(onUpdateInfo(component*)));
        this->layout()->addWidget(bar);
    }
}

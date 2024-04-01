#include "standardComponentsBar.h"

standardComponentsBar::standardComponentsBar(twoDForwardList& dataStructure,QWidget* parent):QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* lable= new QLabel("COMPONENTI STANDARD:",this);
    layout->addWidget(lable);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);

    QWidget* scrollAreaContainer = new QWidget();
    scrollAreaContainer->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
    QVBoxLayout* scrollAreaLayout = new QVBoxLayout();
    scrollAreaContainer->setLayout(scrollAreaLayout);

    auto standardNodePointer = dataStructure.getFirst();
    while(standardNodePointer){
        standardComponentInfo* componentInfo = new standardComponentInfo(*(standardNodePointer->coreComponent));
        connect(componentInfo,SIGNAL(onPressed(component&)),this,SIGNAL(componentInfoPressed(component&)));
        scrollAreaLayout->addWidget(componentInfo);
        standardNodePointer=standardNodePointer->nextStandardComponent;
    }
    scrollAreaLayout->addStretch();
    scrollArea->setWidget(scrollAreaContainer);
}

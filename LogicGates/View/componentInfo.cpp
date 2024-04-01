#include "componentInfo.h"

componentInfo::componentInfo(component& coreComponent, QWidget* parent): QWidget(parent), coreComponent(coreComponent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    componentNameLabel= new QLabel("NOME DEL COMPONENTE: " + QString::fromStdString(coreComponent.getName()));
    componentNameLabel->setWordWrap(true);
    layout->addWidget(componentNameLabel);

    componentDescriptionLabel= new QLabel("DESCRIZIONE DEL COMPONENTE: " + QString::fromStdString(coreComponent.getDescription()));
    componentDescriptionLabel->setWordWrap(true);
    layout->addWidget(componentDescriptionLabel);

    //info derivate: (in base al tipo dinamico)
    componentInfoVisitor visitor;
    coreComponent.accept(visitor);
    visitorWidget = visitor.getWidget();
    layout->addWidget(visitorWidget);

    layout->addStretch();
}

void componentInfo::updateInfo(component& coreComponent){
    componentInfoVisitor visitor;
    coreComponent.accept(visitor);
    QWidget* newVisitorWidget = visitor.getWidget();
    QLayoutItem* oldLayout = this->layout()->replaceWidget(visitorWidget,newVisitorWidget);
    delete visitorWidget;
    visitorWidget=newVisitorWidget;
    delete oldLayout;
}

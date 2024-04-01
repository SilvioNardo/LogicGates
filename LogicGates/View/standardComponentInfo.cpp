#include "standardComponentInfo.h"

standardComponentInfo::standardComponentInfo(component& coreComponent, QWidget* parent):QWidget(parent),coreComponent(coreComponent){
    setCursor(Qt::PointingHandCursor);
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* name = new QLabel("Nome: "+QString::fromStdString(coreComponent.getName()));
    layout->addWidget(name);
    QLabel* componentNumber = new QLabel("Numero del componente: "+QString::fromStdString(std::to_string(coreComponent.getComponentNumber())));
    layout->addWidget(componentNumber);
    QLabel* numberOfInputs = new QLabel("Numero di input: "+ QString::fromStdString(std::to_string(coreComponent.getNumberOfInputs())));
    layout->addWidget(numberOfInputs);
    QLabel* numberOfOutputs = new QLabel("Numero di output: "+ QString::fromStdString(std::to_string(coreComponent.getNumberOfOutputs())));
    layout->addWidget(numberOfOutputs);
    QLabel* description = new QLabel("Descrizione: "+QString::fromStdString(coreComponent.getDescription()));
    description->setWordWrap(true);
    layout->addWidget(description);
    layout->setSpacing(0);
}

void standardComponentInfo::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(0,5,width()-5, height()-7,3,3);
    QWidget::paintEvent(event);
}

void standardComponentInfo::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        setCursor(Qt::ClosedHandCursor);
        emit onPressed(coreComponent);
    }
    QWidget::mousePressEvent(event);
}

void standardComponentInfo::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        setCursor(Qt::PointingHandCursor);
    }
    QWidget::mouseReleaseEvent(event);
}

#include "componentInfoVisitor.h"

QWidget* componentInfoVisitor::getWidget(){
    return widget;
}

void componentInfoVisitor::visitLamp(lamp& l){
    QWidget* finalWidget= new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(finalWidget);
    layout->setContentsMargins(0,0,0,0);

    QLabel* instanceIdLabel= new QLabel("ID DEL COMPONENTE: " + QString::fromStdString(l.pairToString(l.getId())));
    instanceIdLabel->setWordWrap(true);
    layout->addWidget(instanceIdLabel);

    QLabel* instanceNameLabel= new QLabel("NOME DELL'ISTANZA DEL COMPONENTE: " + QString::fromStdString(l.getName()));
    instanceNameLabel->setWordWrap(true);
    layout->addWidget(instanceNameLabel);

    QLabel* instanceDescriptionLabel= new QLabel("DESCRIZIONE DELL'ISTANZA DEL COMPONENTE: " + QString::fromStdString(l.getDescription()));
    instanceDescriptionLabel->setWordWrap(true);
    layout->addWidget(instanceDescriptionLabel);

    QLabel* stateLabel= new QLabel("STATO DEL COMPONENTE: " + ((l.getState()) ? QString("Accesa") : QString("Spenta")));
    stateLabel->setWordWrap(true);
    layout->addWidget(stateLabel);

    auto pinConnected = l.getInput().front()->getPinConnected();
    QLabel* componentConnectedLabel= new QLabel();
    if(pinConnected.empty() == false){
        std::pair id = pinConnected.front()->getComponentConnected()->getId();
        componentConnectedLabel->setText("COMPONENTE CONNESSO: " + QString::fromStdString("id: " + l.pairToString(id)));
    }
    else{
        componentConnectedLabel->setText("COMPONENTE CONNESSO: Nessuno");

    }
    componentConnectedLabel->setWordWrap(true);
    layout->addWidget(componentConnectedLabel);

    widget = finalWidget;
}

void componentInfoVisitor::visitLogicGate(logicGate& lg){
    QWidget* finalWidget= new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(finalWidget);
    layout->setContentsMargins(0,0,0,0);

    QLabel* instanceIdLabel= new QLabel("ID DEL COMPONENTE: " + QString::fromStdString(lg.pairToString(lg.getId())));
    instanceIdLabel->setWordWrap(true);
    layout->addWidget(instanceIdLabel);

    QLabel* instanceNameLabel= new QLabel("NOME DELL'ISTANZA DEL COMPONENTE: " + QString::fromStdString(lg.getName()));
    instanceNameLabel->setWordWrap(true);
    layout->addWidget(instanceNameLabel);

    QLabel* instanceDescriptionLabel= new QLabel("DESCRIZIONE DELL'ISTANZA DEL COMPONENTE: " + QString::fromStdString(lg.getDescription()));
    instanceDescriptionLabel->setWordWrap(true);
    layout->addWidget(instanceDescriptionLabel);

    //truth table
    QLabel* truthTableLabel = new QLabel("TRUTH TABLE:");
    QTableWidget* truthTableWidget = new QTableWidget((pow(2,lg.getNumberOfInputs())),(lg.getNumberOfInputs() +lg.getNumberOfOutputs()));
    for(int row=0;row<truthTableWidget->rowCount();++row){
        for(int column= 0;column< truthTableWidget->columnCount();++column){
            QLabel* cellLabel = new QLabel(QString::fromStdString(std::to_string((lg.getTruthTable())[row][column])));
            truthTableWidget->setCellWidget(row,column,cellLabel);
        }
    }
    layout->addWidget(truthTableLabel);
    layout->addWidget(truthTableWidget);

    //component connected
    //input:
    std::string inputComponentsConnectedIdString;
    int pinNumber = 1;
    auto input = lg.getInput();
    for(auto it = input.begin(); it != input.end();++it){
        inputComponentsConnectedIdString.append("Pin numero " + std::to_string(pinNumber) + ": ");
        if(!((*it)->getPinConnected().empty())){
            std::pair id = (*it)->getPinConnected().front()->getComponentConnected()->getId();
            inputComponentsConnectedIdString.append(lg.pairToString(id)+"\n");
        }
        else{
            inputComponentsConnectedIdString.append("Nessuno\n");
        }
        ++pinNumber;
    }

    //output:
    std::string outputComponentsConnectedIdString;
    pinNumber = 1;
    auto output = lg.getOutput();
    for(auto it = output.begin();it != output.end();++it){
        outputComponentsConnectedIdString.append("Pin numero " + std::to_string(pinNumber) + ": ");
        if(!((*it)->getPinConnected().empty())){
            std::string pinOutputsConnected;
            auto pinConnected = (*it)->getPinConnected();
            for(auto pinIt = pinConnected.begin();pinIt != pinConnected.end();++pinIt){
                std::pair id = (*pinIt)->getComponentConnected()->getId();
                pinOutputsConnected.append(lg.pairToString(id)+"\n");
            }
            outputComponentsConnectedIdString.append(pinOutputsConnected);
        }
        else{
            outputComponentsConnectedIdString.append("Nessuno\n");
        }
        ++pinNumber;
    }

    QLabel* componentConnectedLabel= new QLabel("COMPONENTI CONNESSI:\nINPUT:\n" + QString::fromStdString(inputComponentsConnectedIdString) + "\nOUTPUT:\n" + QString::fromStdString( outputComponentsConnectedIdString));
    componentConnectedLabel->setWordWrap(true);
    layout->addWidget(componentConnectedLabel);

    widget = finalWidget;
}

void componentInfoVisitor::visitButton(button& b){
    QWidget* finalWidget= new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(finalWidget);
    layout->setContentsMargins(0,0,0,0);

    QLabel* instanceIdLabel= new QLabel("ID DEL COMPONENTE: " + QString::fromStdString(b.pairToString(b.getId())));
    instanceIdLabel->setWordWrap(true);
    layout->addWidget(instanceIdLabel);

    QLabel* instanceNameLabel= new QLabel("NOME DELL'ISTANZA DEL COMPONENTE: " + QString::fromStdString(b.getName()));
    instanceNameLabel->setWordWrap(true);
    layout->addWidget(instanceNameLabel);

    QLabel* instanceDescriptionLabel= new QLabel("DESCRIZIONE DELL'ISTANZA DEL COMPONENTE: " + QString::fromStdString(b.getDescription()));
    instanceDescriptionLabel->setWordWrap(true);
    layout->addWidget(instanceDescriptionLabel);

    QLabel* stateLabel= new QLabel("STATO DEL COMPONENTE: " + ((b.getIsPressed()) ? QString("Acceso") : QString("Spento")));
    stateLabel->setWordWrap(true);
    layout->addWidget(stateLabel);

    auto pinConnected = b.getOutput().front()->getPinConnected();
    std::string componentsConnectedIdString;
    if(!(pinConnected.empty())){
        for(auto it = pinConnected.begin();it != pinConnected.end();++it){
            componentsConnectedIdString.append((*it)->getComponentConnected()->printId());
        }
    }

    QLabel* componentConnectedLabel= new QLabel("COMPONENTI CONNESSI: " + (((!(pinConnected.empty()))) ? QString::fromStdString("id: " + componentsConnectedIdString) : QString("Nessuno")));
    componentConnectedLabel->setWordWrap(true);
    layout->addWidget(componentConnectedLabel);

    widget = finalWidget;
}

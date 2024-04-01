#include "dataPersistance.h"

dataPersistance::dataPersistance(twoDForwardList& dataStructure,std::string fileName):dataStructure(dataStructure),fileName(QString::fromStdString(fileName)){
}

void dataPersistance::standardComponentsFromJson(const QJsonObject &json){
    if (const QJsonValue v = json["instanceName"]; v.isString()){
             instanceName = v.toString();
    }

    if (const QJsonValue v = json["instanceDescription"]; v.isString()){
             instanceDescription = v.toString();
    }

    if (const QJsonValue v = json["componentName"]; v.isString()){
             componentName = v.toString();
    }

    if (const QJsonValue v = json["componentDescription"]; v.isString()){
             componentDescription = v.toString();
    }

    if (const QJsonValue v = json["type"]; v.isDouble()){
            int type = v.toInt();

            if(type==1){
                //bottone
                button* b = new button(dataStructure,instanceName.toStdString(),instanceDescription.toStdString());
                b->component::setName(componentName.toStdString());
                b->component::setDescription(componentDescription.toStdString());
            }
            else if(type==2){
                //lampadina
                lamp* l = new lamp(dataStructure,instanceName.toStdString(),instanceDescription.toStdString());
                l->component::setName(componentName.toStdString());
                l->component::setDescription(componentDescription.toStdString());
            }
            else if(type==3){
                //logicgate
                if (const QJsonValue v = json["inputNumber"]; v.isDouble()){
                         numberOfInputs = v.toInt();
                }

                if (const QJsonValue v = json["outputNumber"]; v.isDouble()){
                         numberOfOutputs = v.toInt();
                }

                if (const QJsonValue v = json["truthTable"]; v.isArray()) {
                     auto truthTableArray = v.toArray();
                     truthTable.clear();
                     for(auto row = truthTableArray.begin(); row != truthTableArray.end(); ++row){
                         if(row->isArray()) {
                             auto truthTableRow = row->toArray();
                             std::vector<bool> rows;
                             for(auto column = truthTableRow.begin(); column != truthTableRow.end(); ++column){
                                 if (column->isBool()){
                                    bool value = column->toBool();
                                    rows.push_back(value);
                                 }
                             }
                             truthTable.push_back(rows);
                         }
                     }
                }

                logicGate* lg = new logicGate(dataStructure,numberOfInputs,numberOfOutputs,truthTable,instanceName.toStdString(),instanceDescription.toStdString());
                lg->component::setName(componentName.toStdString());
                lg->component::setDescription(componentDescription.toStdString());
            }
    }
}

void dataPersistance::load(){
    QFile loadedFile(fileName);
    if (!loadedFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }
    else{
        QByteArray saveData = loadedFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        const QJsonObject& json = loadDoc.object();
        if (const QJsonValue v = json["standardComponents"]; v.isArray()) {
            const QJsonArray standardComponents = v.toArray();
            for (auto standardComponent = standardComponents.begin(); standardComponent != standardComponents.end(); ++standardComponent){
                standardComponentsFromJson(standardComponent->toObject());
            }
        }
    }
}

QJsonObject dataPersistance::standardComponentsToJson(){
    QJsonObject json;
    QJsonArray standardComponents;
    twoDForwardList::standardComponentNode* nodePointer = dataStructure.first;
    while(nodePointer != nullptr){
        standardComponents.append(nodePointer->coreComponent->toJson());
        nodePointer = nodePointer->nextStandardComponent;
    }
    json["standardComponents"] = standardComponents;
    return json;
}

void dataPersistance::save(){
    QFile loadedFile(fileName);
    if (!loadedFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }
    else{
        loadedFile.write(QJsonDocument(standardComponentsToJson()).toJson());
    }

}

void dataPersistance::setFileName(std::string fn){
    fileName = QString::fromStdString(fn);
}

void dataPersistance::setDataStructure(twoDForwardList& ds){
    dataStructure = ds;
}

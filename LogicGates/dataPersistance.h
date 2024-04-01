#ifndef DATAPERSISTANCE_H
#define DATAPERSISTANCE_H

#include <QJsonObject>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include "2dForwardList.h"
#include "button.h"
#include "lamp.h"
#include "logicGate.h"

class dataPersistance{
private:
    twoDForwardList& dataStructure;
    QString fileName;
    QString instanceName;
    QString instanceDescription;
    QString componentName;
    QString componentDescription;
    int numberOfInputs;
    int numberOfOutputs;
    std::vector<std::vector<bool>> truthTable;
public:
    dataPersistance(twoDForwardList& dataStructure,std::string fileName);
    void standardComponentsFromJson(const QJsonObject&);
    void load();
    QJsonObject standardComponentsToJson();
    void save();
    void setFileName(std::string fileName);
    void setDataStructure(twoDForwardList&);
};

#endif // DATAPERSISTANCE_H

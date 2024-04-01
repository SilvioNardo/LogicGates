#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <QWidget>
#include <QSizePolicy>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include "componentInfoVisitor.h"
#include "../component.h"
#include "componentObserverInterface.h"


class componentInfo: public QWidget{
    Q_OBJECT
private:
    component& coreComponent;
    QLabel* componentNameLabel;
    QLabel* componentDescriptionLabel;
    QWidget* visitorWidget;

public:
    componentInfo(component& coreComponent, QWidget* parent = 0);
    void updateInfo(component& coreComponent);
};

#endif // COMPONENTINFO_H

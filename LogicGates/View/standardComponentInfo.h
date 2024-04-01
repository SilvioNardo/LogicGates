#ifndef STANDARDCOMPONENTINFO_H
#define STANDARDCOMPONENTINFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QSizePolicy>
#include "../component.h"

class standardComponentInfo : public QWidget{
    Q_OBJECT
private:
    component& coreComponent;
public:
    standardComponentInfo(component& coreComponent, QWidget* parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
signals:
    void onPressed(component&);
};

#endif // STANDARDCOMPONENTINFO_H

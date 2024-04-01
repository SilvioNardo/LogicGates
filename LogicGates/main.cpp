#include <QApplication>
#include "2dForwardList.h"
#include "button.h"
#include "lamp.h"
#include "logicGate.h"
#include "View/mainwindow.h"
#include "dataPersistance.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    twoDForwardList dataStructure;
    dataPersistance saveFile(dataStructure,"savedComponents.json");
    saveFile.load();

    MainWindow main_window(dataStructure);
    main_window.resize(1024, 512);
    main_window.show();
    app.exec();

    saveFile.save();
}  
// nel caso vengano istanziati componenti dal main si raccomanda l'uso dello heap

#include "widget.h"
#include "mainscene.h"
#include "config.h"
#include <QApplication>
#include <QResource>
#include <iostream>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    QResource::registerResource(PATH);
    mainscene w;
    w.show();
    //w.startplay();
    return a.exec();
}

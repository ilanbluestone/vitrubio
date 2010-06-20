#include <QtGui/QApplication>
#include "mainwindow.h"

//Main del Proyecto
//Hola Cris, desde aca empezaremos a editar el proyecto

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

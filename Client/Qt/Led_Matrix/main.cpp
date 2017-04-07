#include "mainwindow.h"
#include <QApplication>


#include "ledsmatrix.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv)                                  ;

   QMainWindow *window    = new QMainWindow()                  ;
   QWidget *centralWidget = new QWidget(window)                ;

   LedsMatrix mymatrix(4,3, centralWidget) ;

   window->setWindowTitle(QString::fromUtf8("Leds Matrix"))    ;
   window->setCentralWidget(centralWidget)                     ;
   window->show()                                              ;
   return a.exec()                                             ;
}



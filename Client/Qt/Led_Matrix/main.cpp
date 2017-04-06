#include "mainwindow.h"
#include <QApplication>

#include <QGridLayout>
#include "MyButtonGroup.h"

#include "leds_matrix_tools.h"

#include <QListWidget>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv)                                  ;

   QMainWindow *window    = new QMainWindow()                  ;
   QWidget *centralWidget = new QWidget(window)                ;

   MyButtonGroup* group   = new MyButtonGroup(centralWidget)   ;

   window->setWindowTitle(QString::fromUtf8("Leds Matrix"))    ;
   window->setCentralWidget(centralWidget)                     ;
   window->show()                                              ;
   return a.exec()                                             ;
}

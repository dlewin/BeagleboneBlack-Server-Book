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
  //  QGridLayout *layout    = new QGridLayout(centralWidget)     ;

    QVBoxLayout *layout     = new QVBoxLayout(centralWidget)        ;
    QHBoxLayout *Hlayout    = new QHBoxLayout()                    ;
    QGridLayout *Glayout    = new QGridLayout()                 ;
    Glayout->setSpacing(0)                                      ;
    Hlayout->addStretch(1)                                      ;
    Hlayout->addLayout(Glayout)                                 ;
    Hlayout->addStretch(1)                                      ;
    layout->addLayout(Hlayout)                                  ;
    layout->addStretch(1)                                       ;
    MyButtonGroup* group   = new MyButtonGroup(centralWidget)   ;

    QPushButton *Load_Btn = new QPushButton("Load Patterns")             ;
    layout->addWidget(Load_Btn)                                 ;
    QObject::connect(Load_Btn, SIGNAL(released()), group, SLOT(Loadfile_click()));

    QPushButton *Save_Patt_Btn = new QPushButton("Save Current Pattern")             ;
    layout->addWidget(Save_Patt_Btn)                                 ;
    QObject::connect(Save_Patt_Btn, SIGNAL(released()), group, SLOT(Savefile_click()));

    QListWidget *Patterns_List = new QListWidget()              ;
    layout->addWidget(Patterns_List)                            ;

    QPushButton *Save_PatList_Btn = new QPushButton("Save Patterns list")             ;
    layout->addWidget(Save_PatList_Btn)                                 ;
    QObject::connect(Save_Patt_Btn, SIGNAL(released()), group, SLOT(Savefile_click())); // Changer le SLOT !!<<



    window->setWindowTitle(QString::fromUtf8("Leds Matrix"))    ;

   // layout->setHorizontalSpacing(1);
   // layout->setVerticalSpacing(1);
   group->Matx_dim = 4 ;
    centralWidget->setLayout(layout)                            ;

    group->Populate(Glayout, group )                            ;

    window->setCentralWidget(centralWidget)                     ;
    window->show()                                              ;
    return a.exec()                                             ;
}

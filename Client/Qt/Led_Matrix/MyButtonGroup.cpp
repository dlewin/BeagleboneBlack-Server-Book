#include "MyButtonGroup.h"
#include <QWidget>
#include <QColor>
#include <QFile>
#include <QListWidget>
#include <QDebug>



MyButtonGroup::MyButtonGroup(QWidget* parentWidget)
{
    this->setParent(parentWidget);

    //> ICI
    // Import depuis le main

    this->Matx_dim = 4 ;
    QVBoxLayout *layout     = new QVBoxLayout(parentWidget)        ;
    QHBoxLayout *Hlayout    = new QHBoxLayout()                    ;
    QGridLayout *Glayout    = new QGridLayout()                 ;
    Glayout->setSpacing(0)                                      ;
    Hlayout->addStretch(1)                                      ;
    Hlayout->addLayout(Glayout)                                 ;
    Hlayout->addStretch(1)                                      ;
    layout->addLayout(Hlayout)                                  ;
    layout->addStretch(1)                                       ;

    QPushButton *Load_Btn = new QPushButton("Load Patterns")             ;
    layout->addWidget(Load_Btn)                                 ;
    QObject::connect(Load_Btn, SIGNAL(released()), this, SLOT(Loadfile_click()));

    QPushButton *Save_Patt_Btn = new QPushButton("Save Current Pattern")             ;
    layout->addWidget(Save_Patt_Btn)                                 ;
    QObject::connect(Save_Patt_Btn, SIGNAL(released()), this, SLOT(Savefile_click()));

    QListWidget *Patterns_List = new QListWidget()              ;
    layout->addWidget(Patterns_List)                            ;

    QPushButton *Save_PatList_Btn = new QPushButton("Save Patterns list")             ;
    layout->addWidget(Save_PatList_Btn)                                 ;
    QObject::connect(Save_Patt_Btn, SIGNAL(released()), this, SLOT(Savefile_click())); // Changer le SLOT !!<<


    parentWidget->setLayout(layout)                            ;
    this->Populate(Glayout )                            ;
    // Fin d'Import depuis le main

    //connect buttonClicked signal to our custom slot 'buttonClicked'
    connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));

    Clear() ;
}



void MyButtonGroup::buttonClick(QAbstractButton* button)
{
    int new_ID = abs (this->id(button)) -2 ;  // Adaptation to compute the btn with the matrix

   unsigned short row = new_ID/4 ;
   unsigned short col = new_ID - (4 * row) ;

   qDebug() <<"Matrix index:" << new_ID << " row " << row << " col " << col ;

   unsigned short btn_value = this->Read_Matrix(row, col)  ;

   switch( btn_value )
    {
     case 0:    button->setStyleSheet("background-color:green;")    ;
       btn_value++ ;
        break ;
     case 1:    button->setStyleSheet("background-color:orange;");
       btn_value++ ;
        break ;
     case 2:    button->setStyleSheet("background-color:red;");
       btn_value++ ;
        break ;
     case 3:    button->setStyleSheet("background-color:grey;");
        btn_value = 0 ;
        break ;
    }
  this->Write_Matrix(row, col,btn_value );
}

void MyButtonGroup::Clear()
{
    Leds_Matrix.fill(0); // Init Matrix to 0
}

void MyButtonGroup::Savefile_click()
{
 Save_To_File("Led_Matrix.mtx") ;
 qDebug() << "Savefile_click" ;
}


void MyButtonGroup::Loadfile_click()
{
 Load_From_File("Led_Matrix.mtx") ;
 qDebug() << "Loadfile_click ." ;
}

int MyButtonGroup::Load_From_File(QString Filename)
{
    unsigned short i,j                          ;

    this->Clear()                               ;

    QFile File_Ptr(Filename)                    ;
    if (!File_Ptr.open( QIODevice::ReadOnly  ) )
        return 1                                ;

    //QDataStream out(&File_Ptr) ;
    QByteArray buffer = File_Ptr.readAll()      ;

    for ( i = 0; i < Matx_dim ; ++ i)
    {
     for ( j = 0; j < Matx_dim; ++j)
     {
      this->Write_Matrix( i,j, (unsigned short)buffer[i+j] );
//      qDebug() << i << j << "buffer[i+j]" << buffer[i+j]  ;
     }
    }

    File_Ptr.close();
    qDebug() << "Matrice lue:" << Leds_Matrix << "longueur"  << buffer.length() ;
    return 0 ;
}



int MyButtonGroup::Save_To_File(QString Filename)
{
 int val[20]={};
 unsigned short index ;
 Leds_Matrix.copyDataTo( val );

 QFile File_Ptr(Filename) ;
 if (!File_Ptr.open(QIODevice::WriteOnly ) )
     return 1 ;

  QDataStream out(&File_Ptr) ;
 //QTextStream out(&File_Ptr) ;

 for ( index=0; index<20;index++)
 {
   out << (unsigned char)(val[index])   ;
 }


 File_Ptr.close();
 return 0 ;
}



unsigned short MyButtonGroup::Read_Matrix(unsigned short x, unsigned short y)
{
    return Leds_Matrix(x,y);
}

void MyButtonGroup::Write_Matrix(unsigned short x, unsigned short y, unsigned short value)
{
    Leds_Matrix(x,y) = value    ;
}

//void MyButtonGroup::Populate(QGridLayout *layout, MyButtonGroup* group )
void MyButtonGroup::Populate(QGridLayout *layout )
{
    const int rows =8, columns = 8                             ;

    for (int i = 0; i < rows; ++ i)
    {
     for (int j = 0; j < columns; ++j)
     {
      QString index = QStringLiteral("(%1,%2)").arg(i).arg(j)   ;
      //QPushButton* btn = new QPushButton(index)                 ;
      QPushButton* btn = new QPushButton("-")                 ;
      btn->setFixedWidth(20);
     // layout->setColumnMinimumWidth(j,2);

   //   btn->setFlat(true);

      btn->setStyleSheet("background-color:grey;")              ;
      layout->addWidget(btn,i,j)                                ;

      this->addButton(btn)                              ;
      //group->addButton(btn)                              ;
     }
    }
}

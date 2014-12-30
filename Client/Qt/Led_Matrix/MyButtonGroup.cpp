#include "MyButtonGroup.h"
#include <QWidget>
#include <QColor>
#include <QFile>
#include <QListWidget>
#include <QVector>
#include <QDebug>
#include <QByteArray>


MyButtonGroup::MyButtonGroup(QWidget* parentWidget)
{
    this->setParent(parentWidget)                                                       ;

    this->Matrix_Ba.resize(64);
    this->Matx_dim = 8                                                                  ;

    QVBoxLayout *layout     = new QVBoxLayout(parentWidget)                             ;
    QHBoxLayout *Hlayout    = new QHBoxLayout()                                         ;
    QGridLayout *Glayout    = new QGridLayout()                                         ;
    Glayout->setSpacing(0)                                                              ;
    Hlayout->addStretch(1)                                                              ;
    Hlayout->addLayout(Glayout)                                                         ;
    Hlayout->addStretch(1)                                                              ;
    layout->addLayout(Hlayout)                                                          ;
    layout->addStretch(1)                                                               ;

    QPushButton *Send_Pattern = new QPushButton("Send Pattern")                            ;
    layout->addWidget(Send_Pattern)                                                         ;
    QObject::connect(Send_Pattern, SIGNAL(released()), this, SLOT(Send_Pattern_click()))        ;

    QPushButton *Load_Btn = new QPushButton("Load Patterns")                            ;
    layout->addWidget(Load_Btn)                                                         ;
    QObject::connect(Load_Btn, SIGNAL(released()), this, SLOT(Loadfile_click()))        ;

    QPushButton *Save_Patt_Btn = new QPushButton("Save Current Pattern")                ;
    layout->addWidget(Save_Patt_Btn)                                                    ;
    QObject::connect(Save_Patt_Btn, SIGNAL(released()), this, SLOT(Savefile_click()))   ;

    QListWidget *Patterns_List = new QListWidget()                                      ;
    layout->addWidget(Patterns_List)                                                    ;

  /*  QPushButton *Save_PatList_Btn = new QPushButton("Save Patterns list")               ;
    layout->addWidget(Save_PatList_Btn)                                                 ;
    QObject::connect(Save_Patt_Btn, SIGNAL(released()), this, SLOT(Savefile_click()))   ; // TODO : Changer le SLOT !!<<<<
*/
    parentWidget->setLayout(layout)                                                     ;
    this->Populate(Glayout )                                                            ;

    //connect buttonClicked signal to our custom slot 'buttonClicked'
    connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));

    Clear() ;

}

void MyButtonGroup::buttonClick(QAbstractButton* button)
{
    int new_ID = abs (this->id(button)) -2 ;  // Adaptation to compute the btn with the matrix

   int row = new_ID/8 ;
   int col = new_ID - (8 * row) ;

   //unsigned short btn_value = this->Read_Matrix(row, col)  ;
   unsigned short btn_value = this->Read_Matrix(new_ID)  ;

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
 // this->Write_Matrix(row, col,btn_value );
  Write_Matrix(new_ID, btn_value) ;
}

void MyButtonGroup::Clear()
{
    Leds_Matrix.fill(0); // Init Matrix to 0
}


/*  TODO :
 1/ the data to be sent is made of x,y and a color attribute
 2/ The server must be modified as the 4 1st bytes are 0x00 0x00 0x00 0x40 ->which represent 64, the size of the ByteArray
 3/ Carefull Matrix must be filled before send it
*/


void MyButtonGroup::Send_Pattern_click()
{
    unsigned short btn_value, i;
    socket = new QTcpSocket(this);
    int row, col ;
    socket->connectToHost("google.com",80); // change to BBB server address/port

  //  if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        //send the current matrix to serverS
        for (i=0;i < Matrix_Ba.size(); i++ )
        {
              // Adaptation to compute the btn with the matrix
            row = i/8 ;
            col = i - (8 * row) ;
       //  socket->write(row, col, Matrix_Ba[i] ) ;
        }

    //    socket->write("hello server\r\n\r\n\r\n\r\n");

        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

        qDebug() << socket->readAll();

        socket->close();
    }
    //else
    {
        qDebug() << "Not Connected!";
    }
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
    //unsigned short i,j                          ;
    this->Clear()                               ;

    QFile File_Ptr(Filename)                    ;
    if (!File_Ptr.open( QIODevice::ReadOnly  ) )
        return 1                                ;

    this->Matrix_Ba = File_Ptr.readAll()      ;

/*    QByteArray buffer = File_Ptr.readAll()      ;

    for ( i = 0; i < Matx_dim ; i++)
    {
     for ( j = 0; j < Matx_dim; j++)
     {
      this->Write_Matrix( i,j, (unsigned short)buffer[i+j] );
      qDebug() << i << j << buffer[i+j]  ;
     }
    }
*/
    File_Ptr.close();
    return 0 ;
}


void MyButtonGroup::Write_Matrix(unsigned short Index, unsigned short Value)
{ 
 this->Matrix_Ba[Index] = Value ;
    //   Leds_Matrix(x,y) = value    ;
}

/* http://doc.qt.io/qt-5/containers.html#java-style-iterators */

/* Work as is but is not sufficient.
At the end we'll need a list of matrices for patterns saving purpose.
In that end, using a list of QByteArray list is the best to do :
http://doc.qt.io/qt-5/qbytearraylist.html#details
http://www.qtcentre.org/threads/35541-split-QByteArray?highlight=QByteArray */

int MyButtonGroup::Save_To_File(QString Filename)
{
    //int val[64]={};
    //unsigned short index ;
    QFile File_Ptr(Filename) ;
    QDataStream out(&File_Ptr) ;

 out.setVersion(QDataStream::Qt_5_3);

 if (!File_Ptr.open(QIODevice::WriteOnly ) )
 {
    qDebug() << "Issue with file save"  ;
    return 1 ;
 }

/* OK fonctinne ici mais mieux avec list ou Qbytearraylist
 Leds_Matrix.copyDataTo( val );
 for ( index=0; index<64;index++)
 {
   out << (val[index])   ;
 }*/

 // Nouveau Test  :

 out << this->Matrix_Ba ;

  File_Ptr.close();
  return 0 ;

}

//unsigned short MyButtonGroup::Read_Matrix(unsigned short x, unsigned short y)
unsigned short MyButtonGroup::Read_Matrix(unsigned short Index)
{
  //  return Leds_Matrix(x,y);
    return Matrix_Ba[Index] ;
}

void MyButtonGroup::Populate(QGridLayout *layout )
{
    const int rows = this->Matx_dim, columns = this->Matx_dim                             ;

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

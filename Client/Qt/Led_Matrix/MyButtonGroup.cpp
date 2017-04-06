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

    QPushButton *Send_Pattern = new QPushButton("Send Pattern")                         ;
    layout->addWidget(Send_Pattern)                                                     ;
    QObject::connect(Send_Pattern, SIGNAL(released()), this, SLOT(Send_Pattern_click() )) ;

    QPushButton *Load_Btn = new QPushButton("Load Patterns")                            ;
    layout->addWidget(Load_Btn)                                                         ;
    QObject::connect(Load_Btn, SIGNAL(released()), this, SLOT(Loadfile_click() ))       ;

    QPushButton *Save_Patt_Btn = new QPushButton("Save Current Pattern")                ;
    layout->addWidget(Save_Patt_Btn)                                                    ;
    QObject::connect(Save_Patt_Btn, SIGNAL(released()), this, SLOT( Save_Pattern_click() ))   ;

    QListWidget *Patterns_List = new QListWidget()                                      ;
    layout->addWidget(Patterns_List)                                                    ;

    QPushButton *Save_List_Btn = new QPushButton("Save Patterns list")               ;
    layout->addWidget(Save_List_Btn)                                                 ;
    QObject::connect(Save_List_Btn, SIGNAL(released()), this, SLOT( Savefile_click() )) ;

    parentWidget->setLayout(layout)                                                     ;
    this->Populate(Glayout )                                                            ;

    //connect buttonClicked signal to our custom slot 'buttonClicked'
    connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));

    Clear() ;

}

void MyButtonGroup::buttonClick(QAbstractButton* button)
{
   int new_ID = abs (this->id(button)) -2 ;  // Adaptation to compute the btn with the matrix

   QChar  Btn_Color = Current_Pattern[new_ID]               ;

   if (Btn_Color == '0')
   {
       button->setStyleSheet("background-color:green;")     ;
       Btn_Color ='1'                                       ;
   }
   else if (Btn_Color == '1')
   {
       button->setStyleSheet("background-color:orange;")    ;
       Btn_Color ='2'                                       ;
   }
   else if (Btn_Color == '2')
   {
       button->setStyleSheet("background-color:red;")       ;
       Btn_Color ='3'                                       ;
   }
   else
   {
       button->setStyleSheet("background-color:grey;")      ;
       Btn_Color ='0'                                       ;
   }

   Write_Matrix(new_ID, Btn_Color)                          ;
}

/* Initiate the matrix with "off" value */

void MyButtonGroup::Clear()
{
      // Init Matrix to 0
  for (int i = 0; i < ( Matx_dim * Matx_dim) ; ++i)
      Current_Pattern[i] = QChar('0') ;

  Matrix_SL.clear();
}

///TODO : no need to overload the tcp data.
/// The best thing to do is to compare the current led(x,y) with the one sent previously :
/// if there is no change : don't send anything

void MyButtonGroup::Send_Pattern_click()
{
    socket = new QTcpSocket(this);
    int row, col ;
    QString Tosend ;

    socket->connectToHost("localhost",8000); // change to BBB server address/port

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        foreach (QString QSvalue, Matrix_SL)
        {
            for ( unsigned short i=0; i < ( Matx_dim * Matx_dim); i++ )
            {
                row = i/8                                                                ; // replace with Matx_dim
                col = i - (8 * row)                                                      ;
                //QSvalue = javaStyleIterator.next().toLocal8Bit().constData()   ;
                Tosend = QString::number (row ) + QString::number(col) + QSvalue[i]      ;
                socket->write( Tosend.toLatin1() )                                       ;
                qDebug() << "Sending:"<< i <<" " << Tosend.toLatin1()                    ;
            }
        }
        socket->close();
    }
    else         qDebug() << "Not Connected!"                                           ;
}


void MyButtonGroup::Savefile_click()
{
 Save_To_File("Led_Matrix.mtx") ;
}

void MyButtonGroup::Loadfile_click()
{
 Load_From_File("Led_Matrix.mtx") ;
}

int MyButtonGroup::Load_From_File(QString Filename)
{
    //unsigned short i,j                          ;
    this->Clear()                               ;

    QFile File_Ptr(Filename)                    ;
    if (!File_Ptr.open( QIODevice::ReadOnly | QFile::Text ) )
    {
      qDebug() << "error opening " << Filename << endl      ;
      return EXIT_FAILURE;                                  ;
    }
    else
    {
      QTextStream In_Stream( &File_Ptr );
      while ( !In_Stream.atEnd() )
        Matrix_SL += In_Stream.readLine();
    }

    qDebug() << "Loadfromfile got:" << Matrix_SL ;

        // read data
    File_Ptr.close();
    return 0 ;
}


void MyButtonGroup::Write_Matrix(unsigned short Index, QChar Color_Value )
{ 
 Current_Pattern[Index] =  Color_Value ;
}


void MyButtonGroup::Save_Pattern_click()
{
  Matrix_SL << Current_Pattern  ;
  qDebug() << "Current Pattern:" << Current_Pattern << endl ;
  qDebug() << "StringList :" << Matrix_SL << endl ;
}

/// TODO
/// Using a list of QByteArray list is the best to do :
/// doc.qt.io/qt-5/qbytearraylist.html#details
/// www.qtcentre.org/threads/35541-split-QByteArray?highlight=QByteArray


int MyButtonGroup::Save_To_File(QString Filename)
{
  QFile File_Out(Filename);
  if (File_Out.open(QFile::WriteOnly | QFile::Text))
  {
    QTextStream Out_Stream( &File_Out );

    foreach(QString itm, Matrix_SL)
        Out_Stream << itm ;
  }
  else
  {
    qDebug() << "error opening " << Filename << endl;
    return EXIT_FAILURE;
  }
  File_Out.close();

  return 0 ;
}


QString MyButtonGroup::Read_Matrix(unsigned short Index)
{
    return Matrix_SL[Index] ;
}


void MyButtonGroup::Populate(QGridLayout *layout )
{
    const int rows =8, columns = 8                             ;

    for (int i = 0; i < rows; ++ i)
    {
     for (int j = 0; j < columns; ++j)
     {
      QString index = QStringLiteral("(%1,%2)").arg(i).arg(j)   ;
      QPushButton* btn = new QPushButton("-")                 ;
      btn->setFixedWidth(20);
      btn->setStyleSheet("background-color:grey;")              ;
      layout->addWidget(btn,i,j)                                ;

      this->addButton(btn)                              ;
     }
    }
}

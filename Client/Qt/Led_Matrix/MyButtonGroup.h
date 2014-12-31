#ifndef MYBUTTONGROUP_H
#define MYBUTTONGROUP_H


#include <QButtonGroup>
#include <QPushButton>
#include <QMessageBox>
#include <QGenericMatrix>
#include <QGridLayout>
#include <QTcpSocket>


//Derived Class from QButtonGroup
class MyButtonGroup: public QButtonGroup
{
  Q_OBJECT  
  private :
  //  QGenericMatrix<8,8, int> Leds_Matrix                                           ;
  //  QByteArray  Matrix_Ba                                                          ;
    QStringList Matrix_SL                                                           ;
    QString     Current_Pattern                                                     ;
    QTcpSocket  *socket                                                             ;
  public:
    int Matx_dim ;
    QString Read_Matrix(unsigned short Index)                 ;
    void Write_Matrix(unsigned short Index, QChar Color_Value ) ;
    void Populate(QGridLayout *layout )                       ;
    void Clear()                                                                    ;
    int Save_To_File(QString Filename)                                              ;
    int Load_From_File(QString Filename)                                            ;
    void Send_Pattern()                ;

    MyButtonGroup(QWidget* parent)                                                  ;
  /*  {
      this->setParent(parent);

      //connect buttonClicked signal to our custom slot 'buttonClick'
      connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));
      Clear() ;
    };*/

    ~ MyButtonGroup(){} ;

  public slots:
    //Slot that is called when one of buttons in QButtonGroup is clicked
    void buttonClick(QAbstractButton* button) ;
    void Loadfile_click() ;
    void Savefile_click() ;
    void Send_Pattern_click() ;
    void Save_Pattern_click() ;
};

#endif // MYBUTTONGROUP_H

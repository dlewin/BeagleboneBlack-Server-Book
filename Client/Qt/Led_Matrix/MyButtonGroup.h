#ifndef MYBUTTONGROUP_H
#define MYBUTTONGROUP_H


#include <QButtonGroup>
#include <QPushButton>
#include <QMessageBox>
#include <QGenericMatrix>
#include <QGridLayout>

//Derived Class from QButtonGroup
class MyButtonGroup: public QButtonGroup
{
  Q_OBJECT  
  private :
    QGenericMatrix<8,8,int> Leds_Matrix                                             ;
  public:
    int Matx_dim ;
    unsigned short Read_Matrix( unsigned short x, unsigned short y)                 ;
    void Write_Matrix( unsigned short x, unsigned short y, unsigned short value)    ;
    void Populate(QGridLayout *layout )                       ;
    void Clear()                                                                    ;
    int Save_To_File(QString Filename)                                              ;
    int Load_From_File(QString Filename)                                            ;

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
};

#endif // MYBUTTONGROUP_H

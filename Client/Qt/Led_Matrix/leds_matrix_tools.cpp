#include "leds_matrix_tools.h"
#include <QGenericMatrix>
#include <QGridLayout>
#include "MyButtonGroup.h"
#include <QPushButton>
#include <QDebug>

// Retourne la nouvelle matrice créee au main

Leds_Matrix_Tools::Leds_Matrix_Tools()
{
    Clear() ;
}


void Leds_Matrix_Tools::Populate(QGridLayout *layout, MyButtonGroup* group )
{
    const int rows = 4, columns = 4                             ;
    for (int i = 0; i < rows; ++ i)
    {
     for (int j = 0; j < columns; ++j)
     {
      QString index = QStringLiteral("(%1,%2)").arg(i).arg(j)   ;
      QPushButton* btn = new QPushButton(index)                 ;
      btn->setStyleSheet("background-color:grey;")              ;
      layout->addWidget(btn,i,j)                                ;
      group->addButton(btn)                                     ;
     }
    }
}



void Leds_Matrix_Tools::Write_Matrix(unsigned short x, unsigned short y, unsigned short value)
{
    Leds_Matrix(x,y) = value ;
    qDebug() << Leds_Matrix ;
}

void Leds_Matrix_Tools::Clear()
{
    Leds_Matrix.fill(0); // Init Matrix to 0
}

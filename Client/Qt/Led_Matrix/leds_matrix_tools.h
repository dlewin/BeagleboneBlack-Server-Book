#ifndef LEDS_MATRIX_TOOLS_H
#define LEDS_MATRIX_TOOLS_H
#include <QGridLayout>
#include "MyButtonGroup.h"
#include <QGenericMatrix>


class Leds_Matrix_Tools
{
public:
    Leds_Matrix_Tools(QWidget *parent);
    void Write_Matrix( unsigned short x, unsigned short y, unsigned short value);
    void Populate(QGridLayout *layout, MyButtonGroup* group );
    void Clear() ;
private:
    QGenericMatrix<4,4,int> Leds_Matrix ;
};

#endif // LEDS_MATRIX_TOOLS_H

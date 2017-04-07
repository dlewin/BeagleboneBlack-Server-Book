#include "ledsmatrix.h"
#include <QGridLayout>
#include "MyButtonGroup.h"

#include <QListWidget>

LedsMatrix::LedsMatrix(int Matrix_size, int Led_colors, QWidget *centralWidget)
{
    // Create the Matrix that will holds all the transformation operations
    // There is no graphical representation of it
 QImage MainMatrix(Matrix_size,Matrix_size,QImage::Format_Indexed8);

    // Let's create the HMI that accepts click as input and also represent the MainMatrix states
 MyButtonGroup* group   = new MyButtonGroup(centralWidget)   ;
}

void LedsMatrix::Clear()
{
   MainMatrix.fill(0);
}

void LedsMatrix::Fill()
{
   MainMatrix.fill(1);
}

/*

    myMatrix.fill(0); to turn everything off.
    Point: myMatrix.setPixel(0,0,1);
    Line(1): for(int i=0;i<myMatrix.width();++i) myMatrix.setPixel(0,i,1);
    Column(1): for(int i=0;i<myMatrix.height();++i) myMatrix.setPixel(i,0,1);
    Border: for(int i=0;i<myMatrix.width();++i) {myMatrix.setPixel(0,i,1); myMatrix.setPixel(myMatrix.height()-1,i,1);} for(int i=0;i<myMatrix.height();++i) {myMatrix.setPixel(i,0,1); myMatrix.setPixel(i,myMatrix.width()-1,1);}
    Column Shift(1): myMatrix=myMatrix.transformed(QTransform().translate(1,0));
    Column Shift(-1): myMatrix=myMatrix.transformed(QTransform().translate(-1,0));
    Line Shift(1): myMatrix=myMatrix.transformed(QTransform().translate(0,1));
    Line Shift(-1): myMatrix=myMatrix.transformed(QTransform().translate(0,-1));
    Rotate(1): myMatrix=myMatrix.transformed(QTransform().rotate(270));
    Rotate(-1): myMatrix=myMatrix.transformed(QTransform().rotate(90));
    Invert: myMatrix.invertPixels();


*/


LedsMatrix::~LedsMatrix()
{
}

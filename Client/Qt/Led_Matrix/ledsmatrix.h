#ifndef LEDSMATRIX_H
#define LEDSMATRIX_H
#include <QImage>

class LedsMatrix
{
private:
    int Matrix_size;
    int Led_colors ;
    QImage MainMatrix ;

public:
    LedsMatrix(int Matrix_size, int Led_colors , QWidget *centralWidget);
    ~LedsMatrix();
    void Clear(void);
    void Fill(void);
    void SetPoint(int, int, int);
    void SetLine(int,int);
    void SetColumn(int, int);
    void SetBorder();
    void ColumnShift(int) ;
    void LineShift(int);
    void Rotate(int);
    void Invert(void);
};

#endif // LEDSMATRIX_H

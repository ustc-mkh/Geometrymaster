#ifndef FUNCTION_H
#define FUNCTION_H
#include"config.h"
#include<QPixmap>
int ID(const int &x){
    return x<0?(x+1)/CUBE_L-1:x/CUBE_L;
}
int pre(const int &x){
    return ID(x)*CUBE_L;
}
int sub(const int &x){
    return ID(x)*CUBE_L+CUBE_L;
}
int ID2(const double &x){
    if(x>=0)return ID(int(x));
    else if(pre(int(x))>x)return ID(int(x))-1;
    else return ID(int(x));
}
int pre2(const double &x){
    return ID2(x)*CUBE_L;
}
int sub2(const double &x){
    return ID2(x)*CUBE_L+CUBE_L;
}
QPixmap mirrorpix(const QPixmap &P,int x,int y){
    QImage q;
    q=P.toImage();
    q=q.mirrored(x,y);
    return QPixmap::fromImage(q);
}
#endif // FUNCTION_H

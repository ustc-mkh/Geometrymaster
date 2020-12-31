#ifndef BULLET_H
#define BULLET_H
#include<QPixmap>

class bullet{
public:
    bullet(double xx=0,double yy=0,double vxx=0,double vyy=0,int n=1,int time=0);
public:
    double vx,vy,x,y;
    int time,now,del,kind;
    QRect rect;
};

#endif // BULLET_H

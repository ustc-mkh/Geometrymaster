#ifndef MONSTER1_H
#define MONSTER1_H
#include<QPixmap>
#include<QRect>

class monster1
{
public:
    monster1(int xx=0,int yy=0,int drxx=1);
public:
    int drx,x,y,index,del;
    QRect rect;
};

#endif // MONSTER1_H

#ifndef MONSTER2_H
#define MONSTER2_H
#include<QRect>

class monster2{
public:
    monster2(int xx=0,int yy=0,int drxx=0,int vv=0);
public:
    int x,y,drx,v,del;
    QRect rect1,rect2;
};

#endif // MONSTER2_H

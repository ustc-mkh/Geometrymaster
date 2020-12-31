#ifndef BUTTON_H
#define BUTTON_H
#include<QPixmap>
#include<QRect>
#include "config.h"

class button{
public:
    button(int xx=0,int yy=0,int drxx=1,int kind=0);
public:
    int x,y,drx,type,open;
    QRect rect;
    std::vector<pii > arr;
};

#endif // BUTTON_H

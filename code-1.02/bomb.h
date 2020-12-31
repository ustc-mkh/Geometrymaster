#ifndef BOMB_H
#define BOMB_H
#include<QPixmap>

class bomb{
public:
    bomb(int xx,int yy);
    void update();
public:
    int x,y,w,h,index,del;
};

#endif // BOMB_H

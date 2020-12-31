#ifndef CUBE_H
#define CUBE_H
#include<QPixmap>


class cube{
public:
    cube(int xx=0,int yy=0);
    bool operator <(const cube &b)const {
        return x<b.x||(x==b.x&&y<b.y);
    }
public:
    int x,y;
};

#endif // CUBE_H

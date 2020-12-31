#ifndef ROLE_H
#define ROLE_H

#include<QPixmap>
#include<QVector>
#include<QKeyEvent>
class role
{
public:
    role();
    void act(int Direction);
    void stop_act();
    void jump();
    void init();
public:
    int x,y,move,drx,v,vy,falling,gun_x,gun_y,del;
    QPixmap now,stop;
    QVector<QPixmap> pix;
    QRect rect;
};

#endif // ROLE_H

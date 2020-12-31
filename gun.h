#ifndef GUN_H
#define GUN_H

#include <QPixmap>
class gun
{
public:
    gun();
    void act(int x);
public:
    int angle,lenth,v,time;
    QPixmap gunpix;
};

#endif // GUN_H

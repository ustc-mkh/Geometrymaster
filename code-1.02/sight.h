#ifndef SIGHT_H
#define SIGHT_H
#include"role.h"


class sight{
public:
    sight();
    void update(const role &A);
public:
    int x,y,left,right,up,down;
};

#endif // SIGHT_H

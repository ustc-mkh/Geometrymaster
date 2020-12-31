#include "monster1.h"
#include "config.h"

monster1::monster1(int xx,int yy,int drxx){
    x=xx;
    y=yy;
    drx=drxx;
    index=del=0;
    rect.setWidth(MONSTER1_WIDTH);
    rect.setHeight(MONSTER1_HEIGHT/2);
    rect.moveTo(x,y);
}

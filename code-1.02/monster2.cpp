#include "monster2.h"
#include "config.h"

monster2::monster2(int xx,int yy,int drxx,int vv){
    x=xx;
    y=yy;
    drx=drxx;
    v=vv;
    del=0;
    rect1.setWidth(MONSTER2_FRONT);
    rect1.setHeight(MONSTER2_HEIGHT);
    rect2.setWidth(MONSTER2_WIDTH-MONSTER2_FRONT);
    rect2.setHeight(MONSTER2_HEIGHT2);
    if(drx==1){
        rect1.moveTo(x+MONSTER2_WIDTH-MONSTER2_FRONT,y);
        rect2.moveTo(x,y+MONSTER2_HEIGHT-MONSTER2_HEIGHT2);
    }
    else{
        rect1.moveTo(x,y);
        rect2.moveTo(x+MONSTER2_FRONT,y+MONSTER2_HEIGHT-MONSTER2_HEIGHT2);
    }
}

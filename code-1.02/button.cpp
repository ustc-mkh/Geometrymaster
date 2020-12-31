#include "button.h"
#include "config.h"

button::button(int xx,int yy,int drxx,int kind){
    x=xx;
    y=yy;
    drx=drxx;
    type=kind;
    open=0;
    rect.setWidth(13);
    rect.setHeight(31);
    if(drx==-1)rect.moveTo(x,y+14);
    else rect.moveTo(x+29,y+14);
}

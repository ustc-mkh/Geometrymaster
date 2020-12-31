#include "bomb.h"
#include "config.h"

bomb::bomb(int xx,int yy){
    x=xx;
    y=yy;
    index=w=del=h=0;
}
void bomb::update(){
    if(index==16){
        del=1;
        return;
    }
    index++;
    w+=BOMB_WIDTH/16;
    h+=BOMB_HEIGHT/16;
}

#include "gun.h"
#include "config.h"

gun::gun(){
    gunpix.load(GUN_PATH);
    angle=0;
    v=10;
    time=200;
}
void gun::act(int x){
    if(x==1){
        if(angle<=25)angle+=5;
    }
    else{
        if(angle>=-70)angle-=5;
    }
}

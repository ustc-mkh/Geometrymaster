#include "role.h"
#include "config.h"

role::role(){
    gun_x=ROLE_WIDTH-60;
    gun_y=20;
    rect.setWidth(ROLE_WIDTH/3);
    rect.setHeight(ROLE_HEIGHT);
    for(int i=1;i<=ROLE_MAX;i++){
        QString str=QString(ROLE_PATH).arg(i);
        pix.push_back(QPixmap(str));
    }
    stop.load(ROLE_STOP_PATH);
    init();
}
void role::init(){
    del=0;
    x=y=vy=move=v=0;
    falling=1;
    drx=1;
    now=stop;
    rect.moveTo(x+ROLE_WIDTH/3,y);
}
void role::act(int Direction){
    move=1;
    drx=Direction;
    v=ROLE_V*drx;
}
void role::stop_act(){
    move=0;
    v=0;
}
void role::jump(){
    if(falling)return;
    vy=VY0;
    falling=1;
}

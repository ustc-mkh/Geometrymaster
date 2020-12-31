#include "bullet.h"
#include "config.h"
bullet::bullet(double xx,double yy,double vxx,double vyy,int n,int T){
    x=xx;
    y=yy;
    vx=vxx;
    vy=vyy;
    time=T;
    now=del=0;
    kind=n;
    rect.setWidth(24);
    rect.setHeight(24);
    rect.moveTo(int(x),int(y));
}

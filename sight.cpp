#include "sight.h"

sight::sight(){
    x=y=0;
    left=200;
    right=1140;
    up=450;
    down=610;
}
void sight::update(const role &A){
    if(A.x-x<left)x=A.x-left;
    else if(A.x-x>right)x=A.x-right;
    if(A.y-y>down)y=A.y-down;
    else if(A.y-y<up)y=A.y-up;
}

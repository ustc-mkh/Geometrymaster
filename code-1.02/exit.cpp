#include "exit.h"
#include "config.h"

exit::exit(){
    open=0;
    x=y=0;
    rect.setWidth(59);
    rect.setHeight(95);
    rect.moveTo(x,y);
    pix.load(EXIT_PATH);
}

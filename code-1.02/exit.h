#ifndef EXIT_H
#define EXIT_H
#include <QRect>
#include <QPixmap>

class exit{
public:
    exit();
public:
    QRect rect;
    QPixmap pix;
    int open,x,y;
};

#endif // EXIT_H

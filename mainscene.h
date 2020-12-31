#ifndef MAINSCENE_H
#define MAINSCENE_H


#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QPixmap>
#include <bits/stdc++.h>
#include "role.h"
#include "gun.h"
#include "bullet.h"
#include "bomb.h"
#include "dialog.h"
#include "monster1.h"
#include "monster2.h"
#include "monster3.h"
#include "button.h"
#include "config.h"
#include "exit.h"
#include "sight.h"

class mainscene : public QWidget
{
    Q_OBJECT

public:
    mainscene(QWidget *parent = 0);
    ~mainscene();
    void startplay();
    void updatePosition();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void updatehero();
    void shoot();
    void updatebullet(bullet &B);
    void over();
    void destroyhero();
    void loadmap(int x);
    void updatemonster1();
    void updatemonster2();
    void updatemonster3();
    void updatebomb();
    void colide();
    void clearall();
protected slots:
    void choose();
    void load();
    void save();
public:
    QPushButton *optionbutton, *loadbutton, *savebutton,*statementbutton, *choosebutton;
    QTimer *m_Timer, *m_Timer2;
    dialog* dialogwindow;
    role hero;
    gun herogun;
    std::set<pii >cube_arr;
    std::vector<bullet> bullet_arr;
    std::vector<bomb> bomb_arr;
    std::vector<monster1> monster1_arr;
    std::vector<monster2> monster2_arr;
    std::vector<monster3> monster3_arr;
    std::vector<button> button_arr;
    int pass_number,now;
    bool running;
    QPixmap cubepix,bombpix,bulletpix[3],monster1pix,monster2pix,monster3pix,buttonpix,backgroundpix,background2pix;
    sight windowsight;
    class exit pass;
};
#endif // MAINSCENE_H

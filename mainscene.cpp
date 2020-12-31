#include "mainscene.h"
#include "function.h"
#include "config.h"
#include <string>
#include <QPainter>
#include <QApplication>

QString FormStyleSheetString(){
    const QString thisItemStyle(
        "QPushButton{background-color:rgb(154, 217, 234);color: black;border-radius: 10px;border: 2px groove rgb(38, 111, 130);border-style: outset;}"
        "QPushButton:hover{background-color:rgb(85, 170, 255); color: black;}"
        "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }"
    );

  return thisItemStyle;
}
void mainscene::clearall(){
    running=0;
    cube_arr.clear();
    bullet_arr.clear();
    bomb_arr.clear();
    monster1_arr.clear();
    monster2_arr.clear();
    monster3_arr.clear();
    button_arr.clear();
}
mainscene::~mainscene(){
}
mainscene::mainscene(QWidget *parent)
    : QWidget(parent){
    setFixedSize(WIDTH,HEIGHT);
    running=0;
    pass_number=0;
    now=0;

    optionbutton=new QPushButton(this);
    optionbutton->setText("关卡选择");
    optionbutton->setGeometry(70,600,200,100);
    optionbutton->setStyleSheet(FormStyleSheetString());
    connect(optionbutton,SIGNAL(clicked()),this,SLOT(choose()));


    loadbutton=new QPushButton(this);
    loadbutton->setText("读取存档");
    loadbutton->setGeometry(400,600,200,100);
    loadbutton->setStyleSheet(FormStyleSheetString());
    connect(loadbutton,SIGNAL(clicked()),this,SLOT(load()));


    savebutton=new QPushButton(this);
    savebutton->setText("保存存档");
    savebutton->setGeometry(730,600,200,100);
    savebutton->setStyleSheet(FormStyleSheetString());
    connect(savebutton,SIGNAL(clicked()),this,SLOT(save()));


    statementbutton=new QPushButton(this);
    statementbutton->setText("游戏说明");
    statementbutton->setGeometry(1060,600,200,100);
    statementbutton->setStyleSheet(FormStyleSheetString());
    connect(statementbutton,&QPushButton::clicked,[=](){
        dialogwindow=new dialog(this);
        dialogwindow->one_button_bigwindow();
        dialogwindow->button1->setText("确认");
        dialogwindow->label->setText(STATEMENT);
    });
    cubepix.load(CUBE_PATH);
    monster1pix.load(MONSTER1_PATH);
    monster2pix.load(MONSTER2_PATH);
    monster3pix.load(MONSTER3_PATH);
    bombpix.load(BOMB_PATH);
    buttonpix.load(BUTTON_PATH);
    backgroundpix.load(BACKGROUND_PATH);
    background2pix.load(BACKGROUND2_PATH);
    for(int i=1;i<=2;i++){
        bulletpix[i].load(QString(BULLET_PATH).arg(i));
    }
}
void mainscene::over(){
    clearall();
    m_Timer->stop();
    delete m_Timer;
    optionbutton->show();
    loadbutton->show();
    savebutton->show();
    statementbutton->show();
    optionbutton->setEnabled(1);
    loadbutton->setEnabled(1);
    savebutton->setEnabled(1);
    statementbutton->setEnabled(1);
    hero.init();
    pass.open=0;
    running=0;
    herogun.angle=0;
}
void mainscene::choose(){
    optionbutton->setDisabled(1);
    loadbutton->setDisabled(1);
    savebutton->setDisabled(1);
    statementbutton->setDisabled(1);
    optionbutton->hide();
    loadbutton->hide();
    savebutton->hide();
    statementbutton->hide();
    choosebutton=new QPushButton[5];
    std::string s="1";
    for(int i=0;i<5;i++){
        choosebutton[i].setStyleSheet(FormStyleSheetString());
        choosebutton[i].setParent(this);
        choosebutton[i].setGeometry(100+i*150,100,100,50);
        choosebutton[i].show();
        s[0]=char('1'+i);
        choosebutton[i].setText(s.c_str());
        connect(choosebutton+i,&QPushButton::clicked,[=](){loadmap(i+1);});
        if(i>pass_number)choosebutton[i].setDisabled(1);
    }
}
void mainscene::load(){
    dialogwindow=new dialog(this);
    dialogwindow->two_button_window();
    dialogwindow->button1->setText("确认");
    dialogwindow->button2->setText("取消");
    dialogwindow->label->setText("是否要读取");
    connect(dialogwindow->button1,&QPushButton::clicked,[=](){
       FILE* file=fopen(SAVEDATA_PATH,"r");
       fscanf(file,"%d",&pass_number);
       fclose(file);
       dialogwindow->close();
       delete dialogwindow;
    });
}
void mainscene::save(){
    dialogwindow=new dialog(this);
    dialogwindow->two_button_window();
    dialogwindow->button1->setText("确认");
    dialogwindow->button2->setText("取消");
    dialogwindow->label->setText("是否要保存");
    connect(dialogwindow->button1,&QPushButton::clicked,[=](){
       FILE* file=fopen(SAVEDATA_PATH,"w");
       fprintf(file,"%d",pass_number);
       fclose(file);
       dialogwindow->close();
       delete dialogwindow;
    });
}
void mainscene::loadmap(int x){
    now=x;
    for(int i=0;i<5;i++){
        choosebutton[i].hide();
        choosebutton[i].setDisabled(1);
    }
    clearall();
    std::string map_path="map-1";
    map_path[4]=char('0'+x);
    FILE* file=fopen((map_path+MAP_FILE).c_str(),"r");
    int x1,x2,y1,y2,drx,type;
    while(fscanf(file,"%d%d%d%d",&x1,&x2,&y1,&y2)==4){
        for(int i=ID(x1);i<=ID(x2);i++)
            for(int j=ID(y1);j<=ID(y2);j++)
                cube_arr.insert(pii(i,j));
    }
    fclose(file);
    file=fopen((map_path+MONSTER1_FILE).c_str(),"r");
    while(fscanf(file,"%d%d%d",&x1,&y1,&drx)==3)
        monster1_arr.push_back(monster1(x1,y1-MONSTER1_HEIGHT,drx));
    fclose(file);
    file=fopen((map_path+MONSTER2_FILE).c_str(),"r");
    while(fscanf(file,"%d%d%d",&x1,&y1,&drx)==3)
        monster2_arr.push_back(monster2(x1,y1-70,drx,5));
    fclose(file);
    file=fopen((map_path+MONSTER3_FILE).c_str(),"r");
    while(fscanf(file,"%d%d%d",&x1,&y1,&drx)==3)
        monster3_arr.push_back(monster3(x1,y1,drx));
    fclose(file);
    file=fopen((map_path+BUTTON_FILE).c_str(),"r");
    while(fscanf(file,"%d%d%d%d",&x1,&y1,&drx,&type)==4){
        button_arr.push_back(button(x1,y1,drx,type));
        if(type==1){
            fscanf(file,"%d",&type);
            for(int i=1;i<=type;i++){
                fscanf(file,"%d%d",&x1,&y1);
                button_arr.back().arr.push_back(pii(ID(x1),ID(y1)));
            }
        }
    }
    fclose(file);
    file=fopen((map_path+ELEM_FILE).c_str(),"r");
    fscanf(file,"%d%d%d%d",&x1,&y1,&x2,&y2);
    pass.x=x1;
    pass.y=y1;
    pass.rect.moveTo(pass.x,pass.y);
    hero.x=x2;
    hero.y=y2;
    hero.rect.moveTo(hero.x,hero.y);
    fclose(file);
    startplay();
}
void mainscene::startplay(){
    m_Timer=new QTimer;
    m_Timer->start(FPS);
    running=1;
    connect(m_Timer,&QTimer::timeout,[=](){
        updatePosition();
        update();
    });
}
void mainscene::destroyhero(){
    hero.del=1;
    bomb_arr.push_back(bomb(hero.x,hero.y+BOMB_HEIGHT/2));
    this->setDisabled(1);
    m_Timer2=new QTimer;
    m_Timer2->setInterval(FPS*BOMB_LAST);
    m_Timer2->start();
    connect(m_Timer2,&QTimer::timeout,[=](){
        over();
        delete m_Timer2;
        this->setEnabled(1);
        dialogwindow=new dialog(this);
        dialogwindow->one_button_window();
        dialogwindow->button1->setText("重新来过");
        dialogwindow->label->setText("您死了");
    });
}
void mainscene::shoot(){
    double bullet_x,bullet_y,bullet_vx,bullet_vy;
    double div;
    if(abs(herogun.angle)<30)div=2.5;
    else if(abs(herogun.angle)<=50)div=2.1;
    else div=1.5;
    bullet_x=hero.x+hero.gun_x;
    bullet_y=hero.y+hero.gun_y+GUN_HEIGHT/2-15;
    bullet_x+=cos(herogun.angle*PI/180.0)*GUN_WIDTH/div;
    bullet_y+=sin(herogun.angle*PI/180.0)*GUN_WIDTH/div;
    bullet_vx=cos(herogun.angle*PI/180.0)*herogun.v;
    bullet_vy=sin(herogun.angle*PI/180.0)*herogun.v;
    if(hero.drx==-1){
        bullet_x-=(bullet_x-hero.x-ROLE_WIDTH/2)*2+BULLET_L-1;
        bullet_vx*=-1;
    }
    bullet_arr.push_back(bullet(bullet_x,bullet_y,bullet_vx,bullet_vy,1,herogun.time));
}
void mainscene::updatehero(){
    int x1=hero.x,x2=hero.x+ROLE_WIDTH-1,y1=hero.y,y2=hero.y+ROLE_HEIGHT-1;
    int v=hero.v,vy=hero.vy;
    hero.y+=vy;
    hero.x+=v;
    if(hero.v!=0)hero.move=1;
    double t1=std::max(1.0*(sub(x2)-x2)/v,1.0*(pre(x1)-x1+1)/v);
    double t2=std::max(1.0*(sub(y2)-y2)/vy,1.0*(pre(y1)-y1+1)/vy);
    if(t1<=t2&&t1<=1.0){
        int xx=0,yy=0,l=ID(int(y1+vy*t1)),r=ID(int(y2+vy*t1));
        if(v>0)xx=ID(x2)+1;
        else xx=ID(x1)-1;
        for(int i=l;i<=r;i++)
            if(cube_arr.find(pii(xx,i))!=cube_arr.end()){
                hero.move=0;
                if(v>0)hero.x=sub(x2)-ROLE_WIDTH;
                else hero.x=pre(x1);
                v=0;
                break;
            }
        if(t2<=1.0){
            l=ID(int(hero.x+v*t2));
            r=ID(int(hero.x+ROLE_WIDTH-1+v*t2));
            if(vy>0)yy=ID(y2)+1;
            else yy=ID(y1)-1;
            for(int i=l;i<=r;i++){
                if(cube_arr.find(pii(i,yy))!=cube_arr.end()){
                    if(vy>0){
                        hero.y=sub(y2)-ROLE_HEIGHT;
                        hero.falling=0;
                        hero.vy=0;
                    }
                    else{
                        hero.y=pre(y1);
                        hero.vy=0;
                    }
                    break;
                }
            }
        }
    }
    else if(t2<=t1&&t2<=1.0){
        int xx=0,yy=0,l=ID(int(x1+v*t2)),r=ID(int(x2+v*t2));
        if(vy>0)yy=ID(y2)+1;
        else yy=ID(y1)-1;
        for(int i=l;i<=r;i++){
            if(cube_arr.find(pii(i,yy))!=cube_arr.end()){
                if(vy>0){
                    hero.y=sub(y2)-ROLE_HEIGHT;
                    hero.falling=0;
                    hero.vy=0;
                }
                else{
                    hero.y=pre(y1);
                    hero.vy=0;
                }
                break;
            }
        }
        if(t1<=1.0){
            l=ID(int(hero.y+vy*t1));
            r=ID(int(hero.y+ROLE_HEIGHT-1+vy*t1));
            if(v>0)xx=ID(x2)+1;
            else xx=ID(x1)-1;
            for(int i=l;i<=r;i++)
                if(cube_arr.find(pii(xx,i))!=cube_arr.end()){
                    if(hero.falling)hero.move=0;
                    if(v>0)hero.x=sub(x2)-ROLE_WIDTH;
                    else hero.x=pre(x1);
                    v=0;
                    break;
                }
        }
    }
    static int gindex;
    if(hero.falling){
        gindex++;
        if(gindex&1)hero.vy+=GRAVITY;
    }
    else{
        gindex=0;
        int yy=ID(hero.y+ROLE_HEIGHT-1)+1,l=ID(hero.x),r=ID(hero.x+ROLE_WIDTH-1);
        bool flag=0;
        for(int i=l;i<=r;i++)
            if(cube_arr.find(pii(i,yy))!=cube_arr.end())flag=1;
        if(!flag)hero.falling=1;
    }
    static int index;
    if(hero.move&&!hero.falling){
        index++;
        if(index>50)index=1;
        hero.now=hero.pix[(index-1)/5];
    }
    else{
        hero.now=hero.stop;
        index=0;
    }
    hero.rect.moveTo(hero.x+ROLE_WIDTH/3,hero.y);
}
void mainscene::updatebullet(bullet &B){
    B.now++;
    double x1=B.x,x2=B.x+BULLET_L-1,y1=B.y,y2=B.y+BULLET_L-1;
    double vx=B.vx,vy=B.vy;
    B.y+=vy;B.x+=vx;
    double t1=std::max(1.0*(sub2(x2)-x2)/vx,1.0*(pre2(x1)-x1)/vx);
    double t2=std::max(1.0*(sub2(y2)-y2)/vy,1.0*(pre2(y1)-y1)/vy);
    if(t1<=t2&&t1<=1.0){
        int xx=0,l=ID2(y1+vy*t1),r=ID2(y2+vy*t1);
        if(vx>0)xx=ID2(x2)+1;
        else xx=ID2(x1)-1;
        for(int i=l;i<=r;i++)
            if(cube_arr.find(pii(xx,i))!=cube_arr.end()){
                B.vx=-vx;
                B.y=y1+vy*t1;
                if(vx>0)B.x=sub2(x2)-BULLET_L;
                else B.x=pre2(x1);
                B.rect.moveTo(int(B.x),int(B.y));
                return;
            }
    }
    if(t2<=1.0){
        int yy=0,l=ID2(x1+vx*t2),r=ID2(x2+vx*t2);
        if(vy>0)yy=ID2(y2)+1;
        else yy=ID2(y1)-1;
        for(int i=l;i<=r;i++){
            if(cube_arr.find(pii(i,yy))!=cube_arr.end()){
                B.vy=-vy;
                B.x=x1+vx*t2;
                if(vy>0)B.y=sub2(y2)-BULLET_L;
                else B.y=pre2(y1);
                B.rect.moveTo(int(B.x),int(B.y));
                return;
            }
        }

    }
    if(t1<=1.0){
        int xx=0,l=ID2(y1+vy*t1),r=ID2(y2+vy*t1);
        if(vx>0)xx=ID2(x2)+1;
        else xx=ID2(x1)-1;
        for(int i=l;i<=r;i++)
            if(cube_arr.find(pii(xx,i))!=cube_arr.end()){
                B.vx=-vx;
                B.y=y1+vy*t1;
                if(vx>0)B.x=sub2(x2)-24;
                else B.x=pre2(x1);
                B.rect.moveTo(int(B.x),int(B.y));
                return;
            }
    }
    B.rect.moveTo(int(B.x),int(B.y));
}
void mainscene::updatemonster1(){
    for(auto &i:monster1_arr){
        if(i.del)i.del--;
        else{
            i.index++;
            if(i.index==12){
                if(i.drx==1)bullet_arr.push_back(bullet(i.x+MONSTER1_WIDTH+BULLET_L,i.y+MONSTER1_HEIGHT/4,10,0,2,200));
                else bullet_arr.push_back(bullet(i.x-BULLET_L,i.y+MONSTER1_HEIGHT/4,-10,0,2,200));
                i.index=0;
            }
        }
    }
    std::vector<monster1>temp=monster1_arr;
    monster1_arr.clear();
    for(auto &i:temp){
        if(i.del!=1)monster1_arr.push_back(i);
    }
}
void mainscene::updatemonster2(){
    for(auto &i:monster2_arr){
        if(i.del)i.del--;
        else{
            int l=ID(i.y),r=ID(i.y+MONSTER2_HEIGHT-1);
            i.x+=i.drx*i.v;
            if(i.drx==1){
                for(int j=l;j<=r;j++)
                    if(cube_arr.find(pii(ID(i.x+MONSTER2_WIDTH),j))!=cube_arr.end()){
                        i.drx=-1;
                        i.x=pre(i.x+MONSTER2_WIDTH)-MONSTER2_WIDTH;
                        break;
                    }
                if(cube_arr.find(pii(ID(i.x+MONSTER2_WIDTH-1),ID(i.y+MONSTER2_HEIGHT)))==cube_arr.end())i.drx=-1;
                i.rect1.moveTo(i.x+MONSTER2_WIDTH-MONSTER2_FRONT,i.y);
                i.rect2.moveTo(i.x,i.y+MONSTER2_HEIGHT-MONSTER2_HEIGHT2);
            }
            else{
                for(int j=l;j<=r;j++)
                    if(cube_arr.find(pii(ID(i.x),j))!=cube_arr.end()){
                        i.drx=1;
                        i.x=sub(i.x);
                        break;
                    }
                if(cube_arr.find(pii(ID(i.x-1),ID(i.y+MONSTER2_HEIGHT)))==cube_arr.end())i.drx=1;
                i.rect1.moveTo(i.x,i.y);
                i.rect2.moveTo(i.x+MONSTER2_FRONT,i.y+MONSTER2_HEIGHT-MONSTER2_HEIGHT2);
            }
        }
    }
    std::vector<monster2>temp=monster2_arr;
    monster2_arr.clear();
    for(auto &i:temp){
        if(i.del!=1)monster2_arr.push_back(i);
    }
}
void mainscene::updatemonster3(){
    for(auto &i:monster3_arr){
        i.index++;
        if(i.index==100){
            int x1=i.x+MONSTER3_WIDTH/2,y1=i.y,L=30,V=10;
            if(i.drx==1){
                y1+=MONSTER3_HEIGHT;
                bullet_arr.push_back(bullet(x1+L,y1-BULLET_L,V,0,2,200));
                bullet_arr.push_back(bullet(x1+L*cos(45),y1-L*sin(45)-BULLET_L,V*cos(45),-V*sin(45),2,200));
                bullet_arr.push_back(bullet(x1-L*cos(45)-BULLET_L,y1-L*sin(45)-BULLET_L,-V*cos(45),-V*sin(45),2,200));
                bullet_arr.push_back(bullet(x1-L-BULLET_L,y1-BULLET_L,-V,0,2,200));
            }
            else{
                bullet_arr.push_back(bullet(x1+L,y1,V,0,2,200));
                bullet_arr.push_back(bullet(x1+L*cos(45),y1+L*sin(45),V*cos(45),V*sin(45),2,200));
                bullet_arr.push_back(bullet(x1-L*cos(45)-BULLET_L,y1+L*sin(45),-V*cos(45),V*sin(45),2,200));
                bullet_arr.push_back(bullet(x1-L-BULLET_L,y1,-V,0,2,200));
            }
            i.index=0;
        }
    }
}
void mainscene::colide(){
    if(pass.open){
        if(!hero.del&&pass.rect.intersects(hero.rect)){
            if(now>pass_number)pass_number=now;
            dialogwindow=new dialog(this);
            dialogwindow->one_button_window();
            dialogwindow->button1->setText("继续");
            dialogwindow->label->setText("恭喜通关");
            over();
            return;
        }
    }
    std::vector<bullet> temp=bullet_arr;
    bullet_arr.clear();
    for(auto &i:temp){
        if(i.time<=i.now)i.del=1;
        if(!hero.del&&hero.rect.intersects(i.rect)){
            i.del=1;
            destroyhero();
        }
        for(auto &j:temp){
            if(&j==&i)continue;
            if(i.rect.intersects(j.rect)){
                i.del=j.del=1;
            }
        }
        for(auto &j:monster1_arr){
            if(!j.del&&j.rect.intersects(i.rect)){
                i.del=1;
                j.del=BOMB_LAST+1;
                bomb_arr.push_back(bomb(j.x,j.y));
            }
        }
        for(auto &j:monster2_arr){
            if(!j.del&&j.rect1.intersects(i.rect))i.del=1;
            else if(!j.del&&j.rect2.intersects(i.rect)){
                i.del=1;
                j.del=BOMB_LAST+1;
                bomb_arr.push_back(bomb(j.x,j.y));
            }
        }
        for(auto &j:button_arr){
            if(j.rect.intersects(i.rect)){
                i.del=1;
                if(j.type==0)pass.open=1;
                else if(j.open){
                    for(auto &k:j.arr)cube_arr.erase(k);
                    j.open=0;
                }
                else{
                    bool flag=0;
                    QRect rect,rect2;
                    rect.setWidth(CUBE_L);
                    rect.setHeight(CUBE_L);
                    rect2.setWidth(ROLE_WIDTH);
                    rect2.setHeight(ROLE_HEIGHT);
                    rect2.moveTo(hero.x,hero.y);
                    for(auto &k:j.arr){
                        rect.moveTo(k.first*20,k.second*20);
                        if(rect.intersects(rect2))flag=1;
                    }
                    if(!flag){
                        for(auto &k:j.arr)cube_arr.insert(k);
                        j.open=1;
                    }
                }
            }
        }
    }
    for(auto &i:temp)
        if(!i.del)bullet_arr.push_back(i);
    for(auto &i:monster1_arr){
        if(!hero.del&&i.rect.intersects(hero.rect))
            destroyhero();
    }
    for(auto &i:monster2_arr){
        if(!hero.del)
            if(i.rect1.intersects(hero.rect)||i.rect1.intersects(hero.rect))
                destroyhero();
    }
}
void mainscene::updatebomb(){
    std::vector<bomb> tempb=bomb_arr;
    for(auto &i:tempb)i.update();
    bomb_arr.clear();
    for(auto i:tempb)if(!i.del)bomb_arr.push_back(i);
}
void mainscene::updatePosition(){
    colide();
    updatebomb();
    updatehero();
    updatemonster1();
    updatemonster2();
    updatemonster3();
    for(auto &i:bullet_arr)updatebullet(i);
    windowsight.update(hero);
}
void mainscene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if(running)painter.drawPixmap(0,0,backgroundpix);
    else painter.drawPixmap(0,0,background2pix);
    painter.translate(-windowsight.x,-windowsight.y);
    if(pass.open&&running)
        painter.drawPixmap(pass.x,pass.y,pass.pix);
    for(auto i:bullet_arr)
        painter.drawPixmap(int(i.x),int(i.y),BULLET_L,BULLET_L,bulletpix[i.kind]);
    if(!hero.del&&running){
        if(hero.drx==-1){
            painter.translate(hero.x+ROLE_WIDTH-hero.gun_x,hero.y+hero.gun_y+GUN_HEIGHT/2);
            painter.rotate(-herogun.angle);
            painter.drawPixmap(-GUN_WIDTH,-GUN_HEIGHT/2,GUN_WIDTH,GUN_HEIGHT,mirrorpix(herogun.gunpix,1,0));
            painter.rotate(herogun.angle);
            painter.translate(-(hero.x+ROLE_WIDTH-hero.gun_x),-(hero.y+hero.gun_y+GUN_HEIGHT/2));
            painter.drawPixmap(hero.x,hero.y,ROLE_WIDTH,ROLE_HEIGHT,mirrorpix(hero.now,1,0));
        }
        else{
            painter.translate(hero.x+hero.gun_x,hero.y+hero.gun_y+GUN_HEIGHT/2);
            painter.rotate(herogun.angle);
            painter.drawPixmap(0,-GUN_HEIGHT/2,GUN_WIDTH,GUN_HEIGHT,herogun.gunpix);
            painter.rotate(-herogun.angle);
            painter.translate(-(hero.x+hero.gun_x),-(hero.y+hero.gun_y+GUN_HEIGHT/2));
            painter.drawPixmap(hero.x,hero.y,ROLE_WIDTH,ROLE_HEIGHT,hero.now);
        }
    }
    for(auto i:monster1_arr){
        if(i.drx==-1)painter.drawPixmap(i.x,i.y,MONSTER1_WIDTH,MONSTER1_HEIGHT,mirrorpix(monster1pix,1,0));
        else painter.drawPixmap(i.x,i.y,MONSTER1_WIDTH,MONSTER1_HEIGHT,monster1pix);
    }
    for(auto i:monster2_arr){
        if(i.drx==-1)painter.drawPixmap(i.x,i.y,mirrorpix(monster2pix,1,0));
        else painter.drawPixmap(i.x,i.y,monster2pix);
    }
    for(auto i:monster3_arr){
        if(i.drx==-1)painter.drawPixmap(i.x,i.y,MONSTER3_WIDTH,MONSTER3_HEIGHT,mirrorpix(monster3pix,0,1));
        else painter.drawPixmap(i.x,i.y,MONSTER3_WIDTH,MONSTER3_HEIGHT,monster3pix);
    }
    for(auto i:cube_arr)
        painter.drawPixmap(i.first*CUBE_L,i.second*CUBE_L,cubepix);
    for(auto i:button_arr){
        if(i.drx==-1)painter.drawPixmap(i.x,i.y,mirrorpix(buttonpix,1,0));
        else painter.drawPixmap(i.x,i.y,buttonpix);
    }
    for(auto i:bomb_arr)
        painter.drawPixmap(i.x+(BOMB_WIDTH-i.w)/2,i.y+(BOMB_HEIGHT-i.h)/2,i.w,i.h,bombpix);
}
void mainscene::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_D)hero.act(1);
    else if(event->key()==Qt::Key_A)hero.act(-1);
    else if(event->key()==Qt::Key_S)herogun.act(1);
    else if(event->key()==Qt::Key_W)herogun.act(-1);
    else if(event->key()==Qt::Key_K)hero.jump();
    else if(!event->isAutoRepeat()&&event->key()==Qt::Key_J)shoot();
}
void mainscene::keyReleaseEvent(QKeyEvent *event){
    if(event->isAutoRepeat())return;
    if(event->key()==Qt::Key_D)hero.stop_act();
    else if(event->key()==Qt::Key_A)hero.stop_act();
}


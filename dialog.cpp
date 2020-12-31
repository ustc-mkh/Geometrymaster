#include "dialog.h"

dialog::dialog(QWidget* parent){
    button1=button2=NULL;
    label=NULL;
}
dialog::~dialog(){
    delete  button1;
    delete  button2;
    delete  label;
}
void dialog::one_button_window(){
    button1=new QPushButton(this);
    label=new QLabel(this);
    //dialogwindow->setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(400,200);
    button1->setGeometry(x()+150,y()+120,100,50);
    label->setGeometry(x()+150,y()+50,100,50);
    connect(button1,&QPushButton::clicked,[=](){
       close();
       delete this;
    });
    show();
}
void dialog::two_button_window(){
    button1=new QPushButton(this);
    button2=new QPushButton(this);
    label=new QLabel(this);
    //dialogwindow->setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(400,200);
    button1->setGeometry(x()+50,y()+120,80,40);
    button2->setGeometry(x()+270,y()+120,80,40);
    label->setGeometry(x()+50,y(),300,100);
    connect(button2,&QPushButton::clicked,[=](){
       close();
       delete this;
    });
    show();
}
void dialog::one_button_bigwindow(){
    button1=new QPushButton(this);
    label=new QLabel(this);
    //dialogwindow->setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(800,400);
    button1->setGeometry(x()+350,y()+320,100,50);
    label->setGeometry(x()+50,y()+50,700,250);
    connect(button1,&QPushButton::clicked,[=](){
       close();
       delete this;
    });
    show();
}

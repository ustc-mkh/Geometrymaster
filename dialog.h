#ifndef DIALOG_H
#define DIALOG_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>

class dialog : public QWidget
{
    Q_OBJECT

public:
    dialog(QWidget *parent = 0);
    ~dialog();
    void one_button_bigwindow();
    void one_button_window();
    void two_button_window();
public:
    QPushButton* button1, *button2;
    QLabel* label;
};


#endif // DIALOG_H

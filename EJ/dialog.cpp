#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QTime>

static void ShowMsg(const char *str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
    //msgBox.hide();

}

dialog::dialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);



}

dialog::~dialog()
{
    delete ui;
}


void dialog::on_progressBar_valueChanged(int value)
{
    //if打對單字
    //打錯單字
    //if命歸零 endgame msg
     ShowMsg("GG!");


}

void dialog::on_lcdNumber_overflow()
{
    //if打對單字
    //打錯單字
    //if命歸零 紀錄分數
     ShowMsg("GG!");
}



//Score

void dialog::upScore(int value){
    //if打對單字
    score += value;

}

void dialog::downScore(int value){
    //if打錯單字
    score -= value;

}

int dialog::getScore(){
    return score;
}


//Health

void dialog::upHealth(int value){
    health += value;

}

void dialog::downHealth(int value){
    health -= value;

}

int dialog::getHealth(){
    return health;
}


void dialog::on_lcdNumber_2_overflow()
{
}

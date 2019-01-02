#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    new_win = new dialog;
    new_win->resize(winWidth,winHeight);
    new_win->setWindowTitle(QObject::tr("接xxx單字吧!"));
    this->hide();
    new_win->show();
}



void MainWindow::on_pushButton_2_clicked()
{
    new_win = new dialog;
    new_win->resize(winWidth,winHeight);
    new_win->setWindowTitle(QObject::tr("接xxx單字吧!"));
    this->hide();
    new_win->show();
}

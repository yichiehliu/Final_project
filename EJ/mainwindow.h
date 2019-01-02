#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "dialog.h"

#include "parameter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    dialog *new_win;




private slots:
    void on_pushButton_clicked();
    //void on_button1_clicked();
    //void on_button2_clicked();
    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    void createScene();
    void reset();
    void registerUpdatingCallback();
    void updatingStairs();
};



#endif // MAINWINDOW_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include "parameter.h"


#include <QWidget>

namespace Ui {
class dialog;
}

class dialog : public QWidget
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();


    void upHealth(int);
    void downHealth(int);
    void upScore(int);
    void downScore(int);
    int getHealth();
    int getScore();

private slots:
    void on_progressBar_valueChanged(int value);
    void on_lcdNumber_overflow();

    void on_lcdNumber_2_overflow();


private:
    Ui::dialog *ui;
    int health = DEFAULT_HEALTH;
    int score = DEFAULT_SCORE;
    int time = DEFAULT_TIME;
};



#endif // DIALOG_H

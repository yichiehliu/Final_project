#include "widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("按鍵組"));
    myTimer = new QTimer;
    myLCDNumber = new QLCDNumber;
    myLCDNumber->setGeometry(30,30,150,30); //設定位置大小
    myLCDNumber->setDigitCount(8);          //設定位數
    myTimer->start(1000);                   //以1000毫秒為周期起動定時器
    showTime();
    connect(myTimer,SIGNAL(timeout()),this,SLOT(showTime()));
}

void Widget::showTime()
{
    QTime time = QTime::currentTime();
    QString text=time.toString("hh:mm:ss"); //設定顯示時間格式
    myLCDNumber->display(text);
}

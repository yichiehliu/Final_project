#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;           //創造一個主窗口物件

    w.resize(winWidth,winHeight);      //窗口尺寸
    w.move(100,100);        //窗口移動到距螢幕左上角100*100處
    int windowXPos = w.x(); //窗口左上角x座標
    int windowYPos = w.y(); //窗口左上角y座標
    //QRect windowGeometry = w.frameGeometry() //返回的QRect可得窗口長、寬、位置等資訊。


    w.setWindowTitle(QObject::tr("選擇吧!")); //設定窗口標題
    w.show();               //在螢幕上秀出窗口
    return a.exec();
}

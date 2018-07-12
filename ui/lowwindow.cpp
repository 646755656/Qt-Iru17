#include "lowwindow.h"
#include <QTimer>
#include <QDateTime>

lowwindow::lowwindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMaximumSize(800,50);
    setMinimumSize(800,50);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("lowwindow{background:rgb(80,80,160)}");

    QFont font_base;
    font_base.setFamily("宋体");
    font_base.setPixelSize(15);
    font_base.setBold(true);

    pbt_menu = new QPushButton("菜单",this);
    pbt_menu->setGeometry(750,3,45,45);
    pbt_menu->setFont(font_base);

    timelabel = new QLabel(this);
    timelabel->setGeometry(570,22,170,20);
    timelabel->setStyleSheet("QLabel{font-size:15px;font:bold}");

    QTimer *timesys = new QTimer(this);     //定时1s
    timesys->start(1000);
    connect(timesys,SIGNAL(timeout()),this,SLOT(slot_updatesystime()));     //系统时间

}


void lowwindow::slot_updatesystime()        //更新系统时间
{
    QDateTime systime = QDateTime::currentDateTime();

    QString str = systime.toString("yyyy-MM-dd hh:mm:ss");
    timelabel->setText(str);
}

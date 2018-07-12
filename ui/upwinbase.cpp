#include "upwinbase.h"
#include <QPainter>
#include <QStyleOption>

upwinbase::upwinbase(QWidget *parent) :
    QWidget(parent)
{
    setMaximumSize(800,430);
    setMinimumSize(800,430);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("upwinbase{background:white/*rgb(57,196,44)*/;}");

    QPalette palette;
    palette.setBrush(QPalette::Background,QColor(255,255,255));
    this->setPalette(palette);



//    pbt_menu = new QPushButton("菜单",this);
//    pbt_menu->setGeometry(750,390,40,40);
//    pbt_menu->setFont(font_base);

}

void upwinbase::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);
}

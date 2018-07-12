#include "homepage.h"
#include <QLabel>

homepage::homepage(QWidget *parent) :
    upwinbase(parent)
{
//    setStyleSheet("homepage{background:rgb(57,196,44);}");

    QFont font_base;
    font_base.setFamily("宋体");
    font_base.setPixelSize(15);
    font_base.setBold(true);

    titlelabel = new QLabel("IRU17控制终端",this);
    titlelabel->setGeometry(5,5,200,20);
//    titlelabel->setStyleSheet("color:white;/*font-size:14px;*/");
    titlelabel->setFont(font_base);
}

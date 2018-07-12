#include "startdis.h"

startdis::startdis(QWidget *parent) :
    QWidget(parent)
{
    setMaximumSize(800,480);
    setMinimumSize(800,480);

    uilow = new lowwindow(this);
    uilow->setGeometry(0,430,uilow->width(),uilow->height());

//    uimaindis->setGeometry(0,0,uimaindis->width(),uimaindis->height());
//    uimaindis = new maindisui(this);

}

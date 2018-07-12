#include "maindisui.h"

maindisui::maindisui(QWidget *parent) :
    QMainWindow(parent)
{
    setMaximumSize(800,430);
    setMinimumSize(800,430);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("maindisui{background:rgb(80,80,160)}");
}

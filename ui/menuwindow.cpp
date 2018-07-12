#include "menuwindow.h"
#include <QVBoxLayout>

menuwindow::menuwindow(QWidget *parent) :
    QWidget(parent)
{
    setMaximumSize(152,289);
    setMinimumSize(152,289);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("menuwindow{background:rgb(57,196,44);}");

    QFont font_menu;
    font_menu.setFamily("宋体");
    font_menu.setPixelSize(25);
    font_menu.setBold(true);

    pbt_mainui = new QPushButton("主界面",this);
    pbt_firstdataui = new QPushButton("一次数据",this);
    pbt_seconddataui = new QPushButton("二次数据",this);
    pbt_analogui = new QPushButton("采集数据",this);
    pbt_summarydataui = new QPushButton("汇总数据",this);
    pbt_runplanui = new QPushButton("运行计划",this);
    pbt_deviceui = new QPushButton("设备操作",this);

    pbt_mainui->setFixedSize(150,40);
    pbt_firstdataui->setFixedSize(150,40);
    pbt_seconddataui->setFixedSize(150,40);
    pbt_analogui->setFixedSize(150,40);
    pbt_summarydataui->setFixedSize(150,40);
    pbt_runplanui->setFixedSize(150,40);
    pbt_deviceui->setFixedSize(150,40);

    pbt_mainui->setFont(font_menu);
    pbt_firstdataui->setFont(font_menu);
    pbt_seconddataui->setFont(font_menu);
    pbt_analogui->setFont(font_menu);
    pbt_summarydataui->setFont(font_menu);
    pbt_runplanui->setFont(font_menu);
    pbt_deviceui->setFont(font_menu);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(pbt_firstdataui);
    vlayout->addWidget(pbt_seconddataui);
    vlayout->addWidget(pbt_analogui);
    vlayout->addWidget(pbt_summarydataui);
    vlayout->addWidget(pbt_runplanui);
    vlayout->addWidget(pbt_deviceui);
    vlayout->addWidget(pbt_mainui);
    vlayout->setSpacing(1);
    vlayout->setGeometry(QRect(1,1,150,289));
}

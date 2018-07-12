#include "mainwindow.h"
#include <QPainterPath>
#include <QPainter>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMaximumSize(800,480);
    setMinimumSize(800,480);
//    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
//    setStyleSheet("QMainWindow{background:blue;}");

    menuPressed = false;

    uistartdis = new startdis(this);        //显示下方部分

    m_stackwid = new QStackedWidget(this);
    uihomepage = new homepage(m_stackwid);
    uifirstwindow = new firstwindow(m_stackwid);
    uisecondwindow = new secondwindow(m_stackwid);
    uianalogwindow = new analogwindow(m_stackwid);
    uisummarywindow = new summarywindow(m_stackwid);
    uirunplanwindow = new runplanwindow(m_stackwid);
    uidevicewindow = new devicewindow(m_stackwid);

    m_stackwid->addWidget(uihomepage);      //添加并设置索引
    m_stackwid->addWidget(uifirstwindow);
    m_stackwid->addWidget(uisecondwindow);
    m_stackwid->addWidget(uianalogwindow);
    m_stackwid->addWidget(uisummarywindow);
    m_stackwid->addWidget(uirunplanwindow);
    m_stackwid->addWidget(uidevicewindow);

    m_stackwid->setGeometry(0,0,uihomepage->width(),uihomepage->height());
    m_stackwid->setCurrentIndex(0);

    uimenu = new menuwindow();
    connect(uistartdis->uilow->pbt_menu,SIGNAL(clicked()),this,SLOT(slot_showmenuui()));

    connect(uimenu->pbt_mainui,SIGNAL(clicked()),this,SLOT(slot_sethomepagestack0()));      //显示首界面
    connect(uimenu->pbt_firstdataui,SIGNAL(clicked()),this,SLOT(slot_setfirstwindowstack1()));  //显示一次数据界面
    connect(uimenu->pbt_seconddataui,SIGNAL(clicked()),this,SLOT(slot_setsecondwindowstack2()));  //显示一次数据界面
    connect(uimenu->pbt_analogui,SIGNAL(clicked()),this,SLOT(slot_setanalogwindowstack3()));  //显示一次数据界面
    connect(uimenu->pbt_summarydataui,SIGNAL(clicked()),this,SLOT(slot_setsummarywindowstack4()));  //显示一次数据界面
    connect(uimenu->pbt_runplanui,SIGNAL(clicked()),this,SLOT(slot_setrunplanwindowstack5()));  //显示一次数据界面
    connect(uimenu->pbt_deviceui,SIGNAL(clicked()),this,SLOT(slot_setdevicewindowstack6()));  //显示一次数据界面

//    show_animate_init();

//    keybd = new keyboard();
//    keybd->show();
}

MainWindow::~MainWindow()
{
    delete uimenu;

//    delete anishowmain;
//    delete anishowfirst;
//    delete anishowsecond;
//    delete anishowanalog;
//    delete anishowsummary;
//    delete anishowrunplan;
//    delete anishowdevice;
}

void MainWindow::show_animate_init()
{
    //动画显示
    anishowfirst = new QPropertyAnimation(uifirstwindow,"pos");
    connect(uimenu->pbt_firstdataui,SIGNAL(clicked()),this,SLOT(slot_showfirstwindow()));  //显示一次数据界面
    anishowfirst->setStartValue(QPoint(0,-430));
    anishowfirst->setEndValue(QPoint(0,0));
    anishowfirst->setDuration(300);

    anishowsecond = new QPropertyAnimation(uisecondwindow,"pos");
    connect(uimenu->pbt_seconddataui,SIGNAL(clicked()),this,SLOT(slot_showsecondwindow()));  //显示一次数据界面
    anishowsecond->setStartValue(QPoint(800,0));
    anishowsecond->setEndValue(QPoint(0,0));
    anishowsecond->setDuration(300);

    anishowanalog = new QPropertyAnimation(uianalogwindow,"pos");
    connect(uimenu->pbt_analogui,SIGNAL(clicked()),this,SLOT(slot_showanalogwindow()));  //显示一次数据界面
    anishowanalog->setStartValue(QPoint(-800,0));
    anishowanalog->setEndValue(QPoint(0,0));
    anishowanalog->setDuration(300);

    anishowsummary = new QPropertyAnimation(uisummarywindow,"pos");
    connect(uimenu->pbt_summarydataui,SIGNAL(clicked()),this,SLOT(slot_showsummarywindow()));  //显示一次数据界面
    anishowsummary->setStartValue(QPoint(0,430));
    anishowsummary->setEndValue(QPoint(0,0));
    anishowsummary->setDuration(300);

    anishowrunplan = new QPropertyAnimation(uirunplanwindow,"pos");
    connect(uimenu->pbt_runplanui,SIGNAL(clicked()),this,SLOT(slot_showrunplanwindow()));  //显示一次数据界面
    anishowrunplan->setStartValue(QPoint(-800,0));
    anishowrunplan->setEndValue(QPoint(0,0));
    anishowrunplan->setDuration(300);

    anishowdevice = new QPropertyAnimation(uidevicewindow,"pos");
    connect(uimenu->pbt_deviceui,SIGNAL(clicked()),this,SLOT(slot_showdevicewindow()));  //显示一次数据界面
    anishowdevice->setStartValue(QPoint(800,0));
    anishowdevice->setEndValue(QPoint(0,0));
    anishowdevice->setDuration(300);


}

void MainWindow::slot_showmenuui()
{
    int mapX,mapY;
    QPoint globalPos = this->mapToGlobal(uistartdis->uilow->pbt_menu->pos());//转成全局坐标

    mapX = globalPos.rx();
    mapY = globalPos.ry()+ uihomepage->height();

    menudisX = mapX + uistartdis->uilow->pbt_menu->width()-uimenu->width();
    menudisY = mapY - uimenu->height() - 1;
    if(menuPressed == false)
    {

        uimenu->setGeometry(menudisX ,menudisY,uimenu->width(),uimenu->height());//托盘菜单的位置
        uimenu->show();
        menuPressed = true;
    }
    else
    {
        uimenu->hide();
        menuPressed = false;
    }
}

void MainWindow::slot_showfirstwindow()
{
    anishowfirst->start();
}

void MainWindow::slot_showsecondwindow()
{
    anishowsecond->start();
}

void MainWindow::slot_showsummarywindow()
{
    anishowsummary->start();

}

void MainWindow::slot_showanalogwindow()
{
    anishowanalog->start();
}

void MainWindow::slot_showrunplanwindow()
{
    anishowrunplan->start();
}

void MainWindow::slot_showdevicewindow()
{
    anishowdevice->start();
}



void MainWindow::paintEvent(QPaintEvent *)
{
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(9, 9, this->width()-18, this->height()-18);


//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.fillPath(path, QBrush(Qt::white));


//    QColor color(0, 0, 0, 50);
//    for(int i=0; i<9; i++)
//    {
//       QPainterPath path;
//       path.setFillRule(Qt::WindingFill);
//       path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
//       color.setAlpha(150 - qSqrt(i)*50);
//       painter.setPen(color);
//       painter.drawPath(path);
    //    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //点击menu以外，隐藏menu
    if(menuPressed == true)     //按下菜单键
    {
        QRect *menupos = new QRect(menudisX ,menudisY,uimenu->width(),uimenu->height());
        if(menupos->contains(this->mapFromGlobal(QCursor::pos()))==false)
        {
            if (event->button() == Qt::LeftButton)
            {
                menuPressed = false;
                uimenu->hide();
            }
        }
    }
}

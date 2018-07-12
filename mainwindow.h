#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "./ui/menuwindow.h"
#include "./ui/upwinbase.h"
#include "./ui/startdis.h"
#include "./ui/homepage.h"
#include "./ui/firstwindow.h"
#include "./ui/secondwindow.h"
#include "./ui/analogwindow.h"
#include "./ui/summarywindow.h"
#include "./ui/runplanwindow.h"
#include "./ui/devicewindow.h"
#include <QMouseEvent>
#include <QPropertyAnimation>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    menuwindow *uimenu;
    upwinbase *uiupwinbase;
    startdis *uistartdis;
    homepage *uihomepage;
    firstwindow *uifirstwindow;
    secondwindow *uisecondwindow;
    analogwindow *uianalogwindow;
    summarywindow *uisummarywindow;
    runplanwindow *uirunplanwindow;
    devicewindow *uidevicewindow;

    QStackedWidget *m_stackwid; //设置多个界面只能显示一个

    keyboard *keybd;


private:
    bool menuPressed;
    int menudisX,menudisY;

    QPropertyAnimation *anishowmain;
    QPropertyAnimation *anishowfirst;
    QPropertyAnimation *anishowsecond;
    QPropertyAnimation *anishowanalog;
    QPropertyAnimation *anishowsummary;
    QPropertyAnimation *anishowrunplan;
    QPropertyAnimation *anishowdevice;

    void show_animate_init();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void slot_showmenuui();


public slots:
    void slot_sethomepagestack0() {m_stackwid->setCurrentIndex(0);uimenu->hide();menuPressed = false;}
    void slot_setfirstwindowstack1() {m_stackwid->setCurrentIndex(1);uimenu->hide();menuPressed = false;}
    void slot_setsecondwindowstack2() {m_stackwid->setCurrentIndex(2);uimenu->hide();menuPressed = false;}
    void slot_setanalogwindowstack3() {m_stackwid->setCurrentIndex(3);uimenu->hide();menuPressed = false;}
    void slot_setsummarywindowstack4() {m_stackwid->setCurrentIndex(4);uimenu->hide();menuPressed = false;}
    void slot_setrunplanwindowstack5() {m_stackwid->setCurrentIndex(5);uimenu->hide();menuPressed = false;}
    void slot_setdevicewindowstack6() {m_stackwid->setCurrentIndex(6);uimenu->hide();menuPressed = false;}

    void slot_showfirstwindow();
    void slot_showsecondwindow();
    void slot_showsummarywindow();
    void slot_showanalogwindow();
    void slot_showrunplanwindow();
    void slot_showdevicewindow();
};

#endif // MAINWINDOW_H

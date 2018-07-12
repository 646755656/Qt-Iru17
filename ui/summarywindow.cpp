#include "summarywindow.h"
#include <QFontMetrics>
#include <QStyleOption>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QPainter>


summarywindow::summarywindow(QWidget *parent) :
    upwinbase(parent)
{
//    setStyleSheet("summarywindow{background:rgb(80,120,140);}");

    QLabel *labeltitle = new QLabel("汇总数据:",this);
    labeltitle->setGeometry(5,3,22*5,24);
    labeltitle->setStyleSheet("font:bold;font-size:22px;font-family:宋体");

    QFontMetrics metric= labeltitle->fontMetrics(); //获取labeltitle的内容长度
    headlength = metric.width(labeltitle->text());

    hfirstlayout = new QHBoxLayout();
    hsecondlayout = new QHBoxLayout();
    hotherlayout = new QHBoxLayout();

    first_data_display();
    second_data_display();
    other_data_display();

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addLayout(hfirstlayout);
    hlayout->addStretch();
    hlayout->addLayout(hsecondlayout);
    hlayout->addSpacing(10);

    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addLayout(hotherlayout);


    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addSpacing(20);
    vlayout2->addLayout(hlayout);
    vlayout2->addStretch();
    vlayout2->addLayout(vlayout1);
    vlayout2->addStretch();
    vlayout2->setGeometry(QRect(5,30,790,390));


}

void summarywindow::paintEvent(QPaintEvent *)
{
    //绘制背景颜色
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    //标题下方画直线
    QPainter paint(this);
    paint.setPen(QPen(Qt::black,1));
    paint.drawLine(5,28,5 + headlength,28);
    paint.drawLine(5,30,5 + headlength,30);

    //水位下方画直线
//    paint.drawLine(95,54,95 + 65,54);
//    paint.drawLine(315,54,315 + 65,54);

    //画矩形
//    paint.drawRect(95,34,67,20);
//    paint.drawRect(335,34,67,20);

}

void summarywindow::first_data_display()
{
    //数据标题
    QLabel *titlefirstPower = new QLabel("一 次 总 功 率",this);
    titlefirstPower->setFixedSize(150,20);
    titlefirstPower->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlefirstkWh = new QLabel("一 次 用 电 量",this);
    titlefirstkWh->setFixedSize(150,20);
    titlefirstkWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlefirsttotalPV = new QLabel("一次总瞬时流量",this);
    titlefirsttotalPV->setFixedSize(150,20);
    titlefirsttotalPV->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlefirstFwater = new QLabel("一次正向供水量",this);
    titlefirstFwater->setFixedSize(150,20);
    titlefirstFwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlefirstRwater = new QLabel("一次负向供水量",this);
    titlefirstRwater->setFixedSize(150,20);
    titlefirstRwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlefirsttotalwater = new QLabel("一次总供水量",this);
    titlefirsttotalwater->setFixedSize(150,20);
    titlefirsttotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlefirstnormaltime = new QLabel("一次常态时间",this);
    titlefirstnormaltime->setFixedSize(150,20);
    titlefirstnormaltime->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    //数据
    firstPower = new QLineEdit("0.0",this);
    firstPower->setFixedSize(100,20);
    firstPower->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    firstPower->setFocusPolicy(Qt::NoFocus);

    firstkWh = new QLineEdit("0.0",this);
    firstkWh->setFixedSize(100,20);
    firstkWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    firstkWh->setFocusPolicy(Qt::NoFocus);

    firsttotalPV = new QLineEdit("0.0",this);
    firsttotalPV->setFixedSize(100,20);
    firsttotalPV->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    firsttotalPV->setFocusPolicy(Qt::NoFocus);

    firstFwater = new QLineEdit("0.0",this);
    firstFwater->setFixedSize(100,20);
    firstFwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    firstFwater->setFocusPolicy(Qt::NoFocus);

    firstRwater = new QLineEdit("0.0",this);
    firstRwater->setFixedSize(100,20);
    firstRwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    firstRwater->setFocusPolicy(Qt::NoFocus);

    firsttotalwater = new QLineEdit("0.0",this);
    firsttotalwater->setFixedSize(100,20);
    firsttotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    firsttotalwater->setFocusPolicy(Qt::NoFocus);

    firstnormaltime = new QLineEdit("0",this);
    firstnormaltime->setFixedSize(100,20);
    firstnormaltime->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    firstnormaltime->setFocusPolicy(Qt::NoFocus);

    //数据单位
    QLabel *unitfirstPower = new QLabel("kW",this);
    unitfirstPower->setFixedSize(50,20);
    unitfirstPower->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitfirstkWh = new QLabel("kWh",this);
    unitfirstkWh->setFixedSize(50,20);
    unitfirstkWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitfirsttotalPV = new QLabel("m3/h",this);
    unitfirsttotalPV->setFixedSize(50,20);
    unitfirsttotalPV->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitfirstFwater = new QLabel("m3",this);
    unitfirstFwater->setFixedSize(50,20);
    unitfirstFwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitfirstRwater = new QLabel("m3",this);
    unitfirstRwater->setFixedSize(50,20);
    unitfirstRwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitfirsttotalwater = new QLabel("m3",this);
    unitfirsttotalwater->setFixedSize(50,20);
    unitfirsttotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitfirstnormaltime = new QLabel("h",this);
    unitfirstnormaltime->setFixedSize(50,20);
    unitfirstnormaltime->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    titlefirstPower->setAlignment(Qt::AlignJustify);

    //垂直分布
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(titlefirstPower);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlefirstkWh);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlefirsttotalPV);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlefirstFwater);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlefirstRwater);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlefirsttotalwater);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlefirstnormaltime);

    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(firstPower);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(firstkWh);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(firsttotalPV);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(firstFwater);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(firstRwater);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(firsttotalwater);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(firstnormaltime);

    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(unitfirstPower);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitfirstkWh);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitfirsttotalPV);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitfirstFwater);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitfirstRwater);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitfirsttotalwater);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitfirstnormaltime);

    hfirstlayout->addSpacing(10);
    hfirstlayout->addLayout(vlayout1);
    hfirstlayout->addSpacing(0);
    hfirstlayout->addLayout(vlayout2);
    hfirstlayout->addSpacing(5);
    hfirstlayout->addLayout(vlayout3);

}

void summarywindow::second_data_display()
{
    //数据标题
    QLabel *titlesecondPower = new QLabel("二 次 总 功 率",this);
    titlesecondPower->setFixedSize(150,20);
    titlesecondPower->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlesecondkWh = new QLabel("二 次 用 电 量",this);
    titlesecondkWh->setFixedSize(150,20);
    titlesecondkWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlesecondtotalPV = new QLabel("二次总瞬时流量",this);
    titlesecondtotalPV->setFixedSize(150,20);
    titlesecondtotalPV->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlesecondFwater = new QLabel("二次正向供水量",this);
    titlesecondFwater->setFixedSize(150,20);
    titlesecondFwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlesecondRwater = new QLabel("二次负向供水量",this);
    titlesecondRwater->setFixedSize(150,20);
    titlesecondRwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlesecondtotalwater = new QLabel("二次总供水量",this);
    titlesecondtotalwater->setFixedSize(150,20);
    titlesecondtotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titlesecondnormaltime = new QLabel("二次常态时间",this);
    titlesecondnormaltime->setFixedSize(150,20);
    titlesecondnormaltime->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");



    //数据
    secondPower = new QLineEdit("0.0",this);
    secondPower->setFixedSize(100,20);
    secondPower->setFocusPolicy(Qt::NoFocus);
    secondPower->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    secondkWh = new QLineEdit("0.0",this);
    secondkWh->setFixedSize(100,20);
    secondkWh->setFocusPolicy(Qt::NoFocus);
    secondkWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    secondtotalPV = new QLineEdit("0.0",this);
    secondtotalPV->setFixedSize(100,20);
    secondtotalPV->setFocusPolicy(Qt::NoFocus);
    secondtotalPV->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    secondFwater = new QLineEdit("0.0",this);
    secondFwater->setFixedSize(100,20);
    secondFwater->setFocusPolicy(Qt::NoFocus);
    secondFwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    secondRwater = new QLineEdit("0.0",this);
    secondRwater->setFixedSize(100,20);
    secondRwater->setFocusPolicy(Qt::NoFocus);
    secondRwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    secondtotalwater = new QLineEdit("0.0",this);
    secondtotalwater->setFixedSize(100,20);
    secondtotalwater->setFocusPolicy(Qt::NoFocus);
    secondtotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    secondnormaltime = new QLineEdit("0",this);
    secondnormaltime->setFixedSize(100,20);
    secondnormaltime->setFocusPolicy(Qt::NoFocus);
    secondnormaltime->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");


    //数据单位
    QLabel *unitsecondPower = new QLabel("kW",this);
    unitsecondPower->setFixedSize(50,20);
    unitsecondPower->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitsecondkWh = new QLabel("kWh",this);
    unitsecondkWh->setFixedSize(50,20);
    unitsecondkWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitsecondtotalPV = new QLabel("m3/h",this);
    unitsecondtotalPV->setFixedSize(50,20);
    unitsecondtotalPV->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitsecondFwater = new QLabel("m3",this);
    unitsecondFwater->setFixedSize(50,20);
    unitsecondFwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitsecondRwater = new QLabel("m3",this);
    unitsecondRwater->setFixedSize(50,20);
    unitsecondRwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitsecondtotalwater = new QLabel("m3",this);
    unitsecondtotalwater->setFixedSize(50,20);
    unitsecondtotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitsecondnormaltime = new QLabel("h",this);
    unitsecondnormaltime->setFixedSize(50,20);
    unitsecondnormaltime->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");


    titlesecondPower->setAlignment(Qt::AlignJustify);

    //垂直分布
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(titlesecondPower);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlesecondkWh);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlesecondtotalPV);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlesecondFwater);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlesecondRwater);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlesecondtotalwater);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titlesecondnormaltime);

    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(secondPower);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(secondkWh);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(secondtotalPV);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(secondFwater);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(secondRwater);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(secondtotalwater);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(secondnormaltime);

    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(unitsecondPower);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitsecondkWh);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitsecondtotalPV);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitsecondFwater);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitsecondRwater);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitsecondtotalwater);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitsecondnormaltime);

    hsecondlayout->addLayout(vlayout1);
    hsecondlayout->addSpacing(0);
    hsecondlayout->addLayout(vlayout2);
    hsecondlayout->addSpacing(5);
    hsecondlayout->addLayout(vlayout3);
}

void summarywindow::other_data_display()
{
    //数据标题
    QLabel *titlelifekWh = new QLabel("生 活 用 电 量",this);
    titlelifekWh->setFixedSize(150,20);
    titlelifekWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titleproducekWh = new QLabel("生 产 用 电 量",this);
    titleproducekWh->setFixedSize(150,20);
    titleproducekWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *titletotalwater = new QLabel("累 计 供 水 量",this);
    titletotalwater->setFixedSize(150,20);
    titletotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    //数据
    lifekWh = new QLineEdit("0.0",this);
    lifekWh->setFixedSize(100,20);
    lifekWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    lifekWh->setFocusPolicy(Qt::NoFocus);

    producekWh = new QLineEdit("0.0",this);
    producekWh->setFixedSize(100,20);
    producekWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    producekWh->setFocusPolicy(Qt::NoFocus);

    totalwater = new QLineEdit("0.0",this);
    totalwater->setFixedSize(100,20);
    totalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");
    totalwater->setFocusPolicy(Qt::NoFocus);

    //数据单位
    QLabel *unitlifekWh = new QLabel("kWh",this);
    unitlifekWh->setFixedSize(50,20);
    unitlifekWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unitproducekWh = new QLabel("kWh",this);
    unitproducekWh->setFixedSize(50,20);
    unitproducekWh->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    QLabel *unittotalwater = new QLabel("m3",this);
    unittotalwater->setFixedSize(50,20);
    unittotalwater->setStyleSheet("font-size:18px;font:bold;font-family:宋体;");

    //垂直分布
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(titlelifekWh);
    vlayout1->addSpacing(10);
    vlayout1->addWidget(titleproducekWh);
    vlayout1->addSpacing(20);
    vlayout1->addWidget(titletotalwater);

    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(lifekWh);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(producekWh);
    vlayout2->addSpacing(20);
    vlayout2->addWidget(totalwater);

    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(unitlifekWh);
    vlayout3->addSpacing(10);
    vlayout3->addWidget(unitproducekWh);
    vlayout3->addSpacing(20);
    vlayout3->addWidget(unittotalwater);

    hotherlayout->addSpacing(10);
    hotherlayout->addLayout(vlayout1);
    hotherlayout->addSpacing(0);
    hotherlayout->addLayout(vlayout2);
    hotherlayout->addSpacing(5);
    hotherlayout->addLayout(vlayout3);
    hotherlayout->addStretch();

}


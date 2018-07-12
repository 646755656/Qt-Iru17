#include "secondwindow.h"
#include <QPainter>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QVBoxLayout>

secondwindow::secondwindow(QWidget *parent) :
    upwinbase(parent)
{
//    setStyleSheet("secondwindow{background:rgb(200,80,140);}");

    title_row_label_init();
    first_row_label_init();     //第一行label显示
    second_row_label_init();    //第二行label显示

    llj_table_init();           //水表表格

    pump_table_init();          //泵表格

    db_table_init();            //电表表格

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(tablellj);
    hlayout->addStretch();
    hlayout->addWidget(tablepump);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(tabledb);

    QVBoxLayout *boxlayout = new QVBoxLayout;
    boxlayout->addLayout(hlayout);
    boxlayout->setSpacing(2);
//    boxlayout->addStretch();
    boxlayout->addLayout(vlayout);

    boxlayout->setGeometry(QRect(5,90,790,340));
}


void secondwindow::title_row_label_init()
{
    QLabel *labeltitle = new QLabel("二次设备:",this);
    labeltitle->setGeometry(5,3,22*5,24);
    labeltitle->setStyleSheet("font:bold;font-size:22px;font-family:楷体");

    QFontMetrics metric= labeltitle->fontMetrics(); //获取labeltitle的内容长度
    headlength = metric.width(labeltitle->text());
    labelonline = new QLabel(this);
    labelonline->setGeometry(130,5,50,24);
    labelonline->setText("在线"); //首次运行时
    labelonline->setStyleSheet("color:black;font:bold;font-size:22px;font-family:楷体");
}

void secondwindow::first_row_label_init()
{
    QLabel *titlepresslocal = new QLabel("本地压力",this);
    titlepresslocal->setFixedSize(18*5,20);
    titlepresslocal->setStyleSheet("font-size:18px;font:bold;");

    presslocal = new QLineEdit("0.000",this);
    presslocal->setFixedSize(65,20);
    presslocal->setStyleSheet("font-size:18px;font:bold;");
    presslocal->setFocusPolicy(Qt::NoFocus);

    QLabel *unitpresslocal = new QLabel("MPa",this);
    unitpresslocal->setFixedSize(40,20);
    unitpresslocal->setStyleSheet("font-size:18px;font:bold;");

    QLabel *titlepressremote = new QLabel("远端压力",this);
    titlepressremote->setFixedSize(18*5,20);
    titlepressremote->setStyleSheet("font-size:18px;font:bold;");

    pressremote = new QLineEdit("0.000",this);
    pressremote->setFixedSize(65,20);
    pressremote->setStyleSheet("font-size:18px;font:bold;");
    pressremote->setFocusPolicy(Qt::NoFocus);

    QLabel *unitpressremote = new QLabel("MPa",this);
    unitpressremote->setFixedSize(30,20);
    unitpressremote->setStyleSheet("font-size:18px;font:bold;");

    runstatus = new QLabel("常态",this);
    runstatus->setFixedSize(40,20);
    runstatus->setStyleSheet("font-size:18px;font:bold;color:red;");

    controlmode = new QLabel("本控",this);
    controlmode->setFixedSize(40,20);
    controlmode->setStyleSheet("font-size:18px;font:bold;color:red");

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(titlepresslocal);
//    hlayout->addSpacing(2);
    hlayout->addWidget(presslocal);
//    hlayout->addSpacing(1);
    hlayout->addWidget(unitpresslocal);

    hlayout->addSpacing(30);

    hlayout->addWidget(titlepressremote);
    hlayout->addSpacing(2);
    hlayout->addWidget(pressremote);
    hlayout->addSpacing(1);
    hlayout->addWidget(unitpressremote);
    hlayout->addStretch();
    hlayout->addWidget(runstatus);
    hlayout->addSpacing(30);
    hlayout->addWidget(controlmode);
    hlayout->addSpacing(10);
    hlayout->setGeometry(QRect(10,35,790,20));
}

void secondwindow::second_row_label_init()
{
    //第二行显示
    QLabel *titlepressBPset = new QLabel("变频设定压力",this);
    titlepressBPset->setFixedSize(115,20);
    titlepressBPset->setStyleSheet("font-size:18px;font:bold;");

    pressBPset = new QLineEdit("0.000",this);
    pressBPset->setFixedSize(65,20);
    pressBPset->setStyleSheet("font-size:18px;font:bold;");
    pressBPset->setFocusPolicy(Qt::NoFocus);

    QLabel *unitpressBPset = new QLabel("MPa",this);
    unitpressBPset->setFixedSize(30,20);
    unitpressBPset->setStyleSheet("font-size:18px;font:bold;");

    QLabel *titlepressgoal = new QLabel("目标压力",this);
    titlepressgoal->setFixedSize(75,20);
    titlepressgoal->setStyleSheet("font-size:18px;font:bold;");

    pressgoal = new QLineEdit("0.000",this);
    pressgoal->setFixedSize(65,20);
    pressgoal->setStyleSheet("font-size:18px;font:bold;");
    pressgoal->setFocusPolicy(Qt::NoFocus);

    QLabel *unitpressgoal = new QLabel("MPa",this);
    unitpressgoal->setFixedSize(30,20);
    unitpressgoal->setStyleSheet("font-size:18px;font:bold;");

    QLabel *titlepressfeedback = new QLabel("反馈压力",this);
    titlepressfeedback->setFixedSize(75,20);
    titlepressfeedback->setStyleSheet("font-size:18px;font:bold;");

    pressfeedback = new QLineEdit("---",this);
    pressfeedback->setFixedSize(65,20);
    pressfeedback->setStyleSheet("font-size:18px;font:bold;");
    pressfeedback->setFocusPolicy(Qt::NoFocus);

    QLabel *unitpressfeedback = new QLabel("MPa",this);
    unitpressfeedback->setFixedSize(30,20);
    unitpressfeedback->setStyleSheet("font-size:18px;font:bold;");

    QLabel *titlefrequency = new QLabel("运行频率",this);
    titlefrequency->setStyleSheet("font-size:18px;font:bold;");
    titlefrequency->setFixedSize(75,20);

    frequency = new QLineEdit("0.0",this);
    frequency->setFixedSize(50,20);
    frequency->setStyleSheet("font-size:18px;font:bold;");
    frequency->setFocusPolicy(Qt::NoFocus);

    QLabel *unitfrequency = new QLabel("Hz",this);
    unitfrequency->setFixedSize(30,20);
    unitfrequency->setStyleSheet("font-size:18px;font:bold;");

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(titlepressBPset);
    hlayout2->addSpacing(2);
    hlayout2->addWidget(pressBPset);
    hlayout2->addWidget(unitpressBPset);

    hlayout2->addSpacing(10);

    hlayout2->addWidget(titlepressgoal);
    hlayout2->addSpacing(2);
    hlayout2->addWidget(pressgoal);
    hlayout2->addWidget(unitpressgoal);

    hlayout2->addSpacing(10);

    hlayout2->addWidget(titlepressfeedback);
    hlayout2->addSpacing(2);
    hlayout2->addWidget(pressfeedback);
    hlayout2->addWidget(unitpressfeedback);

    hlayout2->addSpacing(10);

    hlayout2->addWidget(titlefrequency);
    hlayout2->addSpacing(2);
    hlayout2->addWidget(frequency);
    hlayout2->addWidget(unitfrequency);

    hlayout2->setGeometry(QRect(10,62,790,20));
}

void secondwindow::llj_table_init()
{
    tablellj = new QTableWidget(8,4,this);      //状态表格
    tablellj->setFrameShape(QFrame::NoFrame);
    tablellj->setFixedSize(392,205);

    QStringList headlabel;
    headlabel << "水表" << "瞬时(m3/h)" << "正向累积(m3)" << "负向累积(m3)";
    tablellj->setHorizontalHeaderLabels(headlabel);
    tablellj->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //设置表格行标题的对齐方式-居中
    for(int i = 0; i < 8; i++)          //设置行高
        tablellj->setRowHeight(i,22);
    tablellj->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//自适应列宽
    tablellj->verticalHeader()->hide();//隐藏行头
    tablellj->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    tablellj->horizontalHeader()->setClickable(false);//表头不可点击
    tablellj->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//表头背景
    tablellj->setSelectionMode(QAbstractItemView::NoSelection);//不能选中

    QFont font_head;//表头字体
    font_head.setPixelSize(14);
    font_head.setBold(true);
    tablellj->horizontalHeader()->setFont(font_head);
}

void secondwindow::pump_table_init()
{
    tablepump = new QTableWidget(8,5,this);      //状态表格
    tablepump->setFrameShape(QFrame::NoFrame);
    tablepump->setFixedSize(392,205);

    QStringList headlabel;
    headlabel << "泵号" << "状态" << "电流(A)" << "故障" << "报警";
    tablepump->setHorizontalHeaderLabels(headlabel);
    tablepump->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //设置表格行标题的对齐方式-居中
    for(int i = 0; i < 8; i++)          //设置行高
        tablepump->setRowHeight(i,22);
    tablepump->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//自适应列宽
    tablepump->verticalHeader()->hide();//隐藏行头
    tablepump->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    tablepump->horizontalHeader()->setClickable(false);//表头不可点击
    tablepump->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//表头背景
    tablepump->setSelectionMode(QAbstractItemView::NoSelection);//不能选中

    QFont font_head;//表头字体
    font_head.setPixelSize(14);
    font_head.setBold(true);
    tablepump->horizontalHeader()->setFont(font_head);

}

void secondwindow::db_table_init()
{
    tabledb = new QTableWidget(4,9,this);      //状态表格
    tabledb->setFrameShape(QFrame::NoFrame);
    tabledb->setFixedSize(790,120);

    QStringList headlabel;
    headlabel << "电表" << "Ua(V)" << "Ub(V)" << "Ub(V)" << "Ia(A)"<< "Ib(A)"<< "Ic(A)"<< "功率(kW)"<< "表底(kWh)";
    tabledb->setHorizontalHeaderLabels(headlabel);
    tabledb->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //设置表格行标题的对齐方式-居中
    for(int i = 0; i < 4; i++)          //设置行高
        tabledb->setRowHeight(i,22);
    tabledb->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//自适应列宽
    tabledb->verticalHeader()->hide();//隐藏行头
    tabledb->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    tabledb->horizontalHeader()->setClickable(false);//表头不可点击
    tabledb->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//表头背景
    tabledb->setSelectionMode(QAbstractItemView::NoSelection);//不能选中

    QFont font_head;//表头字体
    font_head.setPixelSize(14);
    font_head.setBold(true);
    tabledb->horizontalHeader()->setFont(font_head);
}

void secondwindow::paintEvent(QPaintEvent *)
{
    //绘制背景颜色
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    //标题下方画直线
    QPainter paint(this);
    paint.setPen(QPen(Qt::black,1));
//    paint.drawLine(5,28,5 + headlength,28);
//    paint.drawLine(5,30,5 + headlength,30);

    //水位下方画直线
//    paint.drawLine(95,54,95 + 65,54);
//    paint.drawLine(315,54,315 + 65,54);

    //画矩形
//    paint.drawRect(95,34,67,20);
//    paint.drawRect(335,34,67,20);

}

#include "analogwindow.h"
#include <QFontMetrics>
#include <QStyleOption>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QPainter>
#include <QVBoxLayout>

analogwindow::analogwindow(QWidget *parent) :
    upwinbase(parent)
{
//    setStyleSheet("analogwindow{background:rgb(80,120,140);}");

    QLabel *labeltitle = new QLabel("数据采集:",this);
    labeltitle->setGeometry(5,3,22*5,24);
    labeltitle->setStyleSheet("font:bold;font-size:22px;font-family:宋体");

    QFontMetrics metric= labeltitle->fontMetrics(); //获取labeltitle的内容长度
    headlength = metric.width(labeltitle->text());

    labelonline = new QLabel(this);
    labelonline->setGeometry(130,5,50,24);
    labelonline->setText("在线");//首次运行时
    labelonline->setStyleSheet("color:black;font:bold;font-size:22px;font-family:宋体");

    table_analog_init();
    table_dbdata_init();

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addSpacing(10);
    vlayout->addWidget(t_analog);
    vlayout->addStretch();
    vlayout->addWidget(t_dbdata);
    vlayout->addStretch();
    vlayout->setGeometry(QRect(5,35,790,400));
}


void analogwindow::paintEvent(QPaintEvent *)
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

void analogwindow::table_analog_init()
{
    t_analog = new QTableWidget(8,3,this);
    t_analog->setFrameShape(QFrame::NoFrame);
    t_analog->setFixedSize(390,210);

    QStringList headlabel;
    headlabel << "通道" << "名称" << "实际值";

    t_analog->setHorizontalHeaderLabels(headlabel);

    t_analog->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //设置表格行标题的对齐方式-居中
    for(int i = 0; i < 8; i++)          //设置行高
        t_analog->setRowHeight(i,22);
    t_analog->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//自适应列宽
    t_analog->verticalHeader()->hide();//隐藏行头
    t_analog->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    t_analog->horizontalHeader()->setClickable(false);//表头不可点击
    t_analog->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//表头背景
    t_analog->setSelectionMode(QAbstractItemView::NoSelection);//不能选中

    QFont font_head;//表头字体
    font_head.setPixelSize(14);
    font_head.setBold(true);
    t_analog->horizontalHeader()->setFont(font_head);

}

void analogwindow::table_dbdata_init()
{
    t_dbdata = new QTableWidget(4,10,this);
    t_dbdata->setFrameShape(QFrame::NoFrame);
    t_dbdata->setFixedSize(790,130);

    QStringList headlabel;
    headlabel << "电表" << "名称" << "Ua(V)" << "Ub(V)" << "Ub(V)" << "Ia(A)" << "Ib(A)" << "Ic(A)" << "功率(kW)" << "表底(kWh)";

    t_dbdata->setHorizontalHeaderLabels(headlabel);

    t_dbdata->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //设置表格行标题的对齐方式-居中
    for(int i = 0; i < 4; i++)          //设置行高
        t_dbdata->setRowHeight(i,22);
    t_dbdata->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//自适应列宽
    t_dbdata->verticalHeader()->hide();//隐藏行头
    t_dbdata->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    t_dbdata->horizontalHeader()->setClickable(false);//表头不可点击
    t_dbdata->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");//表头背景
    t_dbdata->setSelectionMode(QAbstractItemView::NoSelection);//不能选中

    QFont font_head;//表头字体
    font_head.setPixelSize(14);
    font_head.setBold(true);
    t_dbdata->horizontalHeader()->setFont(font_head);

}

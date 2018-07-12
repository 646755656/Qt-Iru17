#include "firstwindow.h"
#include <QFontMetrics>
#include <QStyleOption>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QPainter>


firstwindow::firstwindow(QWidget *parent) :
    upwinbase(parent)
{
//    setStyleSheet("firstwindow{background:rgb(80,80,40);}");

    label_row_init();

    draw_table_init();       //绘制表格初始化
}

void firstwindow::slot_onlinestatus(bool value)
{
    if(onlineflag != value)
    {
        onlineflag = value;
        if(onlineflag == 1)
        {
            labelonline->setText("在线");
            labelonline->setStyleSheet("color:black/*,font-size:14px*/");
        }
        else
        {
            labelonline->setText("断线");
            labelonline->setStyleSheet("color:red/*,font-size:14px*/");
        }
    }
}

//上方label初始化
void firstwindow::label_row_init()
{
    QLabel *labeltitle = new QLabel("一次设备:",this);
    labeltitle->setGeometry(5,3,22*5,24);
    labeltitle->setStyleSheet("font:bold;font-size:22px;font-family:宋体");

    QFontMetrics metric= labeltitle->fontMetrics(); //获取labeltitle的内容长度
    headlength = metric.width(labeltitle->text());

    labelonline = new QLabel(this);
    labelonline->setGeometry(130,5,50,24);
    labelonline->setText("在线");//首次运行时
    labelonline->setStyleSheet("color:black;font:bold;font-size:22px;font-family:宋体");

    QLabel *titlepoollevel = new QLabel("水池水位:",this);
    titlepoollevel->setStyleSheet("font-size:18px;font:bold;");
    titlepoollevel->setFixedSize(18*5,20);

    poollevel = new QLineEdit("0.00",this);
    poollevel->setStyleSheet("font-size:16px;font:bold;");
    poollevel->setFixedSize(70,20);
    poollevel->setFocusPolicy(Qt::NoFocus);

    QLabel *unitpoollevel = new QLabel("m",this);
    unitpoollevel->setStyleSheet("font-size:16px;font:bold;");
    unitpoollevel->setFixedSize(40,20);
//    unitpoollevel->setGeometry(170,35,40,20);

    QLabel *titlewelllevel = new QLabel("深井水位:",this);
    titlewelllevel->setStyleSheet("font-size:16px;font:bold;");
    titlewelllevel->setFixedSize(18*5,20);

    welllevel = new QLineEdit("0.00",this);
    welllevel->setStyleSheet("font-size:16px;font:bold;");
    welllevel->setFixedSize(70,20);
    welllevel->setFocusPolicy(Qt::NoFocus);

    QLabel *unitwelllevel = new QLabel("m",this);
    unitwelllevel->setStyleSheet("font-size:16px;font:bold;");
    unitwelllevel->setFixedSize(40,20);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addSpacing(10);
    hlayout->addWidget(titlepoollevel);
    hlayout->addWidget(poollevel);
    hlayout->addSpacing(3);
    hlayout->addWidget(unitpoollevel);
    hlayout->addSpacing(50);
    hlayout->addWidget(titlewelllevel);
    hlayout->addWidget(welllevel);
    hlayout->addSpacing(3);
    hlayout->addWidget(unitwelllevel);
    hlayout->addStretch();
    hlayout->setGeometry(QRect(5,35,790,20));
}

//绘制表格
void firstwindow::draw_table_init()
{
    t_status = new QTableWidget(8,8,this);      //状态表格
    t_data = new QTableWidget(8,12,this);

    t_status->setFrameShape(QFrame::NoFrame);
    t_data->setFrameShape(QFrame::NoFrame);

    t_status->setGeometry(5,60,790,180);
    t_data->setGeometry(5,245,790,180);

    QStringList headlabel1,headlabel2/*,rowlabel1,rowlabel2*/;
    headlabel1 << "模块" << "运行模式" << "泵状态" << "泵电流A" << "泵报警" << "变频状态" << "运行频率Hz" << "通讯状态";
    headlabel2 << "模块" << "Ua" << "Ub" << "Uc" << "Ia" << "Ib" << "Ic" << "kW" << "kWh" << "瞬时流量" << "正向累积" << "负向累积";

    t_status->setHorizontalHeaderLabels(headlabel1);
    t_data->setHorizontalHeaderLabels(headlabel2);

    //设置表格行标题的对齐方式
    t_status->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //居中
    t_data->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); //居中

    //设置行标题
//    rowlabel1 << "1#" << "2";

    //表头字体
    QFont font_head;
    font_head.setPixelSize(14);
    t_status->horizontalHeader()->setFont(font_head);
    t_data->horizontalHeader()->setFont(font_head);

    //设置行高
    for(int i = 0; i < 9; i++)
    {
        t_status->setRowHeight(i,180 / 10);
        t_data->setRowHeight(i,180 / 10);
    }
    //自适应行高
    //    t_status->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    //    t_data->verticalHeader()->setResizeMode(QHeaderView::Stretch);

    //自适应列宽
    t_status->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    t_data->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

//    t_status->horizontalHeader()->setResizeMode(0,QHeaderView::Fixed);      //固定
//    t_data->horizontalHeader()->setResizeMode(0,QHeaderView::Fixed);      //固定

//    for(int i = 0; i < 9; i++)
//        t_status->setColumnWidth(i,790 / 8);
//    for(int i = 0; i < 12; i++)
//        t_data->setColumnWidth(i,790 / 12);

    //隐藏行头
    t_status->verticalHeader()->hide();
    t_data->verticalHeader()->hide();

    //只读
    t_status->setEditTriggers(QAbstractItemView::NoEditTriggers);
    t_data->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置不显示格子
//    t_status->setShowGrid(false);

    //表头不可点击
    t_status->horizontalHeader()->setClickable(false);
    t_data->horizontalHeader()->setClickable(false);

    //表头背景
    t_status->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    t_data->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

    //表头高度
//    t_status->horizontalHeader()->setFixedHeight(20);
    //不能选中
    t_status->setSelectionMode(QAbstractItemView::NoSelection);
    t_data->setSelectionMode(QAbstractItemView::NoSelection);

}


void firstwindow::paintEvent(QPaintEvent *)
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


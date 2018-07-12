#include "devicewindow.h"
#include <QFontMetrics>
#include <QStyleOption>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>



devicewindow::devicewindow(QWidget *parent) :
    upwinbase(parent)
{
//    setStyleSheet("devicewindow{background:rgb(120,40,140);}");

    QLabel *labeltitle = new QLabel("设备操作:",this);
    labeltitle->setGeometry(5,3,22*5,24);
    labeltitle->setStyleSheet("font:bold;font-size:22px;font-family:宋体");

    QFontMetrics metric= labeltitle->fontMetrics(); //获取labeltitle的内容长度
    headlength = metric.width(labeltitle->text());

    bp_control_init();

    data_func_init();

    auxiliary_func_init();

    keyval = -1;

    kbd = new keyboard();

    disnonplanpress->installEventFilter(this);
    dissetpress->installEventFilter(this);
    firstsubnum->installEventFilter(this);

    connect(kbd,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));

}


void devicewindow::paintEvent(QPaintEvent *)
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

void devicewindow::bp_control_init()
{
    QLabel *titleBPcontrol = new QLabel("变频操作",this);
    titleBPcontrol->setFixedSize(120,30);
    titleBPcontrol->setStyleSheet("font:bold;font-size:20px");

    //非计划压力
    QLabel *titlenonplanpress = new QLabel("非计划压力",this);
    titlenonplanpress->setFixedSize(120,20);
    titlenonplanpress->setStyleSheet("font-size:18px;font:bold");

    disnonplanpress = new QLineEdit("0.000",this);
    disnonplanpress->setFixedSize(70,20);
    disnonplanpress->setStyleSheet("font-size:18px;font:bold;");

    QLabel *unitnonplanpress = new QLabel("MPa",this);
    unitnonplanpress->setFixedSize(40,20);
    unitnonplanpress->setStyleSheet("font-size:18px;font:bold;");

    QHBoxLayout *hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(titlenonplanpress);
    hlayout1->addWidget(disnonplanpress);
    hlayout1->addSpacing(5);
    hlayout1->addWidget(unitnonplanpress);

    //设定压力
    QLabel *titlesetpress = new QLabel("设定压力",this);
    titlesetpress->setFixedSize(120,20);
    titlesetpress->setStyleSheet("font-size:18px;font:bold");

    dissetpress = new QLineEdit("0.000",this);
    dissetpress->setFixedSize(70,20);
    dissetpress->setStyleSheet("font-size:18px;font:bold;");

    QLabel *unitsetpress = new QLabel("MPa",this);
    unitsetpress->setFixedSize(40,20);
    unitsetpress->setStyleSheet("font-size:18px;font:bold;");

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(titlesetpress);
    hlayout2->addWidget(dissetpress);
    hlayout2->addSpacing(5);
    hlayout2->addWidget(unitsetpress);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(titleBPcontrol);
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(15);
    vlayout->addLayout(hlayout2);

    //停止
    pbt_stopBP = new QPushButton("停止",this);
    pbt_stopBP->setFixedSize(100,50);
    pbt_stopBP->setStyleSheet("font-size:25px;font:bold;");

    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addSpacing(40);
    vlayout1->addWidget(pbt_stopBP);

    //复位
    pbt_resetBP = new QPushButton("复位",this);
    pbt_resetBP->setFixedSize(100,50);
    pbt_resetBP->setStyleSheet("font-size:25px;font:bold;");

    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addSpacing(40);
    vlayout2->addWidget(pbt_resetBP);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addSpacing(15);
    hlayout->addLayout(vlayout);
    hlayout->addStretch();
    hlayout->addLayout(vlayout1);
    hlayout->addSpacing(50);
    hlayout->addLayout(vlayout2);
    hlayout->addStretch();

    hlayout->setGeometry(QRect(5,40,790,100));

}

void devicewindow::data_func_init()
{
    QLabel *titledatafunc = new QLabel("数据功能",this);
    titledatafunc->setFixedSize(100,22);
    titledatafunc->setStyleSheet("font-size:20px;font:bold;");

    pbt_openclose = new QPushButton("关闭",this);
    pbt_openclose->setFixedSize(80,24);
    pbt_openclose->setStyleSheet("font-size:18px;font:bold;");

    QHBoxLayout *hlayout0 = new QHBoxLayout();
    hlayout0->addSpacing(10);
    hlayout0->addWidget(titledatafunc);
    hlayout0->addStretch();
    hlayout0->addWidget(pbt_openclose);
    hlayout0->addStretch();

    //一键恢复
    QLabel *titlerecover = new QLabel("一键恢复",this);
    titlerecover->setFixedSize(80,22);
    titlerecover->setStyleSheet("font-size:20px;font:bold");

    //关键操作
    QLabel *titlekeyoperate = new QLabel("关键操作",this);
    titlekeyoperate->setFixedSize(80,22);
    titlekeyoperate->setStyleSheet("font-size:20px;font:bold");

    QHBoxLayout *hlayout1 = new QHBoxLayout();
    hlayout1->addStretch();
    hlayout1->addWidget(titlerecover);
    hlayout1->addSpacing(70);
    hlayout1->addWidget(titlekeyoperate);
    hlayout1->addSpacing(20);


    //二次主模块
    QLabel *titlesecond = new QLabel("二次主模块",this);
    titlesecond->setFixedSize(120,22);
    titlesecond->setStyleSheet("font-size:20px;font:bold;");

    pbt_downsecond = new QPushButton("下发",this);
    pbt_downsecond->setEnabled(false);
    pbt_downsecond->setFixedSize(80,24);
    pbt_downsecond->setStyleSheet("font-size:18px;font:bold;color:gray;");

    //关键操作按钮
    pbt_keyoperate1 = new QPushButton("关键1",this);
    pbt_keyoperate1->setEnabled(false);
    pbt_keyoperate1->setFixedSize(80,24);
    pbt_keyoperate1->setStyleSheet("font-size:18px;font:bold;color:gray;");

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addSpacing(10);
    hlayout2->addWidget(titlesecond);
    hlayout2->addStretch();
    hlayout2->addWidget(pbt_downsecond);
    hlayout2->addSpacing(70);
    hlayout2->addWidget(pbt_keyoperate1);
    hlayout2->addSpacing(20);

    //一次主模块
    QLabel *titlefirst = new QLabel("一次主模块",this);
    titlefirst->setFixedSize(120,22);
    titlefirst->setStyleSheet("font-size:20px;font:bold;");

    pbt_downfirst = new QPushButton("下发",this);
    pbt_downfirst->setEnabled(false);
    pbt_downfirst->setFixedSize(80,24);
    pbt_downfirst->setStyleSheet("font-size:18px;font:bold;color:gray;");

    //关键操作
    pbt_keyoperate2 = new QPushButton("关键2",this);
    pbt_keyoperate2->setEnabled(false);
    pbt_keyoperate2->setFixedSize(80,24);
    pbt_keyoperate2->setStyleSheet("font-size:18px;font:bold;color:gray;");

    QHBoxLayout *hlayout3 = new QHBoxLayout();
    hlayout3->addSpacing(10);
    hlayout3->addWidget(titlefirst);
    hlayout3->addStretch();
    hlayout3->addWidget(pbt_downfirst);
    hlayout3->addSpacing(70);
    hlayout3->addWidget(pbt_keyoperate2);
    hlayout3->addSpacing(20);


    //一次从模块
    QLabel *titlefirstsub = new QLabel("一次从模块",this);
    titlefirstsub->setFixedSize(120,22);
    titlefirstsub->setStyleSheet("font-size:20px;font:bold;");

    //从模块号
    firstsubnum = new QLineEdit("1",this);
    firstsubnum->setFixedSize(45,22);
    firstsubnum->setAlignment(Qt::AlignCenter);
    firstsubnum->setStyleSheet("font-size:20px;font:bold;");

    pbt_downfirstsub = new QPushButton("下发",this);
    pbt_downfirstsub->setEnabled(false);
    pbt_downfirstsub->setFixedSize(80,24);
    pbt_downfirstsub->setStyleSheet("font-size:18px;font:bold;color:gray;");

    //关键操作
    pbt_keyoperate3 = new QPushButton("关键3",this);
    pbt_keyoperate3->setEnabled(false);
    pbt_keyoperate3->setFixedSize(80,24);
    pbt_keyoperate3->setStyleSheet("font-size:18px;font:bold;color:gray;");

    QHBoxLayout *hlayout4 = new QHBoxLayout();
    hlayout4->addSpacing(10);
    hlayout4->addWidget(titlefirstsub);
    hlayout4->addSpacing(30);
    hlayout4->addWidget(firstsubnum);
    hlayout4->addStretch();
    hlayout4->addWidget(pbt_downfirstsub);
    hlayout4->addSpacing(70);
    hlayout4->addWidget(pbt_keyoperate3);
    hlayout4->addSpacing(20);

    //采集模块
    QLabel *titleanalog = new QLabel("采集模块",this);
    titleanalog->setFixedSize(120,22);
    titleanalog->setStyleSheet("font-size:20px;font:bold;");

    pbt_downanalog = new QPushButton("下发",this);
    pbt_downanalog->setFixedSize(80,24);
    pbt_downanalog->setEnabled(false);
    pbt_downanalog->setStyleSheet("font-size:18px;font:bold;color:gray;");

    QHBoxLayout *hlayout5 = new QHBoxLayout();
    hlayout5->addSpacing(10);
    hlayout5->addWidget(titleanalog);
    hlayout5->addStretch();
    hlayout5->addWidget(pbt_downanalog);
    hlayout5->addSpacing(20+80+70);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout0);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout2);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout3);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout4);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout5);
    vlayout->addStretch();
    vlayout->setGeometry(QRect(5,180,520,300));

}

void devicewindow::auxiliary_func_init()
{
    QLabel *titleauxiliary = new QLabel("辅助功能",this);
    titleauxiliary->setFixedSize(100,25);
    titleauxiliary->setStyleSheet("font-size:22px;font:bold;");

    pbt_correcttime = new QPushButton("校时",this);
    pbt_correcttime->setFixedSize(80,30);
    pbt_correcttime->setStyleSheet("font-size:20px;font:bold;");

    pbt_calibratescreen = new QPushButton("校屏",this);
    pbt_calibratescreen->setFixedSize(80,30);
    pbt_calibratescreen->setStyleSheet("font-size:20px;font:bold");

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addSpacing(20);
    vlayout->addWidget(titleauxiliary);
    vlayout->addSpacing(20);
    vlayout->addWidget(pbt_correcttime);
    vlayout->addSpacing(20);
    vlayout->addWidget(pbt_calibratescreen);
    vlayout->addStretch();
    vlayout->setGeometry(QRect(600,180,190,300));

}

bool devicewindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (watched == disnonplanpress)
            keyval = 1;
        else if(watched == dissetpress)
            keyval = 2;
        else if(watched == firstsubnum)
            keyval = 3;
        if(keyval != -1)
        {
            kbd->setAttribute(Qt::WA_ShowModal,true);
            kbd->show();
            return true;
        }
        return false;
    }
}

void devicewindow::receiveData(QString data)
{
    if(keyval != -1)
    {
        if(keyval == 1)
        {
            QRegExp re("(([0-2])|([0-2]\\.\\d{1,3}))");
            bool flag = re.exactMatch(data);
            if(flag == true)
            {
                double val = data.toDouble();
                QString result = QString::number(val,'f',3);  //设置小数点位数
                disnonplanpress->setText(result);
            }
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~2.999，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval == 2)
        {
            QRegExp re("(([0-2])|([0-2]\\.\\d{1,3}))");
            bool flag = re.exactMatch(data);
            if(flag == true)
            {
                double val = data.toDouble();
                QString result = QString::number(val,'f',3);  //设置小数点位数
                dissetpress->setText(result);
            }
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~2.999，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval == 3)
        {
            QRegExp re("[1-8]");
            bool flag = re.exactMatch(data);
            if(flag == true)
                firstsubnum->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为1~8，请重新输入！",QMessageBox::Ok);
        }

        keyval = -1;
    }

}

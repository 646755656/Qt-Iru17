#include "runplanwindow.h"
#include <QFontMetrics>
#include <QStyleOption>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QRegExp>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QSettings>
#include "globle.h"

runplanwindow::runplanwindow(QWidget *parent) :
    upwinbase(parent)
{
//    setStyleSheet("runplanwindow{background:rgb(80,120,140);}");

    //文件读取
    Read_RunPlan_Config_File();

    title_display_init();
    peak_time_display_init();       //峰时间段
    BP_time_display_init();         //变频时间段
    local_press_display_init();     //本地压力
    remote_press_display_init();    //末端压力
    valley_time_display_init();     //谷时间段
    save_down_display_init();       //保存下发按钮

    for(int i = 0;i < 3; i++)
    {
        peaktime[i].disbghour->installEventFilter(this);
        peaktime[i].disbgmin->installEventFilter(this);
        peaktime[i].disendhour->installEventFilter(this);
        peaktime[i].disendmin->installEventFilter(this);

        bptime[i].disbghour->installEventFilter(this);
        bptime[i].disbgmin->installEventFilter(this);
        bptime[i].disendhour->installEventFilter(this);
        bptime[i].disendmin->installEventFilter(this);
    }

    valleytime.disbghour->installEventFilter(this);
    valleytime.disbgmin->installEventFilter(this);
    valleytime.disendhour->installEventFilter(this);
    valleytime.disendmin->installEventFilter(this);


    keyval = -1;       //初始化为-1
    kbd = new keyboard();
    //关联信号和槽函数
    connect(kbd, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
}

void runplanwindow::paintEvent(QPaintEvent *)
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

void runplanwindow::title_display_init()
{
    QLabel *labeltitle = new QLabel("运行计划:",this);
    labeltitle->setGeometry(5,3,22*5,24);
    labeltitle->setStyleSheet("font:bold;font-size:22px;font-family:宋体");

    QFontMetrics metric= labeltitle->fontMetrics(); //获取labeltitle的内容长度
    headlength = metric.width(labeltitle->text());
}

void runplanwindow::peak_time_display_init()
{
    QLabel *titlepeak[3];
    titlepeak[0] = new QLabel("峰时段1",this);
    titlepeak[1] = new QLabel("峰时段2",this);
    titlepeak[2] = new QLabel("峰时段3",this);

    for(unsigned char i = 0; i < 3; i++)
    {
        titlepeak[i]->setFixedSize(70,20);
        titlepeak[i]->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    }

    //数据
    for(unsigned char i = 0; i < 3; i++)        //峰时间段
    {
        peaktime[i].disbghour     = new QLineEdit(QString::number(RunPlan::TimePeak[i].BgHour,10),this);
        peaktime[i].disbgmin      = new QLineEdit(QString::number(RunPlan::TimePeak[i].BgMin,10),this);
        peaktime[i].disendhour    = new QLineEdit(QString::number(RunPlan::TimePeak[i].EndHour,10),this);
        peaktime[i].disendmin     = new QLineEdit(QString::number(RunPlan::TimePeak[i].EndMin,10),this);
    }

    for(unsigned char i = 0; i < 3; i++)
    {
        peaktime[i].disbghour->setFixedSize(30,20);
        peaktime[i].disbgmin->setFixedSize(30,20);
        peaktime[i].disendhour->setFixedSize(30,20);
        peaktime[i].disendmin->setFixedSize(30,20);

        peaktime[i].disbghour->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        peaktime[i].disbgmin->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        peaktime[i].disendhour->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        peaktime[i].disendmin->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

        peaktime[i].disbghour->setAlignment(Qt::AlignCenter);
        peaktime[i].disbgmin->setAlignment(Qt::AlignCenter);
        peaktime[i].disendhour->setAlignment(Qt::AlignCenter);
        peaktime[i].disendmin->setAlignment(Qt::AlignCenter);

    }


    //时分
    for(unsigned char i = 0; i < 3; i++)
    {
        peaktime[i].labelbghourunit   = new QLabel("时:",this);
        peaktime[i].labelbgminunit    = new QLabel("分 - ",this);
        peaktime[i].labelendhourunit  = new QLabel("时:",this);
        peaktime[i].labelendminunit   = new QLabel("分",this);

        peaktime[i].labelbghourunit->setFixedSize(30,20);
        peaktime[i].labelbgminunit->setFixedSize(50,20);
        peaktime[i].labelendhourunit->setFixedSize(30,20);
        peaktime[i].labelendminunit->setFixedSize(30,20);

        peaktime[i].labelbghourunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        peaktime[i].labelbgminunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        peaktime[i].labelendhourunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        peaktime[i].labelendminunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    }


    //峰时间段
    QHBoxLayout *hlayout[3];
    for(unsigned char i = 0; i < 3; i++)
    {
        hlayout[i] = new QHBoxLayout();
        hlayout[i]->addWidget(titlepeak[i]);
        hlayout[i]->addSpacing(5);
        hlayout[i]->addWidget(peaktime[i].disbghour);     //显示数据位置
        hlayout[i]->addWidget(peaktime[i].labelbghourunit);     //时
        hlayout[i]->addWidget(peaktime[i].disbgmin);
        hlayout[i]->addWidget(peaktime[i].labelbgminunit);     //分
        hlayout[i]->addWidget(peaktime[i].disendhour);
        hlayout[i]->addWidget(peaktime[i].labelendhourunit);     //时
        hlayout[i]->addWidget(peaktime[i].disendmin);
        hlayout[i]->addWidget(peaktime[i].labelendminunit);     //分
//        hlayout[i]->addStretch();
    }

    QVBoxLayout *vlayoutpeak = new QVBoxLayout();
    for(unsigned char i = 0; i < 3; i++)
        vlayoutpeak->addLayout(hlayout[i]);

    vlayoutpeak->setGeometry(QRect(10,50,390,100));

}

void runplanwindow::valley_time_display_init()      //谷时间段
{
    QLabel *titlevalley;
    titlevalley = new QLabel("谷时段",this);

    titlevalley->setFixedSize(70,20);
    titlevalley->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    //数据显示
    valleytime.disbghour     = new QLineEdit(QString::number(RunPlan::TimeValley.BgHour,10),this);
    valleytime.disbgmin      = new QLineEdit(QString::number(RunPlan::TimeValley.BgMin,10),this);
    valleytime.disendhour    = new QLineEdit(QString::number(RunPlan::TimeValley.EndHour,10),this);
    valleytime.disendmin     = new QLineEdit(QString::number(RunPlan::TimeValley.EndMin,10),this);

    valleytime.disbghour->setFixedSize(30,20);
    valleytime.disbgmin->setFixedSize(30,20);
    valleytime.disendhour->setFixedSize(30,20);
    valleytime.disendmin->setFixedSize(30,20);

    valleytime.disbghour->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    valleytime.disbgmin->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    valleytime.disendhour->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    valleytime.disendmin->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    valleytime.disbghour->setAlignment(Qt::AlignCenter);
    valleytime.disbgmin->setAlignment(Qt::AlignCenter);
    valleytime.disendhour->setAlignment(Qt::AlignCenter);
    valleytime.disendmin->setAlignment(Qt::AlignCenter);

    //时分
    valleytime.labelbghourunit   = new QLabel("时:",this);
    valleytime.labelbgminunit    = new QLabel("分 - ",this);
    valleytime.labelendhourunit  = new QLabel("时:",this);
    valleytime.labelendminunit   = new QLabel("分",this);

    valleytime.labelbghourunit->setFixedSize(30,20);
    valleytime.labelbgminunit->setFixedSize(50,20);
    valleytime.labelendhourunit->setFixedSize(30,20);
    valleytime.labelendminunit->setFixedSize(30,20);

    valleytime.labelbghourunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    valleytime.labelbgminunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    valleytime.labelendhourunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    valleytime.labelendminunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QHBoxLayout *hlayout1;
    hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(titlevalley);
    hlayout1->addSpacing(5);
    hlayout1->addWidget(valleytime.disbghour);     //显示数据位置
    hlayout1->addWidget(valleytime.labelbghourunit);     //时
    hlayout1->addWidget(valleytime.disbgmin);
    hlayout1->addWidget(valleytime.labelbgminunit);     //分
    hlayout1->addWidget(valleytime.disendhour);
    hlayout1->addWidget(valleytime.labelendhourunit);     //时
    hlayout1->addWidget(valleytime.disendmin);
    hlayout1->addWidget(valleytime.labelendminunit);     //分

    QLabel *titledisnonplanpress = new QLabel("非计划压力",this);
    titledisnonplanpress->setFixedSize(110,25);
    titledisnonplanpress->setStyleSheet("font-size:20px;font:bold;font-family:宋体");

    disnonplanpress = new QLineEdit(QString::number(RunPlan::PressNonPlan,'f',3),this);
    disnonplanpress->setFixedSize(70,25);
    disnonplanpress->setStyleSheet("font-size:20px;font:bold;");

    QLabel *unitnonplanpress = new QLabel("MPa",this);
    unitnonplanpress->setFixedSize(40,25);
    unitnonplanpress->setStyleSheet("font-size:20px;font:bold;");

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addSpacing(10);
    hlayout2->addWidget(titledisnonplanpress);
    hlayout2->addSpacing(10);
    hlayout2->addWidget(disnonplanpress);
    hlayout2->addSpacing(5);
    hlayout2->addWidget(unitnonplanpress);
    hlayout2->addStretch();

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout2);

    vlayout->setGeometry(QRect(410,50,390,100));


}

void runplanwindow::local_press_display_init()
{
    QLabel *titlelocalpress = new QLabel("本地压力",this);
    titlelocalpress->setFixedSize(120,30);
    titlelocalpress->setStyleSheet("font-size:25px;font:bold;font-family:宋体");

    //标题
    QLabel *titlepeakpress     = new QLabel("峰压力",this);
    titlepeakpress->setFixedSize(60,20);
    titlepeakpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *titlevalleypress   = new QLabel("谷压力",this);
    titlevalleypress->setFixedSize(60,20);
    titlevalleypress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *titleflatpress     = new QLabel("平压力",this);
    titleflatpress->setFixedSize(60,20);
    titleflatpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    //数据
    localpress.dispeakpress     = new QLineEdit(QString::number(RunPlan::PressLocalPeak,'f',3),this);
    localpress.dispeakpress->setFixedSize(70,20);
    localpress.dispeakpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    localpress.dispeakpress->setFocusPolicy(Qt::NoFocus);

    localpress.disvalleypress   = new QLineEdit(QString::number(RunPlan::PressLocalVally,'f',3),this);
    localpress.disvalleypress->setFixedSize(70,20);
    localpress.disvalleypress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    localpress.disvalleypress->setFocusPolicy(Qt::NoFocus);

    localpress.disflatpress     = new QLineEdit(QString::number(RunPlan::PressLocalFlat,'f',3),this);
    localpress.disflatpress->setFixedSize(70,20);
    localpress.disflatpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    localpress.disflatpress->setFocusPolicy(Qt::NoFocus);

    //单位
    QLabel *unitpeakpress     = new QLabel("MPa",this);
    unitpeakpress->setFixedSize(30,20);
    unitpeakpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *unitvalleypress   = new QLabel("MPa",this);
    unitvalleypress->setFixedSize(30,20);
    unitvalleypress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *unitflatpress     = new QLabel("MPa",this);
    unitflatpress->setFixedSize(30,20);
    unitflatpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QHBoxLayout *hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(titlepeakpress);
    hlayout1->addWidget(localpress.dispeakpress);
    hlayout1->addWidget(unitpeakpress);

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(titlevalleypress);
    hlayout2->addWidget(localpress.disvalleypress);
    hlayout2->addWidget(unitvalleypress);

    QHBoxLayout *hlayout3 = new QHBoxLayout();
    hlayout3->addWidget(titleflatpress);
    hlayout3->addWidget(localpress.disflatpress);
    hlayout3->addWidget(unitflatpress);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addSpacing(20);
    hlayout->addWidget(titlelocalpress);
    hlayout->addSpacing(20);
    hlayout->addLayout(vlayout);
    hlayout->addStretch();

    hlayout->setGeometry(QRect(10,180,390,100));

}

void runplanwindow::remote_press_display_init()
{
    QLabel *titleremotepress = new QLabel("远端压力",this);
    titleremotepress->setFixedSize(120,30);
    titleremotepress->setStyleSheet("font-size:25px;font:bold;font-family:宋体");

    //标题
    QLabel *titlepeakpress     = new QLabel("峰压力",this);
    titlepeakpress->setFixedSize(60,20);
    titlepeakpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *titlevalleypress   = new QLabel("谷压力",this);
    titlevalleypress->setFixedSize(60,20);
    titlevalleypress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *titleflatpress     = new QLabel("平压力",this);
    titleflatpress->setFixedSize(60,20);
    titleflatpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");



    //数据
    remotepress.dispeakpress     = new QLineEdit(QString::number(RunPlan::PressRemotePeak,'f',3),this);
    remotepress.dispeakpress->setFixedSize(70,20);
    remotepress.dispeakpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    remotepress.dispeakpress->setFocusPolicy(Qt::NoFocus);

    remotepress.disvalleypress   = new QLineEdit(QString::number(RunPlan::PressRemoteVally,'f',3),this);
    remotepress.disvalleypress->setFixedSize(70,20);
    remotepress.disvalleypress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    remotepress.disvalleypress->setFocusPolicy(Qt::NoFocus);

    remotepress.disflatpress     = new QLineEdit(QString::number(RunPlan::PressRemoteFlat,'f',3),this);
    remotepress.disflatpress->setFixedSize(70,20);
    remotepress.disflatpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    remotepress.disflatpress->setFocusPolicy(Qt::NoFocus);



    //单位
    QLabel *unitpeakpress     = new QLabel("MPa",this);
    unitpeakpress->setFixedSize(30,20);
    unitpeakpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *unitvalleypress   = new QLabel("MPa",this);
    unitvalleypress->setFixedSize(30,20);
    unitvalleypress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QLabel *unitflatpress     = new QLabel("MPa",this);
    unitflatpress->setFixedSize(30,20);
    unitflatpress->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QHBoxLayout *hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(titlepeakpress);
    hlayout1->addWidget(remotepress.dispeakpress);
    hlayout1->addWidget(unitpeakpress);

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(titlevalleypress);
    hlayout2->addWidget(remotepress.disvalleypress);
    hlayout2->addWidget(unitvalleypress);

    QHBoxLayout *hlayout3 = new QHBoxLayout();
    hlayout3->addWidget(titleflatpress);
    hlayout3->addWidget(remotepress.disflatpress);
    hlayout3->addWidget(unitflatpress);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addStretch();
    hlayout->addWidget(titleremotepress);
    hlayout->addSpacing(30);
    hlayout->addLayout(vlayout);
    hlayout->addStretch();

    hlayout->setGeometry(QRect(410,180,390,100));

}

void runplanwindow::BP_time_display_init()
{
    for(unsigned char i = 0; i < 3; i++)        //变频时间段
    {
        bptime[i].disbghour     = new QLineEdit(QString::number(RunPlan::TimeBp[i].BgHour,10),this);
        bptime[i].disbgmin      = new QLineEdit(QString::number(RunPlan::TimeBp[i].BgMin,10),this);
        bptime[i].disendhour    = new QLineEdit(QString::number(RunPlan::TimeBp[i].EndHour,10),this);
        bptime[i].disendmin     = new QLineEdit(QString::number(RunPlan::TimeBp[i].EndMin,10),this);
    }

    QLabel *bpcontrol = new QLabel("变频控制",this);
    bpcontrol->setFixedSize(80,20);
    bpcontrol->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    bpvalid = new QComboBox(this);
    bpvalid->addItem("无 效");
    bpvalid->addItem("有 效");
    bpvalid->setCurrentIndex(RunPlan::BpControlValid);

    bpvalid->setFixedSize(80,22);
    bpvalid->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

    QHBoxLayout *hlayoutbp = new QHBoxLayout();
    hlayoutbp->addSpacing(10);
    hlayoutbp->addWidget(bpcontrol);
    hlayoutbp->addSpacing(30);
    hlayoutbp->addWidget(bpvalid);
    hlayoutbp->addStretch();

    QLabel *titlebp[3];
    titlebp[0] = new QLabel("时段1",this);
    titlebp[1] = new QLabel("时段2",this);
    titlebp[2] = new QLabel("时段3",this);

    for(unsigned char i = 0; i < 3; i++)
    {
        titlebp[i]->setFixedSize(60,20);
        titlebp[i]->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    }


    //数据
    for(unsigned char i = 0; i < 3; i++)
    {
        bptime[i].disbghour->setFixedSize(30,20);
        bptime[i].disbgmin->setFixedSize(30,20);
        bptime[i].disendhour->setFixedSize(30,20);
        bptime[i].disendmin->setFixedSize(30,20);

        bptime[i].disbghour->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        bptime[i].disbgmin->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        bptime[i].disendhour->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        bptime[i].disendmin->setStyleSheet("font-size:18px;font:bold;font-family:宋体");

        bptime[i].disbghour->setAlignment(Qt::AlignCenter);
        bptime[i].disbgmin->setAlignment(Qt::AlignCenter);
        bptime[i].disendhour->setAlignment(Qt::AlignCenter);
        bptime[i].disendmin->setAlignment(Qt::AlignCenter);

    }

    //时分
    for(unsigned char i = 0; i < 3; i++)
    {
        bptime[i].labelbghourunit   = new QLabel("时:",this);
        bptime[i].labelbgminunit    = new QLabel("分 - ",this);
        bptime[i].labelendhourunit  = new QLabel("时:",this);
        bptime[i].labelendminunit   = new QLabel("分",this);

        bptime[i].labelbghourunit->setFixedSize(30,20);
        bptime[i].labelbgminunit->setFixedSize(50,20);
        bptime[i].labelendhourunit->setFixedSize(30,20);
        bptime[i].labelendminunit->setFixedSize(30,20);

        bptime[i].labelbghourunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        bptime[i].labelbgminunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        bptime[i].labelendhourunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
        bptime[i].labelendminunit->setStyleSheet("font-size:18px;font:bold;font-family:宋体");
    }

    QHBoxLayout *hlayout[3];
    for(unsigned char i = 0; i < 3; i++)
    {
        hlayout[i] = new QHBoxLayout();
        hlayout[i]->addWidget(titlebp[i]);
        hlayout[i]->addSpacing(5);
        hlayout[i]->addWidget(bptime[i].disbghour);     //显示数据位置
        hlayout[i]->addWidget(bptime[i].labelbghourunit);     //时
        hlayout[i]->addWidget(bptime[i].disbgmin);
        hlayout[i]->addWidget(bptime[i].labelbgminunit);     //分
        hlayout[i]->addWidget(bptime[i].disendhour);
        hlayout[i]->addWidget(bptime[i].labelendhourunit);     //时
        hlayout[i]->addWidget(bptime[i].disendmin);
        hlayout[i]->addWidget(bptime[i].labelendminunit);     //分
//        hlayout[i]->addStretch();
    }

    QVBoxLayout *vlayoutbp = new QVBoxLayout();
    vlayoutbp->addLayout(hlayoutbp);
    vlayoutbp->addSpacing(10);
    for(unsigned char i = 0; i < 3; i++)
    {
        vlayoutbp->addLayout(hlayout[i]);
//        vlayoutbp->addSpacing(5);
    }

    vlayoutbp->setGeometry(QRect(10,300,390,110));

}

void runplanwindow::save_down_display_init()
{
    pbt_save_send = new QPushButton("保存下发",this);
    pbt_save_send->setFixedSize(140,30);
    pbt_save_send->setStyleSheet("font-size:20px;font:bold");

    QHBoxLayout *hlayoutpbt = new QHBoxLayout();
    hlayoutpbt->addStretch();
    hlayoutpbt->addWidget(pbt_save_send);
    hlayoutpbt->addStretch();

    QVBoxLayout *vlayoutpbt = new QVBoxLayout();
    vlayoutpbt->addStretch();
    vlayoutpbt->addLayout(hlayoutpbt);
    vlayoutpbt->addStretch();
    vlayoutpbt->setGeometry(QRect(410,300,390,110));


}

bool runplanwindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (watched == valleytime.disbghour)
            keyval = 24;
        else if(watched == valleytime.disbgmin)
            keyval = 25;
        else if(watched == valleytime.disendhour)
            keyval = 26;
        else if(watched == valleytime.disendmin)
            keyval = 27;
        if(keyval != -1)
        {
            kbd->setAttribute(Qt::WA_ShowModal,true);
            kbd->show();
            return true;
        }

        for(int i = 0; i < 3; i++)
        {
            if (watched == peaktime[i].disbghour)
                keyval = i;
            else if(watched == peaktime[i].disbgmin)
                keyval = i + 3;
            else if(watched == peaktime[i].disendhour)
                keyval = i + 6;
            else if(watched == peaktime[i].disendmin)
                keyval = i + 9;

            else if (watched == bptime[i].disbghour)
                keyval = i + 12;
            else if(watched == bptime[i].disbgmin)
                keyval = i + 15;
            else if(watched == bptime[i].disendhour)
                keyval = i + 18;
            else if(watched == bptime[i].disendmin)
                keyval = i + 21;

            if(keyval != -1)
            {
                kbd->setAttribute(Qt::WA_ShowModal,true);
                kbd->show();
                return true;
            }
        }
        return false;
    }
    return false;
}

void runplanwindow::Read_RunPlan_Config_File()
{
    char i = 0;
    QString name;
    QString filepath = "../IRU17/ini/runplan.ini";
    QFile file(filepath);
    bool openflag = file.open(QIODevice::ReadWrite | QIODevice::Text);
    if(openflag == false)
        return;
//    qDebug() << QObject::tr("绝对路径：") << info.absolutePath() << endl
//                <<QObject::tr("文件大小：") << info.size();

    QFileInfo info(file);
    int filesize = info.size();
    QSettings setting(filepath,QSettings::IniFormat);
    if(filesize == 0)   //文件为空
    {
        setting.setValue("VER",RunPlan::ParaFileVer);

        for(i = 0; i < 3; i++)
        {
            name = QString().sprintf("PEAKTIME/BgHour%d",i);
            setting.setValue(name,RunPlan::TimePeak[i].BgHour);
            name = QString().sprintf("PEAKTIME/BgMin%d",i);
            setting.setValue(name,RunPlan::TimePeak[i].BgMin);
            name = QString().sprintf("PEAKTIME/EndHour%d",i);
            setting.setValue(name,RunPlan::TimePeak[i].EndHour);
            name = QString().sprintf("PEAKTIME/EndMin%d",i);
            setting.setValue(name,RunPlan::TimePeak[i].EndMin);

            name = QString().sprintf("BPTIME/BgHour%d",i);
            setting.setValue(name,RunPlan::TimeBp[i].BgHour);
            name = QString().sprintf("BPTIME/BgMin%d",i);
            setting.setValue(name,RunPlan::TimeBp[i].BgMin);
            name = QString().sprintf("BPTIME/EndHour%d",i);
            setting.setValue(name,RunPlan::TimeBp[i].EndHour);
            name = QString().sprintf("BPTIME/EndMin%d",i);
            setting.setValue(name,RunPlan::TimeBp[i].EndMin);

        }
        setting.setValue("VALLEYTIME/BgHour",RunPlan::TimeValley.BgHour);
        setting.setValue("VALLEYTIME/BgMin",RunPlan::TimeValley.BgMin);
        setting.setValue("VALLEYTIME/EndHour",RunPlan::TimeValley.EndHour);
        setting.setValue("VALLEYTIME/EndMin",RunPlan::TimeValley.EndMin);

        setting.setValue("PRESS/NONPLAN",RunPlan::PressNonPlan);

        setting.setValue("PRESS/LOCALPEAK",RunPlan::PressLocalPeak);
        setting.setValue("PRESS/LOCALVALLEY",RunPlan::PressLocalVally);
        setting.setValue("PRESS/LOCALFLAT",RunPlan::PressLocalFlat);

        setting.setValue("PRESS/REMOTEPEAK",RunPlan::PressRemotePeak);
        setting.setValue("PRESS/REMOTEVALLEY",RunPlan::PressRemoteVally);
        setting.setValue("PRESS/REMOTEFLAT",RunPlan::PressRemoteFlat);

        setting.setValue("BPCONTROLVALID",RunPlan::BpControlValid);

    }
    else
    {
        RunPlan::ParaFileVer = (unsigned char)setting.value("VER").toInt();
        for(i = 0; i < 3; i++)
        {
            name = QString().sprintf("PEAKTIME/BgHour%d",i);
            RunPlan::TimePeak[i].BgHour = (unsigned char)setting.value(name).toInt();
            name = QString().sprintf("PEAKTIME/BgMin%d",i);
            RunPlan::TimePeak[i].BgMin = (unsigned char)setting.value(name).toInt();
            name = QString().sprintf("PEAKTIME/EndHour%d",i);
            RunPlan::TimePeak[i].EndHour = (unsigned char)setting.value(name).toInt();
            name = QString().sprintf("PEAKTIME/EndMin%d",i);
            RunPlan::TimePeak[i].EndMin = (unsigned char)setting.value(name).toInt();

            name = QString().sprintf("BPTIME/BgHour%d",i);
            RunPlan::TimeBp[i].BgHour = (unsigned char)setting.value(name).toInt();
            name = QString().sprintf("BPTIME/BgMin%d",i);
            RunPlan::TimeBp[i].BgMin = (unsigned char)setting.value(name).toInt();
            name = QString().sprintf("BPTIME/EndHour%d",i);
            RunPlan::TimeBp[i].EndHour = (unsigned char)setting.value(name).toInt();
            name = QString().sprintf("BPTIME/EndMin%d",i);
            RunPlan::TimeBp[i].EndMin = (unsigned char)setting.value(name).toInt();
        }
        RunPlan::TimeValley.BgHour = (unsigned char)setting.value("VALLEYTIME/BgHour").toInt();
        RunPlan::TimeValley.BgMin = (unsigned char)setting.value("VALLEYTIME/BgMin").toInt();
        RunPlan::TimeValley.EndHour = (unsigned char)setting.value("VALLEYTIME/EndHour").toInt();
        RunPlan::TimeValley.EndMin = (unsigned char)setting.value("VALLEYTIME/EndMin").toInt();

        RunPlan::PressNonPlan = setting.value("PRESS/NONPLAN").toDouble();
        RunPlan::PressLocalPeak = setting.value("PRESS/LOCALPEAK").toDouble();
        RunPlan::PressLocalVally = setting.value("PRESS/LOCALVALLEY").toDouble();
        RunPlan::PressLocalFlat = setting.value("PRESS/LOCALFLAT").toDouble();

        RunPlan::PressRemotePeak = setting.value("PRESS/REMOTEPEAK").toDouble();
        RunPlan::PressRemoteVally = setting.value("PRESS/REMOTEVALLEY").toDouble();
        RunPlan::PressRemoteFlat = setting.value("PRESS/REMOTEFLAT").toDouble();

        RunPlan::BpControlValid = (unsigned char)setting.value("BPCONTROLVALID").toInt();


    }




    if(openflag)
    {
        file.seek(0);
        QByteArray array;
//        array = file.read(5);
    }
}

void runplanwindow::receiveData(QString data)
{
    if(keyval != -1)
    {
        if(keyval < 3)
        {
            QRegExp re("([01]?[0-9]|2[0-3])");
            bool flag = re.exactMatch(data);
            if(flag == true)
                peaktime[keyval].disbghour->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~23，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval < 6)
        {
            QRegExp re("([0-9]|([0-5][0-9]))");
            bool flag = re.exactMatch(data);
            if(flag == true)
                peaktime[keyval - 3].disbgmin->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~59，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval < 9)
        {
            QRegExp re("([01]?[0-9]|2[0-3])");
            bool flag = re.exactMatch(data);
            if(flag == true)
                peaktime[keyval - 6].disendhour->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~23，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval < 12)
        {
            QRegExp re("([0-9]|([0-5][0-9]))");
            bool flag = re.exactMatch(data);
            if(flag == true)
                peaktime[keyval - 9].disendmin->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~59，请重新输入！",QMessageBox::Ok);
        }

        else if(keyval < 15)
        {
            QRegExp re("([01]?[0-9]|2[0-3])");
            bool flag = re.exactMatch(data);
            if(flag == true)
                bptime[keyval - 12].disbghour->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~23，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval < 18)
        {
            QRegExp re("([0-9]|([0-5][0-9]))");
            bool flag = re.exactMatch(data);
            if(flag == true)
                bptime[keyval - 15].disbgmin->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~59，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval < 21)
        {
            QRegExp re("([01]?[0-9]|2[0-3])");
            bool flag = re.exactMatch(data);
            if(flag == true)
                bptime[keyval - 18].disendhour->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~23，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval < 24)
        {
            QRegExp re("([0-9]|([0-5][0-9]))");
            bool flag = re.exactMatch(data);
            if(flag == true)
                bptime[keyval - 21].disendmin->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~59，请重新输入！",QMessageBox::Ok);
        }

        else if(keyval == 24)
        {
            QRegExp re("([01]?[0-9]|2[0-3])");
            bool flag = re.exactMatch(data);
            if(flag == true)
                valleytime.disbghour->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~23，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval == 25)
        {
            QRegExp re("([0-9]|([0-5][0-9]))");
            bool flag = re.exactMatch(data);
            if(flag == true)
                valleytime.disbgmin->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~59，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval == 26)
        {
            QRegExp re("([01]?[0-9]|2[0-3])");
            bool flag = re.exactMatch(data);
            if(flag == true)
                valleytime.disendhour->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~23，请重新输入！",QMessageBox::Ok);
        }
        else if(keyval == 27)
        {
            QRegExp re("([0-9]|([0-5][0-9]))");
            bool flag = re.exactMatch(data);
            if(flag == true)
                valleytime.disendmin->setText(data);
            else
                QMessageBox::warning(NULL,"错误","输入范围为0~59，请重新输入！",QMessageBox::Ok);
        }

        keyval = -1;
    }
}


#ifndef RUNPLANWINDOW_H
#define RUNPLANWINDOW_H
#include "upwinbase.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "keyboard.h"

class BE_Time_Dis
{
public:
//    unsigned char bg_hour;
//    unsigned char bg_min;
//    unsigned char end_hour;
//    unsigned char end_min;

    QLineEdit *disbghour;        //显示数据
    QLineEdit *disbgmin;
    QLineEdit *disendhour;
    QLineEdit *disendmin;

    QLabel *labelbghourunit;
    QLabel *labelbgminunit;
    QLabel *labelendhourunit;
    QLabel *labelendminunit;
};

class press_data
{
public:
//    double peakpress;
//    double valleypress;
//    double flatpress;

    QLineEdit *dispeakpress;
    QLineEdit *disvalleypress;
    QLineEdit *disflatpress;
};

class runplanwindow : public upwinbase
{
    Q_OBJECT
public:
    explicit runplanwindow(QWidget *parent = 0);

    QComboBox *bpvalid;     //变频有效性

    BE_Time_Dis peaktime[3];

    BE_Time_Dis valleytime;

    BE_Time_Dis bptime[3];

    press_data remotepress;
    press_data localpress;

//    double nonplanpress;
    QLineEdit *disnonplanpress;

    QPushButton *pbt_save_send;     //保存下发


signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    int headlength;

    keyboard *kbd;

    int keyval;        //用来判断事件返回对应的lineedit

    void title_display_init();
    void peak_time_display_init();
    void valley_time_display_init();
    void remote_press_display_init();
    void local_press_display_init();
    void BP_time_display_init();
    void save_down_display_init();

    bool eventFilter ( QObject * watched, QEvent * event );

    void Read_RunPlan_Config_File();        //读配置文件
private slots:
    void receiveData(QString data);   //接收传递过来的数据的槽


public slots:

};

#endif // RUNPLANWINDOW_H

#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include "upwinbase.h"
#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>

class secondwindow : public upwinbase
{
    Q_OBJECT
public:
    explicit secondwindow(QWidget *parent = 0);

    QLabel *labelonline;
    QLineEdit *presslocal;         //本地压力
    QLineEdit *pressremote;        //远端压力
    QLabel *runstatus;          //运行状态  常态 非计划 节电 自学习 寻优 验证
    QLabel *controlmode;        //控制方式 本控 远控 检修


    QLineEdit *pressBPset;      //变频设定
    QLineEdit *pressgoal;       //目标压力
    QLineEdit *pressfeedback;      //反馈压力
    QLineEdit *frequency;          //运行频率

    QTableWidget *tablellj;    //水表表格
    QTableWidget *tablepump;   //泵表格
    QTableWidget *tabledb;     //电表表格

    bool onlineflag;

private:
    int headlength;
    void title_row_label_init();
    void first_row_label_init();
    void second_row_label_init();

    void llj_table_init();
    void pump_table_init();
    void db_table_init();


protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

};



#endif // SECONDWINDOW_H

#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H
#include "upwinbase.h"
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>


class firstwindow : public upwinbase
{
    Q_OBJECT
public:
    explicit firstwindow(QWidget *parent = 0);

    QLabel *labelonline;
    QLineEdit *poollevel;      //水池水位
    QLineEdit *welllevel;      //深井水位

    bool onlineflag;

    QTableWidget *t_status;        //状态表格
    QTableWidget *t_data;          //数据表格


protected:
    void paintEvent(QPaintEvent *);

private:
    int headlength;

    void label_row_init();      //上方label初始化
    void draw_table_init();  //绘制表格

signals:

public slots:
    void slot_onlinestatus(bool value);

};

#endif // FIRSTWINDOW_H

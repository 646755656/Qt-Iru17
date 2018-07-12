#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H
#include "upwinbase.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>

class summarywindow : public upwinbase
{
    Q_OBJECT
public:
    explicit summarywindow(QWidget *parent = 0);
    QLabel *labelonline;

    //一次数据
    QLineEdit *firstPower;
    QLineEdit *firstkWh;
    QLineEdit *firsttotalPV;
    QLineEdit *firstFwater;
    QLineEdit *firstRwater;
    QLineEdit *firsttotalwater;
    QLineEdit *firstnormaltime;

    //二次数据
    QLineEdit *secondPower;
    QLineEdit *secondkWh;
    QLineEdit *secondtotalPV;
    QLineEdit *secondFwater;
    QLineEdit *secondRwater;
    QLineEdit *secondtotalwater;
    QLineEdit *secondnormaltime;

    QLineEdit *lifekWh;        //生活用电
    QLineEdit *producekWh;     //生产用电
    QLineEdit *totalwater;     //累计供水量

    QHBoxLayout *hfirstlayout;
    QHBoxLayout *hsecondlayout;
    QHBoxLayout *hotherlayout;


signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    int headlength;
    void first_data_display();
    void second_data_display();
    void other_data_display();


public slots:

};

#endif // SUMMARYWINDOW_H


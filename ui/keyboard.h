#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>


class keyboard : public QWidget
{
    Q_OBJECT
public:
    explicit keyboard(QWidget *parent = 0);

    QLineEdit *dislineEdit;

    QPushButton *pbt_1;
    QPushButton *pbt_2;
    QPushButton *pbt_3;
    QPushButton *pbt_4;
    QPushButton *pbt_5;
    QPushButton *pbt_6;
    QPushButton *pbt_7;
    QPushButton *pbt_8;
    QPushButton *pbt_9;
    QPushButton *pbt_0;
    QPushButton *pbt_ok;
    QPushButton *pbt_clear;
    QPushButton *pbt_exit;
    QPushButton *pbt_virgule;
    QPushButton *pbt_dot;

private:
    void keyboard_display_init();
    void keyPressEvent(QKeyEvent *event);

signals:
    void sendData(QString);   //用来传递数据的信号

public slots:
    void on_pbt_1_clicked();
    void on_pbt_2_clicked();
    void on_pbt_3_clicked();
    void on_pbt_4_clicked();
    void on_pbt_5_clicked();
    void on_pbt_6_clicked();
    void on_pbt_7_clicked();
    void on_pbt_8_clicked();
    void on_pbt_9_clicked();
    void on_pbt_0_clicked();
    void on_pbt_ok_clicked();
    void on_pbt_clear_clicked();
    void on_pbt_exit_clicked();
    void on_pbt_virgule_clicked();
    void on_pbt_dot_clicked();

};

#endif // KEYBOARD_H

#ifndef DEVICEWINDOW_H
#define DEVICEWINDOW_H
#include "upwinbase.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "keyboard.h"

class devicewindow : public upwinbase
{
    Q_OBJECT
public:
    explicit devicewindow(QWidget *parent = 0);

    QLineEdit *disnonplanpress;
    QLineEdit *dissetpress;

    QPushButton *pbt_stopBP;
    QPushButton *pbt_resetBP;

    QPushButton *pbt_openclose;

    QPushButton *pbt_downsecond;
    QPushButton *pbt_downfirst;

    QLineEdit *firstsubnum;
    QPushButton *pbt_downfirstsub;
    QPushButton *pbt_downanalog;

    QPushButton *pbt_keyoperate1;
    QPushButton *pbt_keyoperate2;
    QPushButton *pbt_keyoperate3;

    QPushButton *pbt_correcttime;
    QPushButton *pbt_calibratescreen;


protected:
    void paintEvent(QPaintEvent *);

private:
    int headlength;

    void bp_control_init();

    void data_func_init();

    void auxiliary_func_init();

    keyboard *kbd;

    int keyval;

    bool eventFilter ( QObject * watched, QEvent * event );


private slots:
    void receiveData(QString data);   //接收传递过来的数据的槽

public slots:

};

#endif // DEVICEWINDOW_H

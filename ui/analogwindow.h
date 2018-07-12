#ifndef ANALOGWINDOW_H
#define ANALOGWINDOW_H
#include "upwinbase.h"
#include <QLabel>
#include <QTableWidget>


class analogwindow : public upwinbase
{
    Q_OBJECT
public:
    explicit analogwindow(QWidget *parent = 0);
    QLabel *labelonline;

    QTableWidget *t_analog;        //模拟量数据

    QTableWidget *t_dbdata;           //电表数据

signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    int headlength;
    void table_analog_init();
    void table_dbdata_init();

public slots:

};

#endif // ANALOGWINDOW_H

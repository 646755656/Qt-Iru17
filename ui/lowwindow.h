#ifndef LOWWINDOW_H
#define LOWWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class lowwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit lowwindow(QWidget *parent = 0);

    QPushButton *pbt_menu;
    QLabel *timelabel;

signals:

public slots:
    void slot_updatesystime();

};

#endif // LOWWINDOW_H

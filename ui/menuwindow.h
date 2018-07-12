#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QPushButton>

class menuwindow : public QWidget
{
    Q_OBJECT
public:
    explicit menuwindow(QWidget *parent = 0);

    QPushButton *pbt_mainui;
    QPushButton *pbt_firstdataui;
    QPushButton *pbt_seconddataui;
    QPushButton *pbt_analogui;
    QPushButton *pbt_summarydataui;
    QPushButton *pbt_runplanui;
    QPushButton *pbt_deviceui;

signals:

public slots:

};

#endif // MENUWINDOW_H

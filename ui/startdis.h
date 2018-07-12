#ifndef STARTDIS_H
#define STARTDIS_H

#include <QWidget>
#include "lowwindow.h"
#include "maindisui.h"

class startdis : public QWidget
{
    Q_OBJECT
public:
    explicit startdis(QWidget *parent = 0);

    maindisui *uimaindis;
    lowwindow *uilow;
signals:

public slots:

};

#endif // STARTDIS_H

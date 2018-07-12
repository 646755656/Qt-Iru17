#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "upwinbase.h"
#include <QLabel>

class homepage : public upwinbase
{
    Q_OBJECT
public:
    explicit homepage(QWidget *parent = 0);

private:
    QLabel *titlelabel;

signals:

public slots:

};

#endif // HOMEPAGE_H

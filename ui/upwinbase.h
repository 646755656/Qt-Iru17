#ifndef UPWINBASE_H
#define UPWINBASE_H

#include <QWidget>
#include <QPushButton>

class upwinbase : public QWidget
{
    Q_OBJECT
public:
    explicit upwinbase(QWidget *parent = 0);
//    QPushButton *pbt_menu;


protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // UPWINBASE_H

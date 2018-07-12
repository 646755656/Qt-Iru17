#include "keyboard.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>

keyboard::keyboard(QWidget *parent) :
    QWidget(parent)
{
    setMaximumSize(460,240);
    setMinimumSize(460,240);
    setWindowFlags(Qt::FramelessWindowHint);

    keyboard_display_init();


}

void keyboard::keyboard_display_init()
{
    dislineEdit = new QLineEdit(this);
    dislineEdit->setFixedSize(420, 40);
    dislineEdit->setStyleSheet("font-size:28px;font:bold");
    dislineEdit->setFocusPolicy(Qt::StrongFocus);

    pbt_1 = new QPushButton("1",this);
    pbt_1->setFixedSize(75, 40);
    pbt_1->setStyleSheet("font-size:24px;font:bold");

    pbt_2 = new QPushButton("2",this);
    pbt_2->setFixedSize(75, 40);
    pbt_2->setStyleSheet("font-size:24px;font:bold");

    pbt_3 = new QPushButton("3",this);
    pbt_3->setFixedSize(75, 40);
    pbt_3->setStyleSheet("font-size:24px;font:bold");

    pbt_4 = new QPushButton("4",this);
    pbt_4->setFixedSize(75, 40);
    pbt_4->setStyleSheet("font-size:24px;font:bold");

    pbt_5 = new QPushButton("5",this);
    pbt_5->setFixedSize(75, 40);
    pbt_5->setStyleSheet("font-size:24px;font:bold");

    pbt_6 = new QPushButton("6",this);
    pbt_6->setFixedSize(75, 40);
    pbt_6->setStyleSheet("font-size:24px;font:bold");

    pbt_7 = new QPushButton("7",this);
    pbt_7->setFixedSize(75, 40);
    pbt_7->setStyleSheet("font-size:24px;font:bold");

    pbt_8 = new QPushButton("8",this);
    pbt_8->setFixedSize(75, 40);
    pbt_8->setStyleSheet("font-size:24px;font:bold");

    pbt_9 = new QPushButton("9",this);
    pbt_9->setFixedSize(75, 40);
    pbt_9->setStyleSheet("font-size:24px;font:bold");

    pbt_0 = new QPushButton("0",this);
    pbt_0->setFixedSize(75, 40);
    pbt_0->setStyleSheet("font-size:24px;font:bold");

    pbt_ok = new QPushButton("确定",this);
    pbt_ok->setFixedSize(75, 40);
    pbt_ok->setStyleSheet("font-size:18px;font:bold");

    pbt_dot = new QPushButton(".",this);
    pbt_dot->setFixedSize(75, 40);
    pbt_dot->setStyleSheet("font-size:24px;font:bold");

    pbt_clear = new QPushButton("清除",this);
    pbt_clear->setFixedSize(75, 40);
    pbt_clear->setStyleSheet("font-size:18px;font:bold");

    pbt_exit = new QPushButton("退出",this);
    pbt_exit->setFixedSize(75, 40);
    pbt_exit->setStyleSheet("font-size:18px;font:bold");

    pbt_virgule = new QPushButton("/",this);
    pbt_virgule->setFixedSize(75, 40);
    pbt_virgule->setStyleSheet("font-size:24px;font:bold");

    QHBoxLayout *hlayout1 = new QHBoxLayout();  //lineedit
    hlayout1->addStretch();
    hlayout1->addWidget(dislineEdit);
    hlayout1->addStretch();

    QHBoxLayout *hlayout2 = new QHBoxLayout();  //1 2 3 . clear
    hlayout2->addWidget(pbt_1);
    hlayout2->addWidget(pbt_2);
    hlayout2->addWidget(pbt_3);
    hlayout2->addWidget(pbt_dot);
    hlayout2->addWidget(pbt_clear);

    QHBoxLayout *hlayout3 = new QHBoxLayout();  //4 5 6 0 exit
    hlayout3->addWidget(pbt_4);
    hlayout3->addWidget(pbt_5);
    hlayout3->addWidget(pbt_6);
    hlayout3->addWidget(pbt_0);
    hlayout3->addWidget(pbt_exit);

    QHBoxLayout *hlayout4 = new QHBoxLayout();  //7 8 9 / ok
    hlayout4->addWidget(pbt_7);
    hlayout4->addWidget(pbt_8);
    hlayout4->addWidget(pbt_9);
    hlayout4->addWidget(pbt_virgule);
    hlayout4->addWidget(pbt_ok);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);
    vlayout->setGeometry(QRect(5,10,450,220));

    connect(pbt_1,SIGNAL(clicked()),this,SLOT(on_pbt_1_clicked()));
    connect(pbt_2,SIGNAL(clicked()),this,SLOT(on_pbt_2_clicked()));
    connect(pbt_3,SIGNAL(clicked()),this,SLOT(on_pbt_3_clicked()));
    connect(pbt_4,SIGNAL(clicked()),this,SLOT(on_pbt_4_clicked()));
    connect(pbt_5,SIGNAL(clicked()),this,SLOT(on_pbt_5_clicked()));
    connect(pbt_6,SIGNAL(clicked()),this,SLOT(on_pbt_6_clicked()));
    connect(pbt_7,SIGNAL(clicked()),this,SLOT(on_pbt_7_clicked()));
    connect(pbt_8,SIGNAL(clicked()),this,SLOT(on_pbt_8_clicked()));
    connect(pbt_9,SIGNAL(clicked()),this,SLOT(on_pbt_9_clicked()));
    connect(pbt_0,SIGNAL(clicked()),this,SLOT(on_pbt_0_clicked()));
    connect(pbt_dot,SIGNAL(clicked()),this,SLOT(on_pbt_dot_clicked()));
    connect(pbt_clear,SIGNAL(clicked()),this,SLOT(on_pbt_clear_clicked()));
    connect(pbt_virgule,SIGNAL(clicked()),this,SLOT(on_pbt_virgule_clicked()));
    connect(pbt_ok,SIGNAL(clicked()),this,SLOT(on_pbt_ok_clicked()));
    connect(pbt_exit,SIGNAL(clicked()),this,SLOT(on_pbt_exit_clicked()));
}

void keyboard::keyPressEvent(QKeyEvent *event)
{
    // 响应Esc键以退出程序
    if (event->key() == Qt::Key_Escape)
    {
       hide();
    }
}


void keyboard::on_pbt_1_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(1));
        else
        {
            text.append(QString::number(1));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(1));
        this->dislineEdit->setText(text);
    }
}

void keyboard::on_pbt_2_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(2));
        else
        {
            text.append(QString::number(2));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(2));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_3_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(3));
        else
        {
            text.append(QString::number(3));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(3));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_4_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(4));
        else
        {
            text.append(QString::number(4));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(4));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_5_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(5));
        else
        {
            text.append(QString::number(5));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(5));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_6_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(6));
        else
        {
            text.append(QString::number(6));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(6));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_7_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(7));
        else
        {
            text.append(QString::number(7));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(7));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_8_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(8));
        else
        {
            text.append(QString::number(8));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(8));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_9_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 1)
    {
        if(text.mid(0,1) == "0")
            this->dislineEdit->setText(QString::number(9));
        else
        {
            text.append(QString::number(9));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(9));
        this->dislineEdit->setText(text);
    }
}

void keyboard::on_pbt_0_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.size() == 0)
        this->dislineEdit->setText(QString::number(0));
    else if(text.size() == 1)
    {
        if(text.indexOf("0") == -1)
        {
            text.append(QString::number(0));
            this->dislineEdit->setText(text);
        }
    }
    else
    {
        text.append(QString::number(0));
        this->dislineEdit->setText(text);
    }

}

void keyboard::on_pbt_ok_clicked()
{
    int pos=0,len = 0,num = 0,ptr = 0;
    QString text = this->dislineEdit->text();
    len = text.length();
    pos = text.indexOf(".");
    //去除小数点后无效的0
    if(pos != -1)
    {
        if(len > pos + 1)       //小数点后面有数值
        {
            ptr = pos++;
            for(;ptr<len;ptr++)
            {
                if(text.at(ptr) == '0')
                    num++;
            }
            if(num == len - pos)
            {
                text = text.split('.')[0];
            }
        }
        else if(pos == len - 1) //去除最后一位是小数点
            text = text.left(text.length() - 1);
    }

    this->dislineEdit->setText(text);
    emit sendData(text);  //获取lineEdit的输入并且传递出去
    close();
    this->dislineEdit->clear();

}

void keyboard::on_pbt_clear_clicked()
{
    this->dislineEdit->clear();
}

void keyboard::on_pbt_exit_clicked()
{
    close();
}

void keyboard::on_pbt_virgule_clicked()
{
    QString text = this->dislineEdit->text();
    int leng = text.length();

    if(text.isEmpty() == false)
    {
        if((text.mid(leng - 1,1) != "/") && (text.mid(leng - 1,1) != "."))
        {
            text.append("/");
            this->dislineEdit->setText(text);
        }
    }
}

void keyboard::on_pbt_dot_clicked()
{
    QString text = this->dislineEdit->text();
    if(text.isEmpty() == false)
    {
        if(text.indexOf(".") == -1)
            text.append(".");
        this->dislineEdit->setText(text);
    }

}

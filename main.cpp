#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QWSServer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

//    QWSServer::setCursorVisible(false);

    MainWindow w;
    w.show();

    return a.exec();
}



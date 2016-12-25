#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
//    QApplication::setPalette(QApplication::style()->standardPalette());
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//设置编码
    MainWindow w;
    w.show();
    return a.exec();
}

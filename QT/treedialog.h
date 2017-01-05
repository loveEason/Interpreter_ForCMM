#ifndef TREEDIALOG_H
#define TREEDIALOG_H

#include <QMainWindow>
#include <QPainter>
#include <QDialog>
#include <Qt>
#include "Global.h"
#include <QTextBrowser>
class TreeDialog:public QDialog{
//    Q_OBJECT
public:
//    QDialog *dlg;
//    QWidgit *widgit;
    TreeDialog(QWidget *parent = 0,QString xml=0, Qt::WindowFlags flags = 0);
    ~TreeDialog();
    void paintEvent(QPaintEvent *);
//public slots:
//    virtual void accept();
private:
    QString xml;
};

#endif // TREEDIALOG_H

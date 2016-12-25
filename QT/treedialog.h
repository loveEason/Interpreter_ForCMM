#ifndef TREEDIALOG_H
#define TREEDIALOG_H

#include <QMainWindow>
#include <QPainter>
#include <QDialog>
#include <Qt>
class TreeDialog:public QDialog{
//    Q_OBJECT
public:
//    QDialog *dlg;
//    QWidgit *widgit;
    TreeDialog(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~TreeDialog();
    void paintEvent(QPaintEvent *);
//public slots:
//    virtual void accept();
};

#endif // TREEDIALOG_H

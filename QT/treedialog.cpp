#include "treedialog.h"
#include <QFileDialog>
#include <QPainter>
#include <QtMath>
TreeDialog::TreeDialog(QWidget *parent, treeNode *par,Qt::WindowFlags flags):QDialog(parent, flags){
    setWindowTitle(tr("Tree"));
    tree =par;
    resize(800,600);
//    ScrollView *scroll = new scrollView();

}
TreeDialog::~TreeDialog(){

}
void TreeDialog::paintEvent(QPaintEvent *){
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(10, 10, this->width()-20, this->height()-20);

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, this);
//    painter.fillPath(path, QBrush(Qt::white));

//    QColor color(0, 0, 0, 50);
//    for(int i=0; i<10; i++)
//    {
//        QPainterPath path;
//        path.setFillRule(Qt::WindingFill);
//        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
//        color.setAlpha(150 - qSqrt(i)*50);
//        painter.setPen(color);
//        painter.drawPath(path);
//    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>


#include <iosfwd>
#include <iostream>
#include <fstream>
#include "Global.h"
#include "LexAnalysis.h"
#include "Parse.h"
#include "actuator.h"
#include "CodeGenerator.h"
#include <qinputdialog.h>
using namespace std;




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString data;
    ~MainWindow();
    void paintEvent(QPaintEvent *);

    void addoutput(string output=NULL);

    void addintercode(string intercode=NULL);

    string getinput();

private slots:
    void on_Input_cursorPositionChanged();

    void on_Start_clicked();

    void on_Tree_clicked();

    void on_Open_clicked();

    void on_Save_clicked();

    void on_Exit_clicked();

    void on_Exit_released();


private:
    Ui::MainWindow *ui;
    QPoint last;
    int lineNo;          //源文件中行的序号
//    ofstream parseTree_file; //语法树结果文件
//    LexAnalysis *lexAnalysis;
//    normalNode* normalHead;
//    Parse *parse;
//    CodeGenerator *cg;
//    Actuator *actuator;
    treeNode *tree=NULL;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H

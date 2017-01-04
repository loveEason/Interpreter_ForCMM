#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
//#include <string.h>
#include "treedialog.h"
#include <QPainter>
#include <QtMath>
#include <QFileDialog>
#include <QTextStream>

#include <string.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//退出
//void MainWindow::on_actionExit_triggered()
//{
//
//}




void MainWindow::on_Tree_clicked()
{
    TreeDialog *parsetree = new TreeDialog(this,tree);
//    tree->setWindowFlags(Qt::FramelessWindowHint);
//    tree->setAttribute(Qt::WA_TranslucentBackground,true);
    parsetree->show();
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, this);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

//拖动
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    last = e->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    last = e->globalPos();
    move(x()+dx, y()+dy);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    move(x()+dx, y()+dy);
}

//打开文件，载入至Input文本框中
void MainWindow::on_Open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("open file"));
    QFile *in = new QFile(fileName);
    in->open(QIODevice::ReadOnly|QIODevice::Text);
    this->data = QString(in->readAll());
    in->close();
    ui->Input->setPlainText(data);
}


//文件另存为
void MainWindow::on_Save_clicked()
{
    QString url = QFileDialog::getSaveFileName(this,tr("Open Directory"),"","");
    QFile *out = new QFile(url);
    out->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream textStream(out);
    textStream << ui->Input->toPlainText() << "\n";
    out->close();
}

//开始按钮，对代码进行解释
void MainWindow::on_Start_clicked()
{

    QString text = ui->Input->toPlainText();
    string code = text.toStdString();
    string error;
//    code = "int i=1;\n"
//                  "if(i>0){i=i-1;}";
    LexAnalysis lexAnalysis;
    lexAnalysis.lexAnalyse(code);

    if (lexAnalysis.ifHasError()) {
        cout<<"Invalid token,please rectify:"<<endl;
        errorNode *p = lexAnalysis.getErrorHead();
        while (p->next != NULL) {
            cout<<"Line at "<<p->next->line<<":"<<p->next->content<<endl;
            p = p->next;
        }
    } else {    //词法分析正确,开始语法分析
        normalNode* normalHead = lexAnalysis.getNormalHead();
        Parse parse;
        parse.grammarAnalyse(normalHead);

        CodeGenerator *cg = new CodeGenerator();
        cg->interpretPrg(parse.getTreeRoot());
        cg->printCode();
        Actuator actuator(cg->getCode());
        actuator.runCode();
        cg->clearCode();
        delete cg;
    }
//    string out;
//    QString result = QString::fromStdString(out);
//    ui->Result->insertPlainText(result);

}
//光标位置改变
void MainWindow::on_Input_cursorPositionChanged()
{
    const QTextCursor cursor = ui->Input->textCursor();
    int ColNum = cursor.columnNumber()+1;
    int RowNum = cursor.blockNumber()+1;

    QString Col = QString::number(ColNum,10);
    QString Row = QString::number(RowNum,10);
    ui->status->setText("ColNum:"+Col+",RowNum:"+Row);
}
//退出
void MainWindow::on_Exit_clicked()
{

}

void MainWindow::on_Exit_released()
{
    this->close();
}

void MainWindow::addoutput(string output){
    QString result = QString::fromStdString(output);
    ui->Result->insertPlainText(result);
}

void MainWindow::addintercode(string intercode){
    QString result = QString::fromStdString(intercode);
    ui->Intercode->insertPlainText(result);
}

string MainWindow::getinput(){
    QString input;
    bool ok;
    input = QInputDialog::getText(this, tr(""),
                                         tr("Input:"), QLineEdit::Normal,
                                         "", &ok);
    string result = input.toStdString();
    return result;
}

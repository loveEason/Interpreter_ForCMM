#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QFileDialog>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开文件，载入至Input文本框中
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("open file"));
    QFile *in = new QFile(fileName);
    in->open(QIODevice::ReadOnly|QIODevice::Text);
    this->data = QString(in->readAll());
    in->close();
    ui->Input->setPlainText(data);
}

//文件另存为
void MainWindow::on_actionSave_triggered()
{
    QString url = QFileDialog::getSaveFileName(this,tr("Open Directory"),"","");
    QFile *out = new QFile(url);
    out->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream textStream(out);
    textStream << ui->Input->toPlainText() << "\n";
    out->close();
    //        ui->Input->setPlainText(dir);
}

//退出
void MainWindow::on_actionExit_triggered()
{
    this->close();
}

//开始按钮，对代码进行解释
void MainWindow::on_pushButton_clicked()
{

    ui->Result->setPlainText(ui->Input->toPlainText());
}

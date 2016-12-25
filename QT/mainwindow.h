#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
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
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

};

#endif // MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTextEdit *Input;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_3;
    QTextBrowser *Intercode;
    QWidget *formLayoutWidget;
    QGridLayout *gridLayout_2;
    QTextBrowser *Result;
    QPushButton *Start;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_5;
    QLabel *status;
    QPushButton *Tree;
    QPushButton *Open;
    QPushButton *Save;
    QPushButton *Exit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(951, 632);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 50, 581, 361));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Input = new QTextEdit(gridLayoutWidget);
        Input->setObjectName(QStringLiteral("Input"));
        Input->setLineWrapMode(QTextEdit::NoWrap);

        gridLayout->addWidget(Input, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(640, 50, 271, 531));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        Intercode = new QTextBrowser(gridLayoutWidget_2);
        Intercode->setObjectName(QStringLiteral("Intercode"));

        gridLayout_3->addWidget(Intercode, 0, 0, 1, 1);

        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(40, 450, 581, 131));
        gridLayout_2 = new QGridLayout(formLayoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Result = new QTextBrowser(formLayoutWidget);
        Result->setObjectName(QStringLiteral("Result"));

        gridLayout_2->addWidget(Result, 0, 0, 1, 1);

        Start = new QPushButton(centralWidget);
        Start->setObjectName(QStringLiteral("Start"));
        Start->setGeometry(QRect(40, 420, 75, 23));
        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(700, 580, 201, 31));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        status = new QLabel(gridLayoutWidget_3);
        status->setObjectName(QStringLiteral("status"));

        gridLayout_5->addWidget(status, 0, 0, 1, 1);

        Tree = new QPushButton(centralWidget);
        Tree->setObjectName(QStringLiteral("Tree"));
        Tree->setGeometry(QRect(150, 420, 75, 23));
        Open = new QPushButton(centralWidget);
        Open->setObjectName(QStringLiteral("Open"));
        Open->setGeometry(QRect(40, 20, 75, 23));
        Save = new QPushButton(centralWidget);
        Save->setObjectName(QStringLiteral("Save"));
        Save->setGeometry(QRect(140, 20, 75, 23));
        Exit = new QPushButton(centralWidget);
        Exit->setObjectName(QStringLiteral("Exit"));
        Exit->setGeometry(QRect(910, 20, 21, 23));
        Exit->setStyleSheet(QLatin1String("border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color:red;\n"
""));
        MainWindow->setCentralWidget(centralWidget);
        gridLayoutWidget->raise();
        gridLayoutWidget_2->raise();
        formLayoutWidget->raise();
        Start->raise();
        gridLayoutWidget_3->raise();
        Tree->raise();
        Open->raise();
        Save->raise();
        Exit->raise();
        status->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Start->setText(QApplication::translate("MainWindow", "Start", 0));
        status->setText(QApplication::translate("MainWindow", "ColNum:0,RowNum:0", 0));
        Tree->setText(QApplication::translate("MainWindow", "Tree", 0));
        Open->setText(QApplication::translate("MainWindow", "Open", 0));
        Save->setText(QApplication::translate("MainWindow", "Save", 0));
        Exit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

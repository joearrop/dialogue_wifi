/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit_0;
    QTextEdit *textEdit_1;
    QFrame *line;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QMenu *menuTeste;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 585);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        textEdit_0 = new QTextEdit(centralwidget);
        textEdit_0->setObjectName(QStringLiteral("textEdit_0"));
        textEdit_0->setEnabled(true);
        textEdit_0->setGeometry(QRect(220, 20, 531, 241));
        textEdit_0->setAcceptDrops(true);
        textEdit_0->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit_0->setReadOnly(true);
        textEdit_1 = new QTextEdit(centralwidget);
        textEdit_1->setObjectName(QStringLiteral("textEdit_1"));
        textEdit_1->setGeometry(QRect(220, 310, 531, 221));
        textEdit_1->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit_1->setLineWrapColumnOrWidth(0);
        textEdit_1->setReadOnly(true);
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(30, 270, 751, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 0, 171, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 290, 171, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuTeste = new QMenu(menubar);
        menuTeste->setObjectName(QStringLiteral("menuTeste"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTeste->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        textEdit_1->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        textEdit_1->setPlaceholderText(QString());
        label->setText(QApplication::translate("MainWindow", "Server Communication", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Serial Communication", Q_NULLPTR));
        menuTeste->setTitle(QApplication::translate("MainWindow", "Teste", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

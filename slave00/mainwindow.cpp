#include <QApplication>
#include <QObject>
#include <QtUiTools>
#include <QTextEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::LogPCSOL(QString msg){ //implement autoclear
    QTextEdit* TextAreaPCSOL = findChild<QTextEdit*>("textEdit_0");

    TextAreaPCSOL->append(msg);
    qDebug()<< msg <<endl;
}

void MainWindow::LogChariot(QString msg){ //implement autoclear
    QTextEdit* TextAreaChariot = findChild<QTextEdit*>("textEdit_1");

    TextAreaChariot->append(msg);
    qDebug()<< msg <<endl;
}

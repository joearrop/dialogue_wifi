#include <QApplication>
#include <QObject>
#include <QtUiTools>
#include <QTextEdit>
#include <QPushButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* m_button = findChild<QPushButton*>("buttDisconnect");
    // Connect button signal to appropriate slot
    connect(m_button, &QPushButton::released, this, &MainWindow::handleDisconnectButton);
}

MainWindow::~MainWindow()
{
    delete ui;
    QTextEdit* TextAreaPCSOL = findChild<QTextEdit*>("textEdit_0");

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

void MainWindow::handleDisconnectButton(){
    //use link to emit a signal to disconnect etc
    link->send_UI_Command(DISCONNECTCOMMAND);
}

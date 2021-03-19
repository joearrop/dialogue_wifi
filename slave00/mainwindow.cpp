//#include "mainwindow.h"
//#include "ui_mainwindow.h"

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

//#include <QDebug>
//#include <QHostAddress>

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow),
//    _socket(this)
//{
//    ui->setupUi(this);
//    _socket.connectToHost(QHostAddress("192.168.0.2"), 4242);
//    qDebug() << "ok";
//    bool conection = _socket.waitForConnected(30000);
//    qDebug() << conection;
//    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}

//void MainWindow::onReadyRead()
//{
//    QByteArray datas = _socket.readAll();
//    qDebug() << datas;
//    _socket.write(QByteArray("ok !\n"));
//}

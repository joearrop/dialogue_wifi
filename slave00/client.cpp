#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include "client.h"
#include <QtWidgets>
#include <QString>
#include <string>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(connectToHost()));
    timer->setSingleShot(true);
    timer->start(2000);
    qDebug()<<"timer started";
}

bool Client::connectToHost(){
    qDebug()<<"Connexion...";
    socket->connectToHost("192.168.1.42", 10000);
    bool connected = socket->waitForConnected(10000);
    if(connected){
        socket->write("0102101205051054540");
        int available = socket->bytesAvailable();
        qDebug() << QObject::tr("bytes available : %1").arg(available) << endl;
    }
    else{
        qDebug()<<"Error to connect: " << socket -> error()<<endl;
    }
    return connected;
}

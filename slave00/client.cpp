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

bool Client::connectToHost(char* ipv4,int timeThresholdms){
    qDebug()<<"Connexion...";
    socket->connectToHost(ipv4, timeThresholdms);
    bool connected = socket->waitForConnected(timeThresholdms);
    if(connected){
        socket->write("Chariot conneté");
        qDebug() << QObject::tr("Connecté avec le PC-SOL") << endl;
    }
    else{
        qDebug()<<"Error to connect: " << socket -> error()<<endl;
    }
    return connected;
}

bool Client::connectToHost(){
    return Client::connectToHost("192.168.1.42",10000);
}

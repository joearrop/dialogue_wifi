#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include "client.h"
#include <QtWidgets>
#include <QString>
#include <string>

Client::Client(QObject *parent) : QObject(parent){
    TCPsocket = new QTcpSocket(this);
    UDPsocket = new QUdpSocket(this);
    //QTimer *timer = new QTimer();

    /*connect(timer, SIGNAL(timeout()),this, SLOT(connectToHost()));
    timer->setSingleShot(true);
    timer->start(2000);
    qDebug()<<"timer started";*/
}

void Client::getServerIPv4ThroughUDPBroadcast(){
    qDebug()<<" start getIP 222"<<endl;
    UDPsocket->bind(QHostAddress::Broadcast,10000); //To listen to the broadcast ipv4 (255.255.255.255), port 10000

    connect(UDPsocket,&QUdpSocket::readyRead, this,&Client::readPendingDatagrams); //Connect ready signal from UDP socket to a slot where we can process that
    qDebug()<<" end getIP"<<endl;
}

void Client::readPendingDatagrams(){
    qDebug()<<"start datagram"<<endl;

    if(UDPsocket->hasPendingDatagrams()){
        /*
         I chqnged a "while" for a "if" so  its also necessary to
        make sure that we dont have any problem if the first datagram
        fails or if we got a great number of messages from PC-SOL
        stacked in the broadcast
        */
        QNetworkDatagram datagram = UDPsocket->receiveDatagram(); //receive UDP datagrams
        qDebug() << "UDP datagram received" << datagram.data().toHex() << endl; //print HEX
        qDebug() << "UDP datagram received" << datagram.data().toStdString().c_str() << endl; //print String

        ServerIPv4 = datagram.data().toStdString(); //att ipv4 address to connect
    }
    qDebug()<<"end datagram"<<endl;
}

bool Client::connectToHost(const char* ipv4,int timeThresholdms){
    qDebug()<<"Connexion with ..."<<ipv4;
    TCPsocket->connectToHost(ipv4, timeThresholdms);
    bool connected = TCPsocket->waitForConnected(timeThresholdms);
    if(connected){
        TCPsocket->write("Chariot conneté");
        qDebug() <<     QObject::tr("Connecté avec le PC-SOL") << endl;
    }
    else{
        qDebug()<<"Error to connect: " << TCPsocket -> error()<<endl;
    }
    return connected;
}

bool Client::connectToHost(){
    return Client::connectToHost(ServerIPv4.c_str(),10000);
}

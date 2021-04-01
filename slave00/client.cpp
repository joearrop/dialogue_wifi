#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include "client.h"
#include <QtWidgets>
#include <QString>
#include <string>
#include <regex>
#include <chrono>
#include <ctime>


Client::Client(QObject *parent) : QObject(parent){
    TCPsocket = new QTcpSocket(this);
    UDPsocketDiscovery = new QUdpSocket(this);
    UDPsocketComm = new QUdpSocket(this);
    UDPsocketBroadComm = new QUdpSocket(this);
    //QTimer *timer = new QTimer();

    /*connect(timer, SIGNAL(timeout()),this, SLOT(connectToHost()));
    timer->setSingleShot(true);
    timer->start(2000);
    qDebug()<<"timer started";*/
}

void Client::getServerIPv4ThroughUDPBroadcast(){
    qDebug()<<"Getting PC-SOL IPv4 Address"<<endl;
    UDPsocketDiscovery->bind(QHostAddress::Broadcast,10000); //To listen to the broadcast ipv4 (255.255.255.255), port 10000

    connect(UDPsocketDiscovery,&QUdpSocket::readyRead, this,&Client::readPendingDatagramsIP); //Connect ready signal from UDP socket to a slot where we can process that
    qDebug()<<" end getIP"<<endl;
}

void Client::bindUDPcommsocket(){
    qDebug()<<"Connecting to subnet broadcast"<<SubNetBroadcastIPv4.c_str()<<endl;
    UDPsocketComm->bind(QHostAddress(QString(SubNetBroadcastIPv4.c_str())),10000); //To listen to the subnet broadcast ipv4 (e.g. 192.168.1.255), port 10000
    connect(UDPsocketComm,&QUdpSocket::readyRead, this,&Client::readUDPMsg); //Connect ready signal from UDP socket to a slot where we can process that
}

void Client::bindBroadcommsocket(){
    qDebug()<<"Connecting to broadcast"<<endl;
    UDPsocketBroadComm->bind(QHostAddress::Broadcast,8000); //To listen to the broadcast ipv4 (255.255.255.255), port 8000
    connect(UDPsocketBroadComm,&QUdpSocket::readyRead, this,&Client::readBroadMsg); //Connect ready signal from UDP socket to a slot where we can process that
}



void Client::readPendingDatagramsIP(){
    QNetworkDatagram datagram;
    std::regex ipv4_regex("\\d{1,3}[.]\\d{1,3}[.]\\d{1,3}[.]\\d{1,3}");
    std::regex end_ipv4_regex("\\d{1,3}$");
    std::smatch matches;
    qDebug()<<"start datagram"<<endl;

    if(UDPsocketDiscovery->hasPendingDatagrams()){
        /*
         I changed a "while" for a "if" so  its also necessary to
        make sure that we dont have any problem if the first datagram
        fails or if we got a great number of messages from PC-SOL
        stacked in the broadcast
        */
        datagram = UDPsocketDiscovery->receiveDatagram(); //receive UDP datagrams
        //qDebug() << "UDP datagram received" << datagram.data().toHex() << endl; //print HEX
        qDebug() << "UDP Broadcast datagram received" << datagram.data().toStdString().c_str() << endl; //print String

        //(\d{1,3})[.](\d{1,3})[.](\d{1,3})[.](\d{1,3})
        std::string temp = datagram.data().toStdString(); //It seems like regex_search doesnt allow to use a function that returns a std::string, like .toStdString()
        std::regex_search(temp,matches,ipv4_regex);
        if(matches.ready()){ //Use regex to make sure that it is a valid ip address
            ServerIPv4 = temp; //att ipv4 address to connect
            SubNetBroadcastIPv4 = std::regex_replace(temp,end_ipv4_regex,"255"); //get subnetbroadcast e.g. "192.168.1.42" -> "192.168.1.255"
            //qDebug() << "SubNetBroadcastIPv4: " << SubNetBroadcastIPv4.c_str() << endl;
            bindUDPcommsocket();
        }
        else{
            qDebug() << "Invalid IPv4 Address received" <<endl;
        }
    }
    qDebug()<<"end datagram"<<endl;
}

QByteArray Client::readUDPMsg(){
    QByteArray data2return = QByteArray();
    QNetworkDatagram datagram;
    std::time_t reconnectTime = std::time(nullptr);

    //qDebug()<<"test1"<<endl;
    while(UDPsocketComm->hasPendingDatagrams()&& std::difftime(std::time(nullptr),reconnectTime)<UDPTIMEOUTSEC){ //while theres datagrams to read and before timeout
        //qDebug()<<"test2"<<endl;
        datagram = UDPsocketComm->receiveDatagram(); //receive UDP datagrams
        data2return.append(datagram.data()); //Appends the byte array
    }
    return data2return;
}

QByteArray Client::readBroadMsg(){
    QByteArray data2return = QByteArray();
    QNetworkDatagram datagram;
    std::time_t reconnectTime = std::time(nullptr);


    //qDebug()<<"test1"<<endl;
    while(UDPsocketBroadComm->hasPendingDatagrams() && std::difftime(std::time(nullptr),reconnectTime)<UDPTIMEOUTSEC){ //while theres datagrams to read and before timeout
        //qDebug()<<"test2"<<endl;
        datagram = UDPsocketBroadComm->receiveDatagram(); //receive UDP datagrams
        data2return.append(datagram.data()); //Appends the byte array
    }
    return data2return;
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

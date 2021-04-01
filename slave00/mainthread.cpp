#include "mainthread.h"
#include <QtCore>
#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <sstream>
#include <string>
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <ctime>
#include "client.h"
#include "ConsoleReader.h"
#include "mainwindow.h"
#include "LinkThreadGUI.h"


MainThread::MainThread(){

}

void MainThread::run(){
    int iter = 0,socketWrite = 0,protocol = UDPIP;
    bool connectedToHost = false;
    std::time_t reconnectTime;
    Client client;
    QByteArray dataRead, sock;

    //Init
    reception.reserve(3000); //Memory reservation
    historical.reserve(3000);//??
    reception.resize(0); //Taille 0
    historical.resize(0);//??

    //Serial
    serialPortName = (argumentCount > 1) ? argumentList.at(1) : QString("/dev/ttyS2");
    serialPortBaudRate = (argumentCount > 2) ? argumentList.at(2).toInt() : QSerialPort::Baud38400; //38400 default

    serial->setPortName(serialPortName);
    openSerialPort(serialPortName,serialPortBaudRate); //Open Serial port

    //protocol = (argumentCount > 4) ? argumentList.at(4).toInt() : UDPBROAD; //Default = Broadcast
    //Client
    client.getServerIPv4ThroughUDPBroadcast();
    QThread::sleep(1); //just to give time to everything to be seted up before trying to read UDP datagrams
    client.readPendingDatagramsIP();
    connectedToHost = client.connectToHost();

    client.bindBroadcommsocket();

    reconnectTime = std::time(nullptr);

    //Loop
    iterMax = (argumentCount > 3) ? argumentList.at(3).toInt() : -1; //Default = while(1)
    while(1){
        while ((iter<iterMax || iterMax<0)&commRun){
            //Implement broadcast search for PC-SOL ipv4 in order to use dynamic ipv4 adress in PC-SOL
            dataRead = readSerialData();
            //qDebug() << "dataRead HEX:" << dataRead.toHex()<<endl;
            link->send_feedback_Chariot("dataRead HEX:"+dataRead.toHex());

            qDebug() << "Connected to Host:" << connectedToHost <<endl;
             //link->send_feedback_PCSOL("Connected to Host: "+connectedToHost);

            if(connectedToHost){
                //Receive data from PC-SOL through TCP/IP
                /*
                if(client.TCPsocket->waitForReadyRead()){
                    sock = client.TCPsocket->readAll();

                    //qDebug() << "lecture wifi HEX:" << sock.toHex()<<endl;
                    link->send_feedback_PCSOL("lecture wifi HEX:" + sock.toHex());
                    //QThread::sleep(3);
                    //qDebug() << "serial.write(sock):" << serial->write(sock)<<endl;
                    link->send_feedback_Chariot("serial.write(sock):" + serial->write(sock));

                    socketWrite = client.TCPsocket->write(dataRead);
                    //socketWrite = client.TCPsocket->write(QByteArray("test"));
                    //client.TCPsocket->flush();
                    client.TCPsocket->waitForBytesWritten();

                    //qDebug() << "client.socket->write(dataRead):" << socketWrite<<endl;
                    link->send_feedback_PCSOL("client.socket->write(dataRead):" + socketWrite);

                    if(socketWrite<0){// disconnect if its not possible to send data to host
                        client.TCPsocket->disconnectFromHost();
                        connectedToHost = false;
                    }
                }
                else{//disconnect if host doesnt answer for 30 sec
                    client.TCPsocket->disconnectFromHost();
                    connectedToHost = false;
                    //qDebug() << "serial.write(vide1):" << serial->write(QByteArray())<<endl; //writes null array to continue the flux of communication
                    link->send_feedback_Chariot("serial.write(vide1):" + serial->write(QByteArray()));
                }

                //*/
                //Receive data from PC-SOL through UDP/IP
                /*
                client.bindUDPcommsocket();
                sock = client.readUDPMsg();

                qDebug() << "lecture wifi HEX:" << sock.toHex()<<endl;
                //QThread::sleep(3);
                qDebug() << "serial.write(sock):" << serial->write(sock)<<endl;

                socketWrite = client.TCPsocket->write(dataRead);

                qDebug() << "client.socket->write(dataRead):" << socketWrite<<endl;
                //*/

                //Receive data from PC-SOL through Broadcast
                ///*
                //sock = client.TCPsocket->readAll();
                sock = client.readBroadMsg();

                qDebug() << "lecture wifi HEX:" << sock.toHex()<<endl;
                //QThread::sleep(3);
                qDebug() << "serial.write(sock):" << serial->write(sock)<<endl;

                socketWrite = client.TCPsocket->write(dataRead);
                //socketWrite = client.TCPsocket->write(QByteArray("test"));
                client.TCPsocket->waitForBytesWritten();

                qDebug() << "client.TCPsocket->write(dataRead):" << socketWrite<<endl;
                //*/


                if(socketWrite<0){// disconnect if its not possible to send data to host
                    client.TCPsocket->disconnectFromHost();
                    connectedToHost = false;
                }


            }
            else{
                //qDebug() << "serial.write(vide2):" << serial->write(QByteArray())<<endl; //writes null array to continue the flux of communication
                link->send_feedback_Chariot("serial.write(vide2):" + serial->write(QByteArray()));

                if(std::difftime(std::time(nullptr),reconnectTime) > CONNECYCICLESEC){ //try to reconnect after CONNECYCICLESEC seconds
                    client.readPendingDatagramsIP();

                    connectedToHost = client.connectToHost();
                    reconnectTime = std::time(nullptr);
                }
            }

            if(iter == INT_MAX-100)//to avoid overflow
                iter = 0;
            iter++;
        }
        //qDebug() << "disconnectiong from host" << endl;
        link->send_feedback_PCSOL("disconnecting from host");
        client.TCPsocket->disconnectFromHost();
        //qDebug() << "closing Serial Port"<< endl;
        link->send_feedback_Chariot("closing Serial Port");
        closeSerialPort(path);
        //client.TCPsocket->disconnectImpl();
        qDebug() << client.TCPsocket->state() <<endl;
        link->send_feedback_PCSOL("disconnected from host");

    }

}


QByteArray MainThread::readSerialData(){
    static bool firstReadSerialData = true;
    QTextStream sortieTerminal(stdout);
    QByteArray dataRead;

    if(firstReadSerialData)
    {
        gettimeofday(&startTime,NULL);
        firstReadSerialData = false;
    }
    if(serial->error() != QSerialPort::ParityError) //Vérification de la parité
    {
        serial->waitForReadyRead(1000); //Attente - timeout
        dataRead = serial->readAll(); //Lecture de tout ce qu'il y a
    }
    return dataRead;
}

int MainThread::openSerialPort(QString serialPortName,int serialPortBaudRate){
    if (!serial->open(QIODevice::ReadWrite)) {//Serial open error
           qDebug() << "Failed to open port %1, error: " << serial->error() << " - " << serial->errorString() << endl;
           return 0;
    }
    else
    {
        qDebug() << "Connected To Port " << serialPortName << endl;
        serial->setBaudRate(serialPortBaudRate); //Serial Communication BaudRate
        serial->setDataBits(QSerialPort::Data8); //8 bit cell packet
        serial->setParity(QSerialPort::NoParity); //No parity check every cell packet
        serial->setStopBits(QSerialPort::OneStop); //One Stop bit
        serial->setFlowControl(QSerialPort::NoFlowControl);//No hardware and no software flow control (handshake etc)
        if (serial->error() == QSerialPort::ReadError) {
            qDebug() << QObject::tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serial->errorString()) << endl;
            return 0;
        }
        else{
            return 1;
        }
    }


}

void MainThread::closeSerialPort(QString path){ //Déconnexion RS232
    QTextStream outTerminal(stdout);
    serial->close();
    qDebug() << "Serial Port Closed Succesfully"<<endl;
    if((!reception.isEmpty())||(!historical.isEmpty()))
    {
        QFile fileReception, fileHistorical;

        fileReception.setFileName(path+"reception.txt");
        fileHistorical.setFileName(path+"historical.txt");

        if(!fileReception.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream outReception(&fileReception);
        for(int i=0;i<reception.size();i++) outReception << reception[i] << endl;
        fileReception.close();

        if(!fileHistorical.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream outHistorical(&fileHistorical);
        for(int i=0;i<historical.size();i++) outHistorical << historical[i] << endl;
        fileHistorical.close();
    }

    reception.clear();
    reception.resize(0);
    reception.squeeze();
    historical.clear();
    historical.resize(0);
    historical.squeeze();
    #ifdef DEBUG
        QProcess::execute("sudo shutdown -h now"); //RR1611
    #endif
}

void MainThread::Command(int cmd){ //Deals with the commands sent by the UI(at first, but any other entity could do that using the link)
    switch(cmd){
        case DISCONNECTCOMMAND:
            commRun = false;
            break;
    }
}


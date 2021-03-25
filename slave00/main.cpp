#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include "client.h"
#include "serial.h"
#include "ConsoleReader.h"
#include <QtWidgets>
#include <QString>
#include <sstream>
#include <string>
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <ctime>

#define CONNECYCICLESEC 10

struct timeval startTime,debutTimer;
QSerialPort serial;
QVector<QString> historical, reception;

QByteArray readSerialData(){
    static bool firstReadSerialData = true;
    QTextStream sortieTerminal(stdout);
    QByteArray dataRead;

    if(firstReadSerialData)
    {
        gettimeofday(&startTime,NULL);
        firstReadSerialData = false;
    }
    if(serial.error() != QSerialPort::ParityError) //Vérification de la parité
    {
        serial.waitForReadyRead(1000); //Attente - timeout
        dataRead = serial.readAll(); //Lecture de tout ce qu'il y a
    }
    return dataRead;
}

int openSerialPort(QString serialPortName,int serialPortBaudRate){
    if (!serial.open(QIODevice::ReadWrite)) {//Serial open error
           qDebug() << "Failed to open port %1, error: " << serial.error() << " - " << serial.errorString() << endl;
           return 0;
    }
    else
    {
        qDebug() << "Connected To Port " << serialPortName << endl;
        serial.setBaudRate(serialPortBaudRate); //Serial Communication BaudRate
        serial.setDataBits(QSerialPort::Data8); //8 bit cell packet
        serial.setParity(QSerialPort::NoParity); //No parity check every cell packet
        serial.setStopBits(QSerialPort::OneStop); //One Stop bit
        serial.setFlowControl(QSerialPort::NoFlowControl);//No hardware and no software flow control (handshake etc)
        if (serial.error() == QSerialPort::ReadError) {
            qDebug() << QObject::tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serial.errorString()) << endl;
            return 0;
        }
        else{
            return 1;
        }
    }


}

void closeSerialPort(QString path) //Déconnexion RS232
{
    QTextStream outTerminal(stdout);
    serial.close();
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

int main(int argc, char *argv[]){
    QTextStream sortieTerminal(stdout), entreeTerminal(stdin);
    QApplication app(argc, argv);
    QByteArray sock,dataRead;
    Client client;
    QString path = "/media/virtualram/";
    int iter, iterMax,socketWrite = 0;
    bool comEnCours = true, connectedToHost = false;
    std::time_t reconnectTime;

    //Init
    QApplication::setApplicationDisplayName(Client::tr("Fortune Client"));
    gettimeofday(&debutTimer,NULL);
    reception.reserve(3000); //Memory reservation
    historical.reserve(3000);//??
    reception.resize(0); //Taille 0
    historical.resize(0);//??

    int argumentCount = QApplication::arguments().size(); //number of arguments
    QStringList argumentList = QApplication::arguments(); //arguments list

    if (argumentCount == 1  ) {
        sortieTerminal << QObject::tr("Usage %1 <serialportname> [baudrate]").arg(argumentList.first()) << endl;
                return 1;
    }
    QString serialPortName = argumentList.at(1);
    serial.setPortName(serialPortName);

    int serialPortBaudRate = (argumentCount > 2) ? argumentList.at(2).toInt() : QSerialPort::Baud38400; //38400 default

    openSerialPort(serialPortName,serialPortBaudRate); //Open Serial port

    iterMax = (argumentCount > 3) ? argumentList.at(3).toInt() : -1; //Default = while(1)
    iter = 0;

    QWidget window;
    window.show();

    client.getServerIPv4ThroughUDPBroadcast();

    client.readPendingDatagrams();

    connectedToHost = client.connectToHost();
    reconnectTime = std::time(nullptr);

    while (iter<iterMax || iterMax<0){
        //Implement broadcast search for PC-SOL ipv4 in order to use dynamic ipv4 adress in PC-SOL

        dataRead = readSerialData();
        qDebug() << "dataRead HEX:" << dataRead.toHex()<<endl;
        qDebug() << "Connected to Host:" << connectedToHost <<endl;

        if(connectedToHost){
            if(client.TCPsocket->waitForReadyRead()){
                sock = client.TCPsocket->readAll();

                qDebug() << "lecture wifi HEX:" << sock.toHex()<<endl;
                //QThread::sleep(3);
                qDebug() << "serial.write(sock):" << serial.write(sock)<<endl;

                socketWrite = client.TCPsocket->write(dataRead);

                qDebug() << "client.socket->write(dataRead):" << socketWrite<<endl;

                if(socketWrite<0){// disconnect if its not possible to send data to host
                    client.TCPsocket->disconnectFromHost();
                    connectedToHost = false;
                }
            }
            else{//disconnect if host doesnt answer for 30 sec
                client.TCPsocket->disconnectFromHost();
                connectedToHost = false;
                qDebug() << "serial.write(vide1):" << serial.write(QByteArray())<<endl; //writes null array to continue the flux of communication
            }

        }
        else{
            qDebug() << "serial.write(vide2):" << serial.write(QByteArray())<<endl; //writes null array to continue the flux of communication

            if(std::difftime(std::time(nullptr),reconnectTime) > CONNECYCICLESEC){ //try to reconnect after CONNECYCICLESEC seconds
                client.readPendingDatagrams();

                connectedToHost = client.connectToHost();//Implement broadcast search for PC-SOL ipv4 in order to use dynamic ipv4 adress in PC-SOL
                reconnectTime = std::time(nullptr);
            }
        }

        if(iter == INT_MAX-100)//to avoid overflow
            iter = 0;
        iter++;
    }
    sortieTerminal << QObject::tr("disconnectiong from host") << endl;
    client.TCPsocket->disconnectFromHost();
    sortieTerminal << QObject::tr("closing Serial Port") << endl;
    //closeSerialPort(path);
    //return app.exec();
    return 0;
}

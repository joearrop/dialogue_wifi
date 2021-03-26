#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <string>
#include <iostream>
#include "serial.h"

Serial::Serial(QObject *parent) : QObject(parent){
    serialPort = new QSerialPort; //new QSerialPort(this);
}

/*
Seriaal::~Seriaal(){
     Seriaal::closeSerialPort();
     delete this;
}
*/

QByteArray Serial::readSerialData(){
    static bool firstReadSerialData = true;
    QTextStream sortieTerminal(stdout);
    QByteArray dataRead;

    if(firstReadSerialData)
    {
        gettimeofday(&startTime,NULL);
        firstReadSerialData = false;
    }
    if(serialPort->error() != QSerialPort::ParityError) //Vérification de la parité
    {
        serialPort->waitForReadyRead(1000); //Attente - timeout
        dataRead = serialPort->readAll(); //Lecture de tout ce qu'il y a
    }
    return dataRead;
}

int Serial::openSerialPort(QString serialPortName,int serialPortBaudRate){
    if (!serialPort->open(QIODevice::ReadWrite)) {//Serial open error
           qDebug() << "Failed to open port %1, error: " << serialPort->error() << " - " << serialPort->errorString() << endl;
           return 0;
    }
    else
    {
        qDebug() << "Connected To Port " << serialPortName << endl;
        serialPort->setBaudRate(serialPortBaudRate); //Serial Communication BaudRate
        serialPort->setDataBits(QSerialPort::Data8); //8 bit cell packet
        serialPort->setParity(QSerialPort::NoParity); //No parity check every cell packet
        serialPort->setStopBits(QSerialPort::OneStop); //One Stop bit
        serialPort->setFlowControl(QSerialPort::NoFlowControl);//No hardware and no software flow control (handshake etc)
        if (serialPort->error() == QSerialPort::ReadError) {
            qDebug() << QObject::tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serialPort->errorString()) << endl;
            return 0;
        }
        else{
            return 1;
        }
    }


}

void Serial::closeSerialPort(){ //Déconnexion RS232
    QTextStream outTerminal(stdout);
    serialPort->close();
    qDebug() << "Serial Port Closed Succesfully"<<endl;
    if((!reception->isEmpty())||(!historical->isEmpty()))
    {
        QFile fileReception, fileHistorical;

        fileReception.setFileName(path+"reception.txt");
        fileHistorical.setFileName(path+"historical.txt");

        if(!fileReception.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream outReception(&fileReception);
        for(int i=0;i<reception->size();i++) outReception << (*reception)[i] << endl;
        fileReception.close();

        if(!fileHistorical.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream outHistorical(&fileHistorical);
        for(int i=0;i<historical->size();i++) outHistorical << (*historical)[i] << endl;
        fileHistorical.close();
    }

    reception->clear();
    reception->resize(0);
    reception->squeeze();
    historical->clear();
    historical->resize(0);
    historical->squeeze();
    #ifdef DEBUG
        QProcess::execute("sudo shutdown -h now"); //RR1611
    #endif
}

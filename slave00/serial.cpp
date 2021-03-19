#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include "client.h"
#include "serial.h"
#include <QtWidgets>
#include <QString>
#include <string>
#include <iostream>

//void readSerialData(){
//    static bool firstReadSerialData = true;
//    QTextStream sortieTerminal(stdout);

//    if(firstReadSerialData)
//    {
//        gettimeofday(&startTime,NULL);
//        firstReadSerialData = false;
//    }
//    if(serial.error() != QSerialPort::ParityError) //Vérification de la parité
//    {
//        QByteArray dataRead;
//        serial.waitForReadyRead(1000); //Attente - timeout 8ms
//        dataRead = serial.readAll(); //Lecture de tout ce qu'il y a
//        sortieTerminal << QObject::tr("dataRead:") << QObject::tr(dataRead) << endl;
//    }
//}

//void closeSerialPort(QString path) //Déconnexion RS232
//{
//    QTextStream outTerminal(stdout);
//    serial.close();
//    outTerminal << QObject::tr("Serial Port Closed Succesfully");
//    if((!reception.isEmpty())||(!historical.isEmpty()))
//    {
//        QFile fileReception, fileHistorical;

//        fileReception.setFileName(path+"reception.txt");
//        fileHistorical.setFileName(path+"historical.txt");

//        if(!fileReception.open(QIODevice::WriteOnly | QIODevice::Text)) return;
//        QTextStream outReception(&fileReception);
//        for(int i=0;i<reception.size();i++) outReception << reception[i] << endl;
//        fileReception.close();

//        if(!fileHistorical.open(QIODevice::WriteOnly | QIODevice::Text)) return;
//        QTextStream outHistorical(&fileHistorical);
//        for(int i=0;i<historical.size();i++) outHistorical << historical[i] << endl;
//        fileHistorical.close();
//    }

//    reception.clear();
//    reception.resize(0);
//    reception.squeeze();
//    historical.clear();
//    historical.resize(0);
//    historical.squeeze();
//    #ifdef DEBUG
//        QProcess::execute("sudo shutdown -h now"); //RR1611
//    #endif
//}

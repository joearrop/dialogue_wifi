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

static std::string getAnswer()
{
    std::string answer;
    std::cin >> answer;
    return answer;
}

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

void closeSerialPort(QString path) //Déconnexion RS232
{
    QTextStream outTerminal(stdout);
    serial.close();
    outTerminal << QObject::tr("Serial Port Closed Succesfully");
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

int main(int argc, char *argv[])
{
    QTextStream sortieTerminal(stdout);
    QTextStream entreeTerminal(stdin);
    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName(Client::tr("Fortune Client"));
    Client client;
    QString path = "/media/virtualram/";
    bool comEnCours = true;
    //    client.show();
    //Init
    gettimeofday(&debutTimer,NULL);
    reception.reserve(3000); //Réservation mémoire
    historical.reserve(3000);
    reception.resize(0); //Taille 0
    historical.resize(0);

    int argumentCount = QApplication::arguments().size(); //nbre arguments
    QStringList argumentList = QApplication::arguments(); //nom des arguments

    if (argumentCount == 1  ) {
        sortieTerminal << QObject::tr("Usage %1 <serialportname> [baudrate]").arg(argumentList.first()) << endl;
                return 1;
    }
    QString serialPortName = argumentList.at(1);
    serial.setPortName(serialPortName);

    int serialPortBaudRate = (argumentCount > 2) ? argumentList.at(2).toInt() : QSerialPort::Baud19200; //19200 par defaut

    if (!serial.open(QIODevice::ReadWrite)) {
           sortieTerminal << QObject::tr("Failed to open port %1, error: %2 - %3").arg(serialPortName).arg(serial.error()).arg(serial.errorString()) << endl;
           return 1;
    }
    else
    {
        sortieTerminal << QObject::tr("Connected To Port %1").arg(serialPortName) << endl;
        serial.setBaudRate(serialPortBaudRate);
        serial.setDataBits(QSerialPort::Data8); //Correcte
        serial.setParity(QSerialPort::NoParity); //Correcte, avant il y avait: QSerialPort::EvenParity
        serial.setStopBits(QSerialPort::OneStop); //Correcte
        serial.setFlowControl(QSerialPort::NoFlowControl);//sais pas
    }

    if (serial.error() == QSerialPort::ReadError) {
               sortieTerminal << QObject::tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serial.errorString()) << endl;
               return 1;
    }
    /*char arr[3] = {0x02, 0x04, 0x46};
    char arrF[3] = {0x32, 0x34, 0x46};
    QByteArray ba(arr, 3);
    QByteArray baF(arrF, 3);*/

    QByteArray sock,dataRead;

    int iterMax = (argumentCount > 3) ? argumentList.at(3).toInt() : -1; //"infinit" par defaut
    int iter = 0;

    client.connectToHost();
    while (comEnCours) {

        client.socket ->waitForReadyRead();
        sock = client.socket->readAll();
        qDebug() << "lecture wifi HEX:" << sock.toHex()<<endl;
        //QThread::sleep(3);
        qDebug() << "serial.write(sock):" << serial.write(sock)<<endl;

        dataRead = readSerialData();
        qDebug() << "dataRead HEX:" << dataRead.toHex()<<endl;
        qDebug() << "client.socket->write(dataRead):" << client.socket->write(dataRead)<<endl;

        if(iter>iterMax && iterMax>=0)
            comEnCours = false;
        iter++;
    }
    sortieTerminal << QObject::tr("closeSerialPort") << endl;
    client.socket->disconnectFromHost();
    closeSerialPort(path);
    return app.exec();
}

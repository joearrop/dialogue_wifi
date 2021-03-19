#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include "client.h"
#include <QtWidgets>
#include <QString>
#include <string>


int start = 0;
bool firstReadSerialData, flagEnd;
struct timeval startTime,debutTimer;
QSerialPort serial;
double temps;
uint nModify;
uchar count_ctrl_r, countBytes, etat;
qint64 chrono;
qint32 xx, yy ,aa, gg;
bool comEnCours;
QVector<QString> historical, reception;
QString path;


void readSerialData()
{
    QTextStream sortieTerminal(stdout);

    flagEnd = false;
    if(firstReadSerialData)
    {
        gettimeofday(&startTime,NULL);
        temps = 0;
    }
    if(serial.error() != QSerialPort::ParityError) //Vérification de la parité
    {
        QByteArray dataRead;
        serial.waitForReadyRead(1000); //Attente - timeout 8ms
        dataRead = serial.readAll(); //Lecture de tout ce qu'il y a
        sortieTerminal << QObject::tr("dataRead") << endl;
        sortieTerminal << QObject::tr(dataRead) << endl;
    }
}

void closeSerialPort() //Déconnexion RS232
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
    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName(Client::tr("Fortune Client"));
    Client client;
    //    client.show();

    firstReadSerialData = true;
    flagEnd = false;
    //*****Init
    nModify = 0;
    count_ctrl_r = 0;
    etat = 1;
    countBytes = 0;
    chrono = 0;
    xx = 0;
    yy = 0;
    aa = 0;
    comEnCours = true;
    gettimeofday(&debutTimer,NULL);

    reception.reserve(3000); //Réservation mémoire
    historical.reserve(3000);
    reception.resize(0); //Taille 0
    historical.resize(0);

    path = "/media/virtualram/";


    int argumentCount = QApplication::arguments().size(); //nbre arguments
    QStringList argumentList = QApplication::arguments(); //nom des arguments

    if (argumentCount == 1) {
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
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::EvenParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
    }

    if (serial.error() == QSerialPort::ReadError) {
               sortieTerminal << QObject::tr("Failed to read from port %1, error: %2").arg(serialPortName).arg(serial.errorString()) << endl;
               return 1;
    }


    while (comEnCours) {
//            if(start == 0)
//            {
//                client.connectToHost();
//                start = 1;
//            }
            readSerialData();
//            client.socket->waitForReadyRead();
//             QByteArray sock = client.socket->readAll();
//             int available = client.socket->bytesAvailable();
//             sortieTerminal << QObject::tr("bytes available : ") << endl;
//             sortieTerminal << QObject::tr("%1").arg(available) << endl;
//            sortieTerminal << QObject::tr("lecture") << endl;
//            sortieTerminal << QObject::tr(sock) << endl;
            //QThread::sleep(3);
            //serial.write("A14587462152DFT21G5");
            sortieTerminal << QObject::tr("dans la boucle") << endl;
    }
    sortieTerminal << QObject::tr("closeSerialPort") << endl;
    closeSerialPort();




    return app.exec();
}

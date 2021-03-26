#ifndef MAINTHREAD_H
#define MAINTHREAD_H
#include <QtCore>
#include <QtSerialPort/QSerialPort>

#define CONNECYCICLESEC 5


class MainThread : public QThread{
public:
    MainThread();
    void run();

    QByteArray readSerialData();
    int openSerialPort(QString serialPortName,int serialPortBaudRate);
    void closeSerialPort(QString path);

    int argumentCount; //number of arguments
    QStringList argumentList; //arguments list
    QString serialPortName, path = "/media/virtualram/";
    int serialPortBaudRate, iterMax;
    struct timeval startTime;
    QSerialPort *serial = new QSerialPort;
    QVector<QString> historical, reception;
};

#endif // MAINTHREAD_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <QTimer>
#include <QThread>

class Client : public QObject{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void getServerIPv4ThroughUDPBroadcast();

    QObject *client_obj;
    QTcpSocket *TCPsocket;
    QUdpSocket *UDPsocket;
    std::string ServerIPv4 = "192.168.1.42";

public slots:
    //TCP slots
    bool connectToHost(const char* ipv4,int timeThresholdms);
    bool connectToHost();
    //UDP slots
    void readPendingDatagrams();



private:

};




#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <QTimer>
#include <QThread>

#define UDPIP 0
#define UDPBROAD 1
#define TCPIP 2
#define UDPTIMEOUTSEC 10


class Client : public QObject{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void getServerIPv4ThroughUDPBroadcast();
    void bindUDPcommsocket();
    void bindBroadcommsocket();

    QObject *client_obj;
    QTcpSocket *TCPsocket;
    QUdpSocket *UDPsocketDiscovery;
    QUdpSocket *UDPsocketComm;
    QUdpSocket *UDPsocketBroadComm;
    std::string ServerIPv4 = "192.168.1.42";
    std::string SubNetBroadcastIPv4 = "192.168.1.255";

public slots:
    //TCP slots
    bool connectToHost(const char* ipv4,int timeThresholdms);
    bool connectToHost();
    //UDP slots
    void readPendingDatagramsIP();
    QByteArray readUDPMsg();
    QByteArray readBroadMsg();



private:

};




#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <QTimer>
#include <QThread>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    QObject *client_obj;
    QTcpSocket *socket;

public slots:
   bool connectToHost(char* ipv4,int timeThresholdms);
   bool connectToHost();

private:

};




#endif // CLIENT_H

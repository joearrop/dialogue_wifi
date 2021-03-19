#pragma once

#include <QObject>
#include <QSocketNotifier>

class ConsoleReader : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleReader(QObject *parent = 0);
    QString getText();
signals:
    void textReceived(QString message);
public slots:
    void text();
private:
    QSocketNotifier notifier;
    QString tt;
};

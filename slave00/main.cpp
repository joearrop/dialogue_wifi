#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <sstream>
#include <string>
#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <ctime>
#include "mainthread.h"
#include "client.h"
#include "ConsoleReader.h"
#include "mainwindow.h"

int main(int argc, char *argv[]){
    QTextStream sortieTerminal(stdout), entreeTerminal(stdin);
    QApplication app(argc, argv);
    MainThread mThread;
    MainWindow window;
    struct timeval debutTimer;

    //envoyer
    mThread.argumentCount = QApplication::arguments().size(); //number of arguments
    mThread.argumentList = QApplication::arguments(); //arguments list

    //Init
    QApplication::setApplicationDisplayName(Client::tr("Fortune Client"));
    gettimeofday(&debutTimer,NULL);

    //GUI
    window.show();

    mThread.start();

    return app.exec();
}

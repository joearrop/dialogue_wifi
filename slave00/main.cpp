#include <sys/time.h>
#include <QtSerialPort/QSerialPort>
#include <QObject>
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
#include "LinkThreadGUI.h"

int main(int argc, char *argv[]){
    QTextStream sortieTerminal(stdout), entreeTerminal(stdin);
    QApplication app(argc, argv);
    MainThread mThread;
    MainWindow window;
    struct timeval debutTimer;

    mThread.argumentCount = QApplication::arguments().size(); //number of arguments
    mThread.argumentList = QApplication::arguments(); //arguments list

    //Init
    QApplication::setApplicationDisplayName(Client::tr("Axter Automation"));
    gettimeofday(&debutTimer,NULL);

    LinkThreadGUI link;
    mThread.link = &link;
    //conect ui and thread
    QObject::connect(&link,&LinkThreadGUI::feedback_PCSOL,&window,&MainWindow::LogPCSOL);
    QObject::connect(&link,&LinkThreadGUI::feedback_Chariot,&window,&MainWindow::LogChariot);

    //GUI
    //set stylesheet

    //show
    window.show();

    //run main thread
    mThread.start();


    return app.exec();
}

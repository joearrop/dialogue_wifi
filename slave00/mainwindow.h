//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

//#include <QMainWindow>

//namespace Ui {
//class MainWindow;
//}

//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    explicit MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

//private:
//    Ui::MainWindow *ui;
//};

//#endif // MAINWINDOW_H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onReadyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket  _socket;
};

#endif // MAINWINDOW_H

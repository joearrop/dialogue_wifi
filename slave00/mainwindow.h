#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "LinkThreadGUI.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    LinkThreadGUI *link;
public slots:
    void LogPCSOL(QString msg);
    void LogChariot(QString msg);

    void handleDisconnectButton();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

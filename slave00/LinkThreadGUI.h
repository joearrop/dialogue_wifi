#ifndef LINKTHREADGUI_H
#define LINKTHREADGUI_H

#include <QObject>

#define DISCONNECTCOMMAND 2

class LinkThreadGUI : public QObject
{
    Q_OBJECT
public:
    explicit LinkThreadGUI(QObject *parent = nullptr);

    void send_feedback_PCSOL(QString msg);
    void send_feedback_Chariot(QString msg);

    void send_UI_Command(int cmd);

signals:
    void feedback_PCSOL(QString msg);
    void feedback_Chariot(QString msg);

    void UI_Command(int cmd);

public slots:
};

#endif // LINK_THREAD_GUI_H

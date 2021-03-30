#ifndef LINKTHREADGUI_H
#define LINKTHREADGUI_H

#include <QObject>

class LinkThreadGUI : public QObject
{
    Q_OBJECT
public:
    explicit LinkThreadGUI(QObject *parent = nullptr);

    void send_feedback_PCSOL(QString msg);
    void send_feedback_Chariot(QString msg);

signals:
    void feedback_PCSOL(QString msg);
    void feedback_Chariot(QString msg);

public slots:
};

#endif // LINK_THREAD_GUI_H

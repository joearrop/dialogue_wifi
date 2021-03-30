#include "LinkThreadGUI.h"

LinkThreadGUI::LinkThreadGUI(QObject *parent) : QObject(parent)
{

}

void LinkThreadGUI::send_feedback_PCSOL(QString msg){
    emit feedback_PCSOL(msg);
}

void LinkThreadGUI::send_feedback_Chariot(QString msg){
    emit feedback_Chariot(msg);
}

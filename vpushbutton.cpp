#include "vpushbutton.h"


VPushButton::VPushButton(QString label) : QPushButton(label)
{

}

VPushButton::VPushButton(int addr, QString label) : QPushButton(label)
{
    setAddr(addr);
}

int VPushButton::getValue(){
    return this->isChecked()? 1 : 0;
}

void VPushButton::addValueWithData(QString item, QVariant data){
    //faz nada.
}


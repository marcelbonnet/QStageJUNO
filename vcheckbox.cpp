#include "vcheckbox.h"


VCheckBox::VCheckBox(QString label) : QCheckBox(label)
{

}

VCheckBox::VCheckBox(int addr, QString label) : QCheckBox(label)
{
    setAddr(addr);
}

int VCheckBox::getValue(){
    return this->isChecked()? 1 : 0;
}

void VCheckBox::addValueWithData(QString item, QVariant data){
    //faz nada.
}


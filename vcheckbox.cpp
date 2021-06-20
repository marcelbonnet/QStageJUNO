#include "vcheckbox.h"


VCheckBox::VCheckBox(QString label) : QCheckBox(label)
{

}

VCheckBox::VCheckBox(int addr, int addrOffset, QString label) : QCheckBox(label)
{
    setAddr(addr);
    setAddrOffset(addrOffset);
}

int VCheckBox::getValue(){
    return this->isChecked()? 1 : 0;
}

void VCheckBox::addValueWithData(QString item, QVariant data){
    //faz nada.
}


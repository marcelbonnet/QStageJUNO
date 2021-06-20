#include "vspinbox.h"


VSpinBox::VSpinBox(int offset) : QSpinBox()
{
    this->offset = offset;
}

VSpinBox::VSpinBox(int offset, int min, int max) : QSpinBox()
{
    setRange(min, max);
    this->offset = offset;
}

VSpinBox::VSpinBox(int addr, int addrOffset, int offset, int min, int max) : QSpinBox()
{
    setRange(min, max);
    this->offset = offset;
    setAddr(addr);
    setAddrOffset(addrOffset);
}

int VSpinBox::getValue(){
    return this->getValue() - offset;
}

void VSpinBox::addValueWithData(QString item, QVariant data){
    //faz nada.
}


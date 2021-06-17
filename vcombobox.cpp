#include "vcombobox.h"

VComboBox::VComboBox(int offset) : QComboBox()
{
    this->offset = offset;
}

VComboBox::VComboBox(int addr, int offset) : QComboBox()
{
    this->offset = offset;
    setAddr(addr);
}

int VComboBox::getValue(){
    QVariant data = itemData(this->currentIndex());
    if(data != QVariant::Invalid){
        //FIXME vai dar pau se o data for um Patch*
        return data.value<int>();
    } else
        return this->currentIndex() - offset;

}

Patch* VComboBox::getPatch(){
    return itemData(currentIndex()).value<Patch*>();
}

void VComboBox::addValueWithData(QString item, QVariant data){
    addItem(item, QVariant::fromValue(data));
}


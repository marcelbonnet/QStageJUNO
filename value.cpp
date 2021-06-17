#include "value.h"

Value::Value()
{

}

void Value::setAddr(int addr){
    this->address = addr;
}

int Value::getAddr(){
    return this->address;
}

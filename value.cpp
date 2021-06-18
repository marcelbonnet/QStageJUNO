#include "value.h"

Value::Value()
{

}


const int  Value::PERF_COMMON = 0x10000000 ;
const int  Value::PERF_COMMON_MFX1 =   0x10000200 ;
const int  Value::PERF_COMMON_CHORUS = 0x10000400 ;
const int  Value::PERF_COMMON_REVERB = 0x10000600 ;
const int  Value::PERF_COMMON_MFX2 = 0x10000800 ;
const int  Value::PERF_COMMON_MFX3 = 0x10000A00 ;
const int  Value::PERF_MIDI_CH =     0x10001000 ;
const int  Value::PERF_PART =        0x10002000;
const int  Value::PERF_ZONE_CH =     0x10005000 ;
const int  Value::PERF_CTRL =        0x10006000 ;

void Value::setAddr(int addr){
    this->address = addr;
}

int Value::getAddr(){
    return this->address;
}

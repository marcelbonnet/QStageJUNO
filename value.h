#ifndef VALUE_H
#define VALUE_H

#include <QString>
#include <QVariant>

class Value
{
public:
    Value();
    virtual int getValue() = 0;
    virtual void addValueWithData(QString item, QVariant data) = 0;

    void setAddr(int addr);
    int getAddr();

    static const int PERF_PART;
    static const int PERF_COMMON ;
    static const int PERF_COMMON_MFX1 ;
    static const int PERF_COMMON_CHORUS ;
    static const int PERF_COMMON_REVERB ;
    static const int PERF_COMMON_MFX2 ;
    static const int PERF_COMMON_MFX3 ;
    static const int PERF_MIDI_CH ;
    static const int PERF_ZONE_CH ;
    static const int PERF_CTRL ;

private:
    int address;

};

#endif // VALUE_H

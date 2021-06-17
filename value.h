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

private:
    int address;

};

#endif // VALUE_H

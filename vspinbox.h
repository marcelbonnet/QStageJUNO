#ifndef VSPINBOX_H
#define VSPINBOX_H

#include "value.h"
#include <QSpinBox>

class VSpinBox : public QSpinBox, public Value
{
    Q_OBJECT;
public:
    VSpinBox(int offset);
    VSpinBox(int offset, int min, int max);
    VSpinBox(int addr, int addrOffset, int offset, int min, int max);
    virtual int getValue() override;
    virtual void addValueWithData(QString item, QVariant data) override;


private:
    int offset;
};

#endif // VSPINBOX_H

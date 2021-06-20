#ifndef VCHECKBOX_H
#define VCHECKBOX_H

#include "value.h"
#include <QCheckBox>

class VCheckBox : public QCheckBox, public Value
{
    Q_OBJECT;
public:
    VCheckBox(QString label);
    VCheckBox(int addr, int addrOffset, QString label);
    virtual int getValue() override;
    virtual void addValueWithData(QString item, QVariant data) override;
};

#endif // VCHECKBOX_H

#ifndef VCHECKBOX_H
#define VCHECKBOX_H

#include "value.h"
#include <QPushButton>

class VPushButton : public QPushButton, public Value
{
    Q_OBJECT;
public:
    VPushButton(QString label);
    VPushButton(int addr, QString label);
    virtual int getValue() override;
    virtual void addValueWithData(QString item, QVariant data) override;
};

#endif // VCHECKBOX_H

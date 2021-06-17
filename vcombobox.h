#ifndef VCHECKBOX_H
#define VCHECKBOX_H

#include "value.h"
#include <QComboBox>
#include "patch.h"

class VComboBox : public QComboBox, public Value
{
    Q_OBJECT;
public:
    VComboBox(int offset);
    VComboBox(int addr, int offset);
    virtual int getValue() override;
    virtual void addValueWithData(QString item, QVariant data) override;
    Patch* getPatch();

private:
    int offset;
};

#endif // VCHECKBOX_H
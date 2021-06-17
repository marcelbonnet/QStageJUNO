#ifndef PATCH_H
#define PATCH_H

#include <QVariant>
#include <QString>
#include <QMetaType>

class Patch : public QVariant
{
public:
    Patch();
    Patch(int id, QString strPatch, QString name, QString categ, QString newCateg, bool favorite, int msb, int lsb, int pc, QString bank, bool roland, int rolandId);

    Patch(QString strPatch, QString name, QString categ, QString newCateg, bool favorite, int msb, int lsb, int pc, QString bank, bool roland, int rolandId);


    int id;
    QString strPatch;
    QString name;
    QString categ;
    QString newCateg;
    bool favorite;
    int msb;
    int lsb;
    int pc;
    QString bank;
    QString roland;
    int rolandId;

    QString getPatchFullName();

    static const QString CATEGORIES[39];

};

Q_DECLARE_METATYPE(Patch*)

#endif // PATCH_H

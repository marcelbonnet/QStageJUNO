#include "patch.h"

Patch::Patch()
{


}

Patch::Patch(int id, QString strPatch, QString name, QString categ, QString newCateg, bool favorite, int msb, int lsb, int pc, QString bank, bool roland, int rolandId){
    this->id = id;
    this->strPatch = strPatch;
    this->name = name;
    this->categ = categ;
    this->newCateg = newCateg;
    this->favorite = favorite;
    this->msb = msb;
    this->lsb = lsb;
    this->pc = pc;
    this->bank = bank;
    this->roland = roland;
    this->rolandId = rolandId;
}

Patch::Patch(QString strPatch, QString name, QString categ, QString newCateg, bool favorite, int msb, int lsb, int pc, QString bank, bool roland, int rolandId){
    this->strPatch = strPatch;
    this->name = name;
    this->categ = categ;
    this->newCateg = newCateg;
    this->favorite = favorite;
    this->msb = msb;
    this->lsb = lsb;
    this->pc = pc;
    this->bank = bank;
    this->roland = roland;
    this->rolandId = rolandId;
}

const QString Patch::CATEGORIES[39] = {"ACD",
                              "AGT",
                              "BEL",
                              "BPD",
                              "BRS",
                              "BS",
                              "BTS",
                              "CMB",
                              "DGT",
                              "DRM",
                              "EGT",
                              "EP",
                              "ETH",
                              "FLT",
                              "FRT",
                              "FX",
                              "HIT",
                              "HLD",
                              "HRM",
                              "KEY",
                              "MLT",
                              "ORC",
                              "ORG",
                              "PLK",
                              "PLS",
                              "PNO",
                              "PRC",
                              "SAX",
                              "SBR",
                              "SBS",
                              "SFX",
                              "SLD",
                              "SMP",
                              "SPD",
                              "STR",
                              "SYN",
                              "TEK",
                              "VOX",
                              "WND"
                             };

QString Patch::getPatchFullName(){
    return QString("%1 %2").arg(this->rolandId).arg(this->name);
}

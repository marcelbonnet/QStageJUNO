#ifndef MIDI_H
#define MIDI_H

#include <QString>
#include <QList>
#include <QWidget>
#include <QProcess>

class Midi
{
public:
    Midi();

    static int checksum(int addr, int data);
    static QString makeMsg(int addr, int data);
    void enviar(QString msg);
};

#endif // MIDI_H

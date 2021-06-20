#ifndef UIPERFORM_H
#define UIPERFORM_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include "value.h"
#include "vcombobox.h"
#include "vcheckbox.h"
#include "vpushbutton.h"
#include "vspinbox.h"
#include <QLineEdit>
#include <QMetaType>
#include "patch.h"

namespace Ui {
class UIPerform;
}

class UIPerform : public QWidget
{
    Q_OBJECT

public:
    explicit UIPerform(QWidget *parent = nullptr);
    ~UIPerform();

    enum Controles {
        // PATCH E LEVEL/CHANNEL TABS
        PART_LABEL_0,
        KBD,
        GROUP,
        PATCH,
        SOLO,
        MUTE,
        LEVEL,
        PAN,
        RXCH,
        RXSW,
        // OUTPUT TAB
        PART_LABEL_1,
        OUTPUT,
        OUTPUT_MFX_SELECTION,
        OUTPUT_LEVEL,
        OUTPUT_CHORUS,
        OUTPUT_REVERB,
        OUTPUT_1,
        OUTPUT_2,
        OUTPUT_3,
        OUTPUT_C,
        OUTPUT_R,
        //PITCH tab
        PITCH_PART_LABEL ,
        PITCH_OCTAVE ,
        PITCH_COARSE ,
        PITCH_FINE ,
        PITCH_MONO ,
        PITCH_LEGATO ,
        PITCH_BEND ,
        PITCH_PORTAMENTO ,
        PITCH_PORT_TIME ,
        //KBD (Zone) Tab
        ZONE_PART_LABEL ,
        ZONE_KBD_SWITCH ,
        ZONE_RANGE_LOWER ,
        ZONE_RANGE_UPPER ,
        ZONE_VELOCITY_SENS ,
        ZONE_VOICE_RESERVE ,
        ZONE_OCTAVE ,
        // OFFSET E VIBRATO TAB
        OFFSET_PART_LABEL ,
        OFFSET_CUTOFF ,
        OFFSET_RESONANCE ,
        OFFSET_ATTACK ,
        OFFSET_DECAY ,
        OFFSET_RELEASE ,
        VIBRATO_RATE ,
        VIBRATO_DEPTH ,
        VIBRATO_DELAY ,
        //SCALE TAB
        SCALE_PART_LABEL,
        SCALE_C ,
        SCALE_C_SHARP ,
        SCALE_D ,
        SCALE_E_FLAT ,
        SCALE_E ,
        SCALE_F ,
        SCALE_F_SHARP ,
        SCALE_G ,
        SCALE_G_SHARP ,
        SCALE_A ,
        SCALE_B_FLAT ,
        SCALE_B ,
        // MIDI TAB
        MIDI_PART_LABEL,
        MIDI_PROGRAM_CHANGE ,
        MIDI_BANK_SELECT ,
        MIDI_PITCH_BEND ,
        MIDI_POLYPHONIC_AFTERTOUCH ,
        MIDI_CHANNEL_AFTERTOUCH ,
        MIDI_MODULATION ,
        MIDI_VOLUME ,
        MIDI_PAN ,
        MIDI_EXPRESSION ,
        MIDI_HOLD1 ,
        MIDI_PHASE_LOCK ,
        MIDI_VELOCITY_CURVE
    };

    void setSlotConnections(bool b);
    void enviar();

    bool static valueLessThan(Value *v1, Value *v2);

private slots:
    void onChangeOutput123CR(int);

private:
    Ui::UIPerform *ui;
    QList<QList<QWidget*>*> *parts;
    QList<QList<Value*>*> *partsValue;

    void makePart(int part);


};

Q_DECLARE_METATYPE(UIPerform::Controles)

#endif // UIPERFORM_H

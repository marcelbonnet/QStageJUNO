#include "uiperform.h"
#include "ui_uiperform.h"

#include <QGridLayout>
#include <QDebug>

UIPerform::UIPerform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIPerform)
{
    ui->setupUi(this);

    parts = new QList<QList<QWidget*>*>();

    for (short i=0;i<=15;i++) {
        parts->append(makePart(i));
    }


    //adicionar no layout para cada tab
    for (short row=0;row<=15;row++) {
        for (short col=0;col<parts->at(row)->count() ;col++) {
            // Patch/Level tab
            if(col <= 9){
                QGridLayout *grid = (QGridLayout*) ui->scrollAreaWidgetContents->layout();
                grid->addWidget(parts->at(row)->at(col), row+1, col, Qt::AlignLeft);
            }

            // Output tab
            if(col >= 10 && col <= 20){
                int offset = 10;
                QGridLayout *grid = (QGridLayout*) ui->scrollAreaWidgetContents_2->layout();
                grid->addWidget(parts->at(row)->at(col), row+1, col-offset, Qt::AlignLeft);
            }

            // Output tab
            if(col >= 21 && col <= 29){
                int offset = 21;
                QGridLayout *grid = (QGridLayout*) ui->scrollAreaWidgetPitch->layout();
                grid->addWidget(parts->at(row)->at(col), row+1, col-offset, Qt::AlignLeft);
            }

            // KBD (Zone) Tab
            if(col >= 30 && col <= 36){
                int offset = 30;
                QGridLayout *grid = (QGridLayout*) ui->scrollAreaWidgetZone->layout();
                grid->addWidget(parts->at(row)->at(col), row+1, col-offset, Qt::AlignLeft);
            }

            // OFFSET/VIBRATO TABS
            if(col >= 37 && col <= 45){
                int offset = 37;
                QGridLayout *grid = (QGridLayout*) ui->scrollAreaWidgeOffSetVibrato->layout();
                grid->addWidget(parts->at(row)->at(col), row+1, col-offset, Qt::AlignLeft);
            }

            // SCALE
            if(col >= 46 && col <= 58){
                int offset = 46;
                QGridLayout *grid = (QGridLayout*) ui->scrollAreaWidgetScale->layout();
                grid->addWidget(parts->at(row)->at(col), row+1, col-offset, Qt::AlignLeft);
            }

            // MIDI
            if(col >= 59 && col <= 71){
                int offset = 59;
                QGridLayout *grid = (QGridLayout*) ui->scrollAreaWidgeMidiSwitches->layout();
                grid->addWidget(parts->at(row)->at(col), row+1, col-offset, Qt::AlignLeft);
            }
        }
    }

}

void UIPerform::setSlotConnections(bool b){
    if(b){
        //QObject::connect()
    } else {

    }
}

void UIPerform::onChangeOutput123CR(int){
    QCheckBox *source = qobject_cast<QCheckBox*>(sender());
    int index = source->property("index").value<int>();

    if (!source->isChecked()) return;

    for (short i=0;i<=15;i++) {
        QCheckBox *ck = (QCheckBox*) parts->at(i)->at(index);

        if(source != ck){
            ck->setChecked(false);
        }
    }
}

QList<QWidget*>* UIPerform::makePart(int part){
    QList<QWidget*> *el = new QList<QWidget*>();

    QLabel *lblPart = new QLabel(QString::number(part+1));
    QCheckBox *kbd = new QCheckBox("");

    QComboBox *group = new QComboBox();
    //TODO lista de grupos e filtrar patches pelo grupo

    QComboBox *patch = new QComboBox();
    //TODO patches

    QCheckBox *solo = new QCheckBox("");
    QCheckBox *mute = new QCheckBox("");
    QSpinBox *level = new QSpinBox();
    level->setRange(0,127);
    QSpinBox *pan = new QSpinBox();
    pan->setRange(0,127);
    pan->setValue(63);
    QSpinBox *rxch = new QSpinBox();
    rxch->setRange(1,16);
    rxch->setValue(part+1);
    QCheckBox *rxsw = new QCheckBox("");
    rxsw->setChecked(true);

    el->append(lblPart);
    el->append(kbd);
    el->append(group);
    el->append(patch);
    el->append(solo);
    el->append(mute);
    el->append(level);
    el->append(pan);
    el->append(rxch);
    el->append(rxsw);

    // Output
    QLabel *outLblPart = new QLabel(QString::number(part+1));
    QComboBox *out = new QComboBox();
    out->addItem("MFX",0);
    out->addItem("L+R Mono",1);
    out->addItem("L",5);
    out->addItem("R",6);
    out->addItem("Patch",13);

    QSpinBox *mfxSel = new QSpinBox();
    mfxSel->setRange(1,3);
    QSpinBox *outLevel = new QSpinBox();
    outLevel->setRange(0,127);
    QSpinBox *outChorus = new QSpinBox();
    outChorus->setRange(0,127);
    QSpinBox *outReverb = new QSpinBox();
    outReverb->setRange(0,127);

    // FIXME: preciso entender isso. Só sei que só pode ter um ativado por vez.
    QCheckBox *out1 = new QCheckBox("");
    QCheckBox *out2 = new QCheckBox("");
    QCheckBox *out3 = new QCheckBox("");
    QCheckBox *outC = new QCheckBox("");
    QCheckBox *outR = new QCheckBox("");

    out1->setProperty("index",QVariant::fromValue(Controles::OUTPUT_1));
    out2->setProperty("index",QVariant::fromValue(Controles::OUTPUT_2));
    out3->setProperty("index",QVariant::fromValue(Controles::OUTPUT_3));
    outC->setProperty("index",QVariant::fromValue(Controles::OUTPUT_C));
    outR->setProperty("index",QVariant::fromValue(Controles::OUTPUT_R));

    QObject::connect(out1, SIGNAL(stateChanged(int)), this, SLOT(onChangeOutput123CR(int)));
    QObject::connect(out2, SIGNAL(stateChanged(int)), this, SLOT(onChangeOutput123CR(int)));
    QObject::connect(out3, SIGNAL(stateChanged(int)), this, SLOT(onChangeOutput123CR(int)));
    QObject::connect(outC, SIGNAL(stateChanged(int)), this, SLOT(onChangeOutput123CR(int)));
    QObject::connect(outR, SIGNAL(stateChanged(int)), this, SLOT(onChangeOutput123CR(int)));

    el->append(outLblPart);
    el->append(out);
    el->append(mfxSel);
    el->append(outLevel);
    el->append(outChorus);
    el->append(outReverb);
    el->append(out1);
    el->append(out2);
    el->append(out3);
    el->append(outC);
    el->append(outR);

    //PITCH TAB
    QLabel *pitchLblPart = new QLabel(QString::number(part+1));
    QSpinBox *pitchOctaveShitf = new QSpinBox();
    QSpinBox *pitchCoarse = new QSpinBox();
    QSpinBox *pitchFine = new QSpinBox();
    QComboBox *pitchMono = new QComboBox();
    QComboBox *pitchLegato = new QComboBox();
    QComboBox *pitchBend = new QComboBox();
    QComboBox *pitchPortamento = new QComboBox();
    QComboBox *pitchPortTime = new QComboBox();

    pitchOctaveShitf->setRange(-3,3);
    pitchCoarse->setRange(-48,48);
    pitchFine->setRange(-50,50);

    pitchMono->addItem("MONO");
    pitchMono->addItem("POLY");
    pitchMono->addItem("PATCH");

    pitchLegato->addItem("OFF");
    pitchLegato->addItem("ON");
    pitchLegato->addItem("PATCH");

    for(int i=0; i<=24; i++)
        pitchBend->addItem(QString::number(i));
    pitchBend->addItem("PATCH");

    pitchPortamento->addItem("OFF");
    pitchPortamento->addItem("ON");
    pitchPortamento->addItem("PATCH");

    for(int i=0; i<=127; i++)
        pitchPortTime->addItem(QString::number(i));
    pitchPortTime->addItem("PATCH");

    el->append(pitchLblPart);
    el->append(pitchOctaveShitf);
    el->append(pitchCoarse);
    el->append(pitchFine);
    el->append(pitchMono);
    el->append(pitchLegato);
    el->append(pitchBend);
    el->append(pitchPortamento);
    el->append(pitchPortTime);


    /******************
     *  KBD (Zone) Tab
     ******************/
    QLabel *zoneLblPart = new QLabel(QString::number(part+1));
    QPushButton *zoneSwitch = new QPushButton("ON/OFF");
    QComboBox *zoneRangeLower = new QComboBox();
    QComboBox *zoneRangeUpper = new QComboBox();
    //mistura o performance part aqui?
    QSpinBox *zoneVelocitySens = new QSpinBox();
    QComboBox *zoneVoiceReserve = new QComboBox();
    QSpinBox *zoneOctave = new QSpinBox();

    QString notas[] = {"C","C#","D","Eb","E","F","F#","G","G#","A","Bb","B"};

    for(int i=-1; i<=9; i++){
        for(int n=0; n<12; n++){
            zoneRangeLower->addItem(QString("%1 %2").arg(notas[n]).arg(i));
            zoneRangeUpper->addItem(QString("%1 %2").arg(notas[n]).arg(i));
            if(i==9)
                if(n==7)
                    break;
        }
    }

    zoneSwitch->setCheckable(true);
    zoneVelocitySens->setRange(-63,63);

    for(int i=0; i<=63; i++)
        zoneVoiceReserve->addItem(QString::number(i));
    zoneVoiceReserve->addItem("FULL");

    zoneOctave->setRange(-3,3);

    el->append(zoneLblPart);
    el->append(zoneSwitch);
    el->append(zoneRangeLower);
    el->append(zoneRangeUpper);
    el->append(zoneVelocitySens);
    el->append(zoneVoiceReserve);
    el->append(zoneOctave);

    /**************************
     * OFFSET + VIBRATO TAB
     * ***********************/
    QLabel *offLblPart = new QLabel(QString::number(part+1));
    QSpinBox *offsetCut = new QSpinBox();
    QSpinBox *offsetReso = new QSpinBox();
    QSpinBox *offsetAttack = new QSpinBox();
    QSpinBox *offsetDecay = new QSpinBox();
    QSpinBox *offsetRelease = new QSpinBox();
    QSpinBox *vibratoRate = new QSpinBox();
    QSpinBox *vibratoDepth = new QSpinBox();
    QSpinBox *vibratoDelay = new QSpinBox();

    offsetCut->setRange(-64,63);
    offsetReso->setRange(-64,63);
    offsetAttack->setRange(-64,63);
    offsetDecay->setRange(-64,63);
    offsetRelease->setRange(-64,63);
    vibratoRate->setRange(-64,63);
    vibratoDepth->setRange(-64,63);
    vibratoDelay->setRange(-64,63);

    el->append(offLblPart);
    el->append(offsetCut);
    el->append(offsetReso);
    el->append(offsetAttack);
    el->append(offsetDecay);
    el->append(offsetRelease);
    el->append(vibratoRate);
    el->append(vibratoDepth);
    el->append(vibratoDelay);


    /***********************
     * SCALE Tab
     * ***********************/
    QLabel *scalefLblPart = new QLabel(QString::number(part+1));
    el->append(scalefLblPart);
    for(int n=0; n<12; n++){
        QSpinBox *scale = new QSpinBox();
        scale->setRange(-64,63);
        el->append(scale);
    }

    /***********************
     * MIDI Tab
     * ***********************/
    QLabel *midifLblPart = new QLabel(QString::number(part+1));
    el->append(midifLblPart);
    for(int n=0; n<11; n++){
        QCheckBox *chk = new QCheckBox();
        el->append(chk);
    }
    QComboBox *midiVelocityCurve = new QComboBox();

    QPixmap pixmapCurve1(QString(":/icones/patchtone/tvf/v-curve-%1.png").arg(3));
    QPixmap pixmapCurve2(QString(":/icones/patchtone/tvf/v-curve-%1.png").arg(2));
    QPixmap pixmapCurve3(QString(":/icones/patchtone/tvf/v-curve-%1.png").arg(4));
    QPixmap pixmapCurve4(QString(":/icones/patchtone/tvf/v-curve-%1.png").arg(5));
    QIcon iconCurve1(pixmapCurve1);
    QIcon iconCurve2(pixmapCurve2);
    QIcon iconCurve3(pixmapCurve3);
    QIcon iconCurve4(pixmapCurve4);
    midiVelocityCurve->addItem("OFF");
    midiVelocityCurve->addItem(iconCurve1, "1");
    midiVelocityCurve->addItem(iconCurve2, "2");
    midiVelocityCurve->addItem(iconCurve3, "3");
    midiVelocityCurve->addItem(iconCurve4, "4");
    midiVelocityCurve->setIconSize(QSize(30,30));
    midiVelocityCurve->setMaximumWidth(70);

    el->append(midiVelocityCurve);

    return el;
}

UIPerform::~UIPerform()
{
    delete ui;
}

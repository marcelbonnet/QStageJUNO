#include "uiperform.h"
#include "ui_uiperform.h"

#include <QGridLayout>
#include <QDebug>
#include "midi.h"

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
    VCheckBox *source = qobject_cast<VCheckBox*>(sender());
    int index = source->property("index").value<int>();

    if (!source->isChecked()) return;

    for (short i=0;i<=15;i++) {
        VCheckBox *ck = (VCheckBox*) parts->at(i)->at(index);

        if(source != ck){
            ck->setChecked(false);
        }
    }
}

QList<QWidget*>* UIPerform::makePart(int part){
    QList<QWidget*> *el = new QList<QWidget*>();

    QLabel *lblPart = new QLabel(QString::number(part+1));
    VPushButton *kbd = new VPushButton(0x001b, "ON/OFF");
    kbd->setCheckable(true);

    VComboBox *group = new VComboBox(0);
    for(int i=0; i<39; i++)
        group->addItem(Patch::CATEGORIES[i]);

    VComboBox *patch = new VComboBox(0x0004, 0);
    /*
     * 5	Pf:005	JUNO Piano 1	PNO	87	64	5	PRESET		PNO

     * */
    Patch *p1 = new Patch("Pf:005","JUNO Piano 1","PNO","PNO",false,87,64,5,"PRESET",true,5);
    Patch *p2 = new Patch("Wr:075","Flute+1octLS","ETH","ETH",true,87,72,87,"India",true,1111);
    Patch *p3 = new Patch("Wr:005","Vintage Call","BEL","BEL",true,87,72,101,"India",true,1125);
    patch->addItem(p1->getPatchFullName(), QVariant::fromValue(p1));
    patch->addItem(p2->getPatchFullName(), QVariant::fromValue(p2));
    patch->addItem(p3->getPatchFullName(), QVariant::fromValue(p3));

    VCheckBox *solo = new VCheckBox("");
    VCheckBox *mute = new VCheckBox("");
    QSpinBox *level = new QSpinBox();
    level->setRange(0,127);
    QSpinBox *pan = new QSpinBox();
    pan->setRange(0,127);
    pan->setValue(63);
    QSpinBox *rxch = new QSpinBox();
    rxch->setRange(1,16);
    rxch->setValue(part+1);
    VCheckBox *rxsw = new VCheckBox("");
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
    VComboBox *out = new VComboBox();
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
    VCheckBox *out1 = new VCheckBox("");
    VCheckBox *out2 = new VCheckBox("");
    VCheckBox *out3 = new VCheckBox("");
    VCheckBox *outC = new VCheckBox("");
    VCheckBox *outR = new VCheckBox("");

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
    VComboBox *pitchMono = new VComboBox();
    VComboBox *pitchLegato = new VComboBox();
    VComboBox *pitchBend = new VComboBox();
    VComboBox *pitchPortamento = new VComboBox();
    VComboBox *pitchPortTime = new VComboBox();

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
    VPushButton *zoneSwitch = new VPushButton("ON/OFF");
    VComboBox *zoneRangeLower = new VComboBox();
    VComboBox *zoneRangeUpper = new VComboBox();
    //mistura o performance part aqui?
    QSpinBox *zoneVelocitySens = new QSpinBox();
    VComboBox *zoneVoiceReserve = new VComboBox();
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
        VCheckBox *chk = new VCheckBox("");
        el->append(chk);
    }
    VComboBox *midiVelocityCurve = new VComboBox();

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

void UIPerform::enviar(){
    QString msg = "";

    // por part 1-16

    /*
     * Part 10 (index 9)
     *  não tem Octave, enviar assim mesmo?
     *  garantir apenas Patches de DRM
     * */

    int addr = 0x10000000;
    int part = 0;

    //Performance MIDI pg 31
    /*
     * super tipo de qwidget para cada tipo:
     * tipo->setAddress()
     * tipo->getVal()
     *
     * Interface
     *   setAddr
     *   addValueWithData   (prop ItemValue , testar se é tipo <Patch*> )
     *   getAddr
     *   getValue
     *      se tem Data -> retornda
     *      se tem Patch retorna o valor
     *      se não tem nada retorna currentIndex
     *
     * QList que implemente ordenar por getAddr
     * */

    qDebug() << (qobject_cast<VCheckBox*>(parts->at(part)->at(RXCH)) == NULL);
    qDebug() << (qobject_cast<VCheckBox*>(parts->at(part)->at(RXSW)) == NULL);
//    msg += Midi::makeMsg(addr + 0x0000, ((VComboBox*)parts->at(part)->at(RXCH))->currentIndex() -1);
//    msg += Midi::makeMsg(addr + 0x0001, ((VCheckBox*)parts->at(part)->at(RXSW))->isChecked()? 1 : 0 );

}

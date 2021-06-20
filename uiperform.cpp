#include "uiperform.h"
#include "ui_uiperform.h"

#include <QGridLayout>
#include <QDebug>
#include "midi.h"
#include <algorithm>

UIPerform::UIPerform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIPerform)
{
    ui->setupUi(this);

    parts = new QList<QList<QWidget*>*>();
    partsValue = new QList<QList<Value*>*>();

    for (short i=0;i<=15;i++) {
        makePart(i);
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

void UIPerform::makePart(int part){
    parts->append(new QList<QWidget*>());
    partsValue->append(new QList<Value*>());

    QLabel *lblPart = new QLabel(QString::number(part+1));
    VPushButton *kbd = new VPushButton(Value::PERF_ZONE_CH , 0x0001, "ON/OFF");
    kbd->setCheckable(true);

    VComboBox *group = new VComboBox(0);
    for(int i=0; i<39; i++)
        group->addItem(Patch::CATEGORIES[i]);

    VComboBox *patch = new VComboBox(Value::PERF_PART , 0x0004, 0);
    /*
     * 5	Pf:005	JUNO Piano 1	PNO	87	64	5	PRESET		PNO

     * */
    Patch *p1 = new Patch("Pf:005","JUNO Piano 1","PNO","PNO",false,87,64,5,"PRESET",true,5);
    Patch *p2 = new Patch("Wr:075","Flute+1octLS","ETH","ETH",true,87,72,87,"India",true,1111);
    Patch *p3 = new Patch("Wr:005","Vintage Call","BEL","BEL",true,87,72,101,"India",true,1125);
    patch->addItem(p1->getPatchFullName(), QVariant::fromValue(p1));
    patch->addItem(p2->getPatchFullName(), QVariant::fromValue(p2));
    patch->addItem(p3->getPatchFullName(), QVariant::fromValue(p3));

    VCheckBox *solo = new VCheckBox( -000000001 ,0, ""); // FIXME o que é esse solo?
    VCheckBox *mute = new VCheckBox(Value::PERF_PART , 0x001b, "");
    VSpinBox *level = new VSpinBox(Value::PERF_PART , 0x0007, 0, 0, 127);
    VSpinBox *pan = new VSpinBox(Value::PERF_PART , 0x0008, 0, 0, 127);
    pan->setValue(63);
    VSpinBox *rxch = new VSpinBox(Value::PERF_PART , 0x00, 1, 1, 16);
    rxch->setValue(part+1);
    VCheckBox *rxsw = new VCheckBox(Value::PERF_PART , 0x0001, "");
    rxsw->setChecked(true);

    parts->at(part)->append(lblPart);
    parts->at(part)->append(kbd);
    parts->at(part)->append(group);
    parts->at(part)->append(patch);
    parts->at(part)->append(solo);
    parts->at(part)->append(mute);
    parts->at(part)->append(level);
    parts->at(part)->append(pan);
    parts->at(part)->append(rxch);
    parts->at(part)->append(rxsw);

    // Output
    QLabel *outLblPart = new QLabel(QString::number(part+1));
    VComboBox *out = new VComboBox(Value::PERF_PART , 0x001F, 0 );
    out->addValueWithData("MFX",0);
    out->addValueWithData("L+R Mono",1);
    out->addValueWithData("L",5);
    out->addValueWithData("R",6);
    out->addValueWithData("Patch",13);

    VSpinBox *mfxSel = new VSpinBox(Value::PERF_PART , 0x0020, 1, 1, 3);

    VSpinBox *outLevel = new VSpinBox(Value::PERF_PART , 0x001C, 0, 0, 127);
    VSpinBox *outChorus = new VSpinBox(Value::PERF_PART , 0x001D, 0, 0, 127);
    VSpinBox *outReverb = new VSpinBox(Value::PERF_PART , 0x001E, 0, 0, 127);

    // preciso entender isso. Só sei que só pode ter um ativado por vez.
    // FIXME ver se é do Setup (pg.21) MFX1 Switch (0x000A até Reverb switch)
    VCheckBox *out1 = new VCheckBox(0,0, "");
    VCheckBox *out2 = new VCheckBox(0,0, "");
    VCheckBox *out3 = new VCheckBox(0,0, "");
    VCheckBox *outC = new VCheckBox(0,0, "");
    VCheckBox *outR = new VCheckBox(0,0, "");

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

    parts->at(part)->append(outLblPart);
    parts->at(part)->append(out);
    parts->at(part)->append(mfxSel);
    parts->at(part)->append(outLevel);
    parts->at(part)->append(outChorus);
    parts->at(part)->append(outReverb);
    parts->at(part)->append(out1);
    parts->at(part)->append(out2);
    parts->at(part)->append(out3);
    parts->at(part)->append(outC);
    parts->at(part)->append(outR);

    //PITCH TAB
    QLabel *pitchLblPart = new QLabel(QString::number(part+1));
    VSpinBox *pitchOctaveShitf = new VSpinBox(Value::PERF_PART , 0x0015, -64, -3, 3 ); //FIXME confirmar se é dessa página de endereços
    VSpinBox *pitchCoarse = new VSpinBox(Value::PERF_PART , 0x0009, -64, -48, 48 );
    VSpinBox *pitchFine = new VSpinBox(Value::PERF_PART , 0x000A, -64, -50, 50 );
    VComboBox *pitchMono = new VComboBox(Value::PERF_PART , 0x000B, 0 );
    VComboBox *pitchLegato = new VComboBox(Value::PERF_PART , 0x000C, 0);
    VComboBox *pitchBend = new VComboBox(Value::PERF_PART , 0x000D, 0);
    VComboBox *pitchPortamento = new VComboBox(Value::PERF_PART , 0x000E, 0);
    VComboBox *pitchPortTime = new VComboBox(Value::PERF_PART , 0x000F, 0);


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

    parts->at(part)->append(pitchLblPart);
    parts->at(part)->append(pitchOctaveShitf);
    parts->at(part)->append(pitchCoarse);
    parts->at(part)->append(pitchFine);
    parts->at(part)->append(pitchMono);
    parts->at(part)->append(pitchLegato);
    parts->at(part)->append(pitchBend);
    parts->at(part)->append(pitchPortamento);
    parts->at(part)->append(pitchPortTime);


    /******************
     *  KBD (Zone) Tab
     ******************/
    QLabel *zoneLblPart = new QLabel(QString::number(part+1));
    VPushButton *zoneSwitch = new VPushButton(-00000000000001, 0, "ON/OFF");//FIXME é o mesmo botão da primeira aba
    VComboBox *zoneRangeLower = new VComboBox(Value::PERF_ZONE_CH , 0x000C, 0);
    VComboBox *zoneRangeUpper = new VComboBox(Value::PERF_ZONE_CH , 0x000D, 0);
    //mistura o performance part aqui?
    VSpinBox *zoneVelocitySens = new VSpinBox(Value::PERF_PART , 0x0016, -64, -63, 63);
    VComboBox *zoneVoiceReserve = new VComboBox(Value::PERF_COMMON , 0x0010, 0); //FIXME é do Performance Common, mesmo?
    VSpinBox *zoneOctave = new VSpinBox(Value::PERF_ZONE_CH , 0x0000, -64, -3, 3);

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

    for(int i=0; i<=63; i++)
        zoneVoiceReserve->addItem(QString::number(i));
    zoneVoiceReserve->addItem("FULL");


    parts->at(part)->append(zoneLblPart);
    parts->at(part)->append(zoneSwitch);
    parts->at(part)->append(zoneRangeLower);
    parts->at(part)->append(zoneRangeUpper);
    parts->at(part)->append(zoneVelocitySens);
    parts->at(part)->append(zoneVoiceReserve);
    parts->at(part)->append(zoneOctave);

    /**************************
     * OFFSET + VIBRATO TAB
     * ***********************/
    QLabel *offLblPart = new QLabel(QString::number(part+1));
    VSpinBox *offsetCut = new VSpinBox(Value::PERF_PART , 0x0011, -64, -64, 63);
    VSpinBox *offsetReso = new VSpinBox(Value::PERF_PART , 0x0012, -64, -64, 63);
    VSpinBox *offsetAttack = new VSpinBox(Value::PERF_PART , 0x0013, -64, -64, 63);
    VSpinBox *offsetDecay = new VSpinBox(Value::PERF_PART , 0x0021, -64, -64, 63);
    VSpinBox *offsetRelease = new VSpinBox(Value::PERF_PART , 0x0014, -64, -64, 63);
    VSpinBox *vibratoRate = new VSpinBox(Value::PERF_PART , 0x0022, -64, -64, 63);
    VSpinBox *vibratoDepth = new VSpinBox(Value::PERF_PART , 0x0023, -64, -64, 63);
    VSpinBox *vibratoDelay = new VSpinBox(Value::PERF_PART , 0x0024, -64, -64, 63);

    parts->at(part)->append(offLblPart);
    parts->at(part)->append(offsetCut);
    parts->at(part)->append(offsetReso);
    parts->at(part)->append(offsetAttack);
    parts->at(part)->append(offsetDecay);
    parts->at(part)->append(offsetRelease);
    parts->at(part)->append(vibratoRate);
    parts->at(part)->append(vibratoDepth);
    parts->at(part)->append(vibratoDelay);


    /***********************
     * SCALE Tab
     * ***********************/
    QLabel *scalefLblPart = new QLabel(QString::number(part+1));
    parts->at(part)->append(scalefLblPart);
    for(int n=0; n<12; n++){
        VSpinBox *scale = new VSpinBox(Value::PERF_PART , 0x0025 + n, -64, -64, 63);
        parts->at(part)->append(scale);
        partsValue->at(part)->append(scale);
    }

    /***********************
     * MIDI Tab
     * ***********************/
    QLabel *midifLblPart = new QLabel(QString::number(part+1));
    parts->at(part)->append(midifLblPart);
    for(int n=0; n<11; n++){
        VCheckBox *chk = new VCheckBox(Value::PERF_MIDI_CH , 0x0000 + n , "");
        parts->at(part)->append(chk);
        partsValue->at(part)->append(chk);
    }
    VComboBox *midiVelocityCurve = new VComboBox(Value::PERF_MIDI_CH , 0x000B, 0);

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

    parts->at(part)->append(midiVelocityCurve);

//    for(int i=0; i<parts->at(part)->count(); i++){
//        partsValue->at(part)->append(  );
//    }

//    partsValue->at(part)->append(new VCheckBox(-1,-1,""));
    partsValue->at(part)->append(kbd);
    partsValue->at(part)->append(group);
    partsValue->at(part)->append(patch);
    partsValue->at(part)->append(solo);
    partsValue->at(part)->append(mute);
    partsValue->at(part)->append(level);
    partsValue->at(part)->append(pan);
    partsValue->at(part)->append(rxch);
    partsValue->at(part)->append(rxsw);
//    partsValue->at(part)->append(new VCheckBox(-1,-1,""));
    partsValue->at(part)->append(out);
    partsValue->at(part)->append(mfxSel);
    partsValue->at(part)->append(outLevel);
    partsValue->at(part)->append(outChorus);
    partsValue->at(part)->append(outReverb);
    partsValue->at(part)->append(out1);
    partsValue->at(part)->append(out2);
    partsValue->at(part)->append(out3);
    partsValue->at(part)->append(outC);
    partsValue->at(part)->append(outR);
//    partsValue->at(part)->append(new VCheckBox(-1,-1,""));
    partsValue->at(part)->append(pitchOctaveShitf);
    partsValue->at(part)->append(pitchCoarse);
    partsValue->at(part)->append(pitchFine);
    partsValue->at(part)->append(pitchMono);
    partsValue->at(part)->append(pitchLegato);
    partsValue->at(part)->append(pitchBend);
    partsValue->at(part)->append(pitchPortamento);
    partsValue->at(part)->append(pitchPortTime);
//    partsValue->at(part)->append(new VCheckBox(-1,-1,""));
    partsValue->at(part)->append(zoneSwitch);
    partsValue->at(part)->append(zoneRangeLower);
    partsValue->at(part)->append(zoneRangeUpper);
    partsValue->at(part)->append(zoneVelocitySens);
    partsValue->at(part)->append(zoneVoiceReserve);
    partsValue->at(part)->append(zoneOctave);
//    partsValue->at(part)->append(new VCheckBox(-1,-1,""));
    partsValue->at(part)->append(offsetCut);
    partsValue->at(part)->append(offsetReso);
    partsValue->at(part)->append(offsetAttack);
    partsValue->at(part)->append(offsetDecay);
    partsValue->at(part)->append(offsetRelease);
    partsValue->at(part)->append(vibratoRate);
    partsValue->at(part)->append(vibratoDepth);
    partsValue->at(part)->append(vibratoDelay);
//    partsValue->at(part)->append(scalefLblPart);
//    partsValue->at(part)->append(scale);
//    partsValue->at(part)->append(midifLblPart);
//    partsValue->at(part)->append(chk);
    partsValue->at(part)->append(midiVelocityCurve);


}

UIPerform::~UIPerform()
{
    delete ui;
}

bool UIPerform::valueLessThan(Value *v1, Value *v2){
    return v1->operator<(*v2);
}

void UIPerform::enviar(){
//    QString msg = "";

//    // por part 1-16

//    /*
//     * Part 10 (index 9)
//     *  não tem Octave, enviar assim mesmo?
//     *  garantir apenas Patches de DRM
//     * */

//    int addr = 0x10000000;
//    int part = 0;

//    //Performance MIDI pg 31
//    /*
//     * super tipo de qwidget para cada tipo:
//     * tipo->setAddress()
//     * tipo->getVal()
//     *
//     * Interface
//     *   setAddr
//     *   addValueWithData   (prop ItemValue , testar se é tipo <Patch*> )
//     *   getAddr
//     *   getValue
//     *      se tem Data -> retornda
//     *      se tem Patch retorna o valor
//     *      se não tem nada retorna currentIndex
//     *
//     * QList que implemente ordenar por getAddr
//     * */

//    qDebug() << (qobject_cast<VCheckBox*>(parts->at(part)->at(RXCH)) == NULL);
//    qDebug() << (qobject_cast<VCheckBox*>(parts->at(part)->at(RXSW)) == NULL);
//    msg += Midi::makeMsg(addr , 0x0000, ((VComboBox*)parts->at(part)->at(RXCH))->currentIndex() -1);
//    msg += Midi::makeMsg(addr , 0x0001, ((VCheckBox*)parts->at(part)->at(RXSW))->isChecked()? 1 : 0 );

    QList<Value*> *partValue = partsValue->at(0);

    qDebug() << "=====================================";
    for(int i=0; i<partValue->count(); i++) {
        qDebug() << partValue->at(i)->getAddr() + partValue->at(i)->getAddrOffset();
    }

    std::sort(partValue->begin(), partValue->end(), valueLessThan);
    qDebug() << "====================== ORDENADA ===============";
    for(int i=0; i<partValue->count(); i++) {
        qDebug() << partValue->at(i)->getAddr() + partValue->at(i)->getAddrOffset();
    }

}

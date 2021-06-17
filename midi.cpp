#include "midi.h"
#include <QDebug>

Midi::Midi()
{

}

int Midi::checksum(int addr, int data)
{
    int a,b,c,d, e, f, soma = 0;
    a = b = c = d = e = f = soma = 0;
    //endereço
    a = addr & 0xFF;
    b = (addr >> 8) & 0xFF;
    c = (addr >> 16) & 0xFF;
    d = (addr >> 24) & 0xFF;
    //dados
    if(data <= 0xFF){
        e=data;
    } else {
        e = data & 0xFF;
        f = (data >> 8) & 0xFF;
    }

    soma = 128 - ( (a+b+c+d+e+f)%128 );

    return soma;
}

QString Midi::makeMsg(int addr, int data){
    int a,b,c,d, e, f, soma = 0;
    a = b = c = d = e = f = soma = 0;
    //endereço
    a = addr & 0xFF;
    b = (addr >> 8) & 0xFF;
    c = (addr >> 16) & 0xFF;
    d = (addr >> 24) & 0xFF;
    //dados
    if(data <= 0xFF){
        e=data;
    } else {
        e = data & 0xFF;
        f = (data >> 8) & 0xFF;
    }

    soma = checksum(addr, data);

    return QString("%1 %2 %3 %4 %5 %6 %7 %8 F7 ")
            .arg("F0 41 10 00 00 3A 12")
            .arg(QString::number(a,16))
            .arg(QString::number(b,16))
            .arg(QString::number(c,16))
            .arg(QString::number(d,16))
            .arg(QString::number(e,16))
            .arg(QString::number(f,16))
            .arg(QString::number(soma,16)) ;

}

void Midi::enviar(QString msg){
    /*
     *
    QThread* thread = new QThread;
    WorkerSerialMidi* worker = new WorkerSerialMidi(smidi);
    worker->moveToThread(thread);
    // "this" não é um QObject para implementar errorString(QString)
    //QObject::connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
    QObject::connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    */

    qDebug() << "ENVIAR...";

    QProcess proc;
    QStringList args;
    args << "-i" << "20" << "-p" << "hw:1,0,0" << "-S" << "10 0 0 0 41 10 0 0 1 42 10 0 0 2 43 10 0 0 3 44";
    proc.start("/usr/bin/amidi", args);
    proc.waitForFinished();
}

#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/icones/QStage.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Carregando", Qt::AlignLeft, Qt::yellow);

    MainWindow w;
    w.show();
    return a.exec();
}

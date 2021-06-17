#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTabWidget>
#include <QTabBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MainWindow::showMaximized();
    ui->setupUi(this);

    /* QTabWidget UI
     * */
    QTabWidget* tab = ui->tabWidget;
    tab->setTabPosition(QTabWidget::TabPosition::West);
    tab->setTabText(0, "");
    QTabBar* tabBar = tab->tabBar();
    tabBar->setTabButton(0, QTabBar::LeftSide, new QLabel("Set List"));

    perform = new UIPerform();

    tab->addTab(perform, "");
    tab->addTab(new QLabel("teste"), "");
    tabBar->setTabButton(1, QTabBar::LeftSide, new QLabel("Perform"));
    tabBar->setTabButton(2, QTabBar::LeftSide, new QLabel("Patch"));
//    QLabel* tabLabel1 = new QLabel("Perform");
//    QLabel* tabLabel2 = new QLabel("Patch");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionEnviar_triggered()
{
    perform->enviar();
}

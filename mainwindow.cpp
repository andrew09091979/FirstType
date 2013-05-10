#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen_New_Device, SIGNAL(triggered()),SLOT(NewDev()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewDev()
{
//    DeviceHolder<Device, Protocol10007, ConnectionImplQT, float>* dev
//            = new DeviceHolder<Device, Protocol10007, ConnectionImplQT, float>();
    DeviceHolder<Device, Protocol10007, connectionImplRandomStub, float>* dev
            = new DeviceHolder<Device, Protocol10007, connectionImplRandomStub, float>();
    ui->mdiArea->addSubWindow((*dev)());
    dev->show();
}

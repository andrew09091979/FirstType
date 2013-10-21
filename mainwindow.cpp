#include "mainwindow.h"
#include "enteringaddress.h"
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

    EnteringAddress e;
    e.exec();
//    DeviceHolder<Device, Protocol10007, ConnectionImplQT, float>* dev
//            = new DeviceHolder<Device, Protocol10007, ConnectionImplQT, float>();
      DeviceHolder<Device, Protocol10007, connectionImplRandomStub, float>* dev
              = new DeviceHolder<Device, Protocol10007, connectionImplRandomStub, float>();
//    DeviceHolder<Device, Protocol10007, ConnectionImplBoost, float>* dev
//            = new DeviceHolder<Device, Protocol10007, ConnectionImplBoost, float>();
    QMdiSubWindow * mdiDevWnd = ui->mdiArea->addSubWindow((*dev)());
    QObject::connect(mdiDevWnd,SIGNAL(destroyed(QObject *)),this,SLOT(on_DeviceWindowClosed(QObject *)));
    QObject::connect(mdiDevWnd, SIGNAL(windowStateChanged(Qt::WindowStates, Qt::WindowStates)),
                     this, SLOT(on_DevWndStateChanged(Qt::WindowStates, Qt::WindowStates)));
    dev->show();
}

void MainWindow::on_mdiArea_destroyed()
{
    qDebug() << "From mdiArea destroyed";
}

void MainWindow::on_mdiArea_destroyed(QObject *arg1)
{
     qDebug() << "From mdiArea destroyed1";
}

void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    qDebug() << "From mdiArea on_mdiArea_subWindowActivated";
}
void MainWindow::on_DeviceWindowClosed(QObject *obj)
{
    qDebug() << "From mdiSubWindow destroyed//////////////////////////////////////////////";
}

void MainWindow::on_DevWndStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState)
{
    //qDebug() << "on_DevWndStateChanged oldState=" <<oldState << "  newState = " << newState << "////////////////";
}

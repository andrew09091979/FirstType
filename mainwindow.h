#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "protocol10007.h"
#include "devwnd.h"
#include "deviceholder.h"
#include "device.h"
#include "connectionImplQT.h"
#include "connectionImplRandomStub.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void NewDev();

    void on_DeviceWindowClosed(QObject *obj = 0);
    void on_DevWndStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState);
private slots:
    void on_mdiArea_destroyed();

    void on_mdiArea_destroyed(QObject *arg1);

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "protocol10007.h"
#include "devwnd.h"
#include "deviceholder.h"
#include "device.h"
#include "connectionImplQT.h"
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
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

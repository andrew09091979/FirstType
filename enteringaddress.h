#ifndef ENTERINGADDRESS_H
#define ENTERINGADDRESS_H

#include <QDialog>

namespace Ui {
class EnteringAddress;
}

class EnteringAddress : public QDialog
{
    Q_OBJECT
    
public:
    explicit EnteringAddress(QWidget *parent = 0);
    ~EnteringAddress();
    
private:
    Ui::EnteringAddress *ui;
};

#endif // ENTERINGADDRESS_H

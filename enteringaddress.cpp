#include "enteringaddress.h"
#include "ui_enteringaddress.h"

EnteringAddress::EnteringAddress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnteringAddress)
{
    ui->setupUi(this);
}

EnteringAddress::~EnteringAddress()
{
    delete ui;
}

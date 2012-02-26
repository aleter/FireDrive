#include "firedrive.h"
#include "ui_firedrive.h"

FireDrive::FireDrive(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FireDrive)
{
    ui->setupUi(this);
}

FireDrive::~FireDrive()
{
    delete ui;
}

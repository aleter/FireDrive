#include "firedrive.h"
#include "ui_firedrive.h"

#include "QProcess"

#include "sys/unistd.h"
#include "stdio.h"

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

void FireDrive::_new_mnt()
{
    printf("OLOLOOLO \n ");

}

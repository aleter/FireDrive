#include "firedrive.h"
#include "ui_firedrive.h"

#include "QProcess"
#include "QByteArray"
#include "QStringList"
#include "QFileDialog"

#include "stdio.h"

FireDrive::FireDrive(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FireDrive)
{
    ui->setupUi(this);

    ret = QByteArray();
}

FireDrive::~FireDrive()
{
    delete ui;
}

void FireDrive::run_sh()
{
    ret.clear();
    QStringList arguments;
    QProcess * proc = new QProcess();
    FILE * f = fopen("/tmp/FD__tmp.sh","w+");
    for(int i= 0;i< this->cmds.count();i++)
    {
        fprintf(f,"%s\n",this->cmds[i].toStdString().c_str());
    }
    fprintf(f,"exit\n");
    fclose(f);
    arguments.clear();
    arguments << "-t" << "/bin/sh" << "/tmp/FD__tmp.sh";
    proc->start("kdesu",arguments);
    while(proc->Running)
    {
        int bo = proc->bytesAvailable();
        if( bo > 0 )
        {
            ret = proc->readAllStandardOutput();
        }
    }

    printf("%s",QString("").append(ret).toStdString().c_str());

    delete proc;
    delete f;
}

void FireDrive::_new_mnt()
{
    this->cmds.clear();

    QString fname = QFileDialog::getOpenFileName(this,
         tr("Select image"), "~/", tr("Device Image Files (*.iso)"));
    printf(" -- iso selected %s \n",fname.toStdString().c_str());

    this->cmds.push_back(QString("mdconfig -a -t vnode -f %s -u %d\n").arg(fname,this->mntcount));


    fname = QFileDialog::getExistingDirectory(
            this,
            tr("Select mount point"),
            "~/" );
    printf(" -- mpoint selected %s \n",fname.toStdString().c_str());

    this->cmds.push_back(QString("mount -t cd9660 /dev/md%s %s\n").arg(QString::number(this->mntcount),fname));

    this->cmds.push_back(QString("chmod 777 %s\n").arg(fname));

    this->run_sh();

}

void FireDrive::_init()
{
    this->cmds.clear();
    this->cmds.push_back(QString("mount -l | grep /dev/md\n"));
    this->run_sh();


    this->mntcount = 0; //TODO: check for exiting devices

}

void FireDrive::_un_mnt()
{


}

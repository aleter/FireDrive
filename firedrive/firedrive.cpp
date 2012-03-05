#include "firedrive.h"
#include "ui_firedrive.h"

#include "QProcess"
#include "QByteArray"
#include "QStringList"
#include "QFileDialog"

#include "stdio.h"
#include "string.h"

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
    proc->waitForFinished();

    ret = proc->readAllStandardOutput();
    printf("finished\n");
    printf("%s",QString("").append(ret).toStdString().c_str());

    delete proc;
    //delete f;
}

void FireDrive::_new_mnt()
{
    this->cmds.clear();

    QString fname = QFileDialog::getOpenFileName(this,
         tr("Select image"), "~/", tr("Device Image Files (*.iso)"));
    printf(" -- iso selected %s \n",fname.toStdString().c_str());

    this->cmds.push_back(QString("").sprintf("mdconfig -a -t vnode -f \"%s\" -u %d\n",
                                             fname.toStdString().c_str(),
                                             this->mntcount).toStdString().c_str());


    fname = QFileDialog::getExistingDirectory(
            this,
            tr("Select mount point"),
            "~/" );
    printf(" -- mpoint selected %s \n",fname.toStdString().c_str());

    this->cmds.push_back(QString("").sprintf("mount -t cd9660 /dev/md%s \"%s\"\n",
                                             QString::number(this->mntcount).toStdString().c_str(),
                                             fname.toStdString().c_str()));

    //this->cmds.push_back(QString("").sprintf("chmod 777 \"%s\"\n",
    //                                         fname.toStdString().c_str()));
    this->mntcount++;
    this->run_sh();

}

void FireDrive::_init()
{
    this->cmds.clear();
    this->cmds.push_back(QString("mount -l | grep /dev/md\n"));
    this->run_sh();

    if(this->ret.length()==0)
    {
        this->mntcount = 0;
    }else
    {
        //TODO: check for exiting devices
        QString tstr = QString("").append(this->ret);

    }
}

void FireDrive::_un_mnt()
{


}

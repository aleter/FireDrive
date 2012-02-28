#ifndef FIREDRIVE_H
#define FIREDRIVE_H

#include <QMainWindow>
#include "QProcess"
#include "QByteArray"
#include "QStringList"


namespace Ui {
    class FireDrive;
}

class FireDrive : public QMainWindow
{
    Q_OBJECT

public:
    explicit FireDrive(QWidget *parent = 0);
    ~FireDrive();

    int mntcount;


    QStringList cmds;
    QByteArray ret;
    bool pr_fin;

    void run_sh();

public slots:
    void _init();
    void _new_mnt();
    void _un_mnt();


private:
    Ui::FireDrive *ui;
};

#endif // FIREDRIVE_H

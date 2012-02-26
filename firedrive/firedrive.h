#ifndef FIREDRIVE_H
#define FIREDRIVE_H

#include <QMainWindow>

namespace Ui {
    class FireDrive;
}

class FireDrive : public QMainWindow
{
    Q_OBJECT

public:
    explicit FireDrive(QWidget *parent = 0);
    ~FireDrive();

private:
    Ui::FireDrive *ui;
};

#endif // FIREDRIVE_H

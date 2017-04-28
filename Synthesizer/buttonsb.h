#ifndef BUTTONSB_H
#define BUTTONSB_H

#include <QMainWindow>
#include <mainwindow.h>

class ButtonsB : public QMainWindow, public QMap<QString, QPushButton>
{
    Q_OBJECT

public:
    ButtonsB();

signals:

public slots:
};

#endif // BUTTONSB_H

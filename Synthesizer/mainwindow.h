#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Windows.h>
#include <QKeyEvent>
#include <Qt>
#include <QPushButton>
#include <QSound>
#include <QMap>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>
#include "functions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString path, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_but_clicked();//слот для ловли нажатой клавиши

    void on_open_triggered();//открытие файла

    void on_save_triggered();//сохранение файла

    void on_close_triggered();//закрытие нотного стана

    void on_beginRecord_triggered();//начать запись

    void on_stopRecord_triggered();//закончить запись

    void on_about_triggered();//о программе

    void on_help_triggered();//справка

private:
    Ui::MainWindow *ui;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void closeEvent(QCloseEvent *event);

    void constructButtonsW(); //функция заполнения QMap белыми клавишами
    void constructButtonsB(); //функция заполнения QMap черными клавишами
    void openTextEdit();      //функция открытия нотного стана

    bool window = false, //переменная проверки открыт ли нотный стан
         record = false; //переменная проверки идёт ли запись
    QString path, //путь до exe
            text = ""; //ноты на нотном стане
    int pos_y[5] = {35, 85, 155, 200, 245}; //координаты x черных клавиш
    QString octavesW[7] = {"C", "D", "E", "F", "G", "A", "B"}; //массив хранящий обозначение октавы для белых клавиш
    QString octavesB[5] = {"CD", "DE", "FG", "GA", "AB"};  //массив хранящий обозначение октавы для черных клавиш
    //массив хранящий путь до изображений белых клавиш ненажатых
    QString pictureW[7] = {"border-image: url(:/keys/image/CF.png);",
                           "border-image: url(:/keys/image/D.png);",
                           "border-image: url(:/keys/image/EB.png);",
                           "border-image: url(:/keys/image/CF.png);",
                           "border-image: url(:/keys/image/G.png);",
                           "border-image: url(:/keys/image/A.png);",
                           "border-image: url(:/keys/image/EB.png);"};
    //массив хранящий путь до изображений белых клавиш нажатых
    QString pictureWEntered[5] = {"border-image: url(:/keys/image/enteredCF.png);",
                                  "border-image: url(:/keys/image/enteredD.png);",
                                  "border-image: url(:/keys/image/enteredEB.png);",
                                  "border-image: url(:/keys/image/enteredG.png);",
                                  "border-image: url(:/keys/image/enteredA.png);",};
    //переменная хранящяя путь до излбражения черной нажатой клавиши
    QString pictureB = "border-image: url(:/keys/image/black.png); color: rgb(255, 255, 255);";
    //переменная хранящяя путь до излбражения черной ненажатой клавиши
    QString pictureBEntered = "border-image: url(:/keys/image/enteredBlack.png); color: rgb(255, 255, 255);";
    QMap<int, QPushButton*> buttonsW, buttonsB; //два контейнера клавиш
    //массив хранящий номера клавиш на клавиатуре для белых клавиш
    int keyboardW[35] = {Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4, Qt::Key_5, Qt::Key_6, Qt::Key_7,
                         Qt::Key_8, Qt::Key_9, Qt::Key_0, Qt::Key_Q, Qt::Key_W, Qt::Key_E, Qt::Key_R,
                         Qt::Key_T, Qt::Key_Y, Qt::Key_U, Qt::Key_I, Qt::Key_O, Qt::Key_P, Qt::Key_A,
                         Qt::Key_S, Qt::Key_D, Qt::Key_F, Qt::Key_G, Qt::Key_H, Qt::Key_J, Qt::Key_K,
                         Qt::Key_L, Qt::Key_Z, Qt::Key_X, Qt::Key_C, Qt::Key_V, Qt::Key_B, Qt::Key_N};
    //массив хранящий номера клавиш на клавиатуре для черных клавиш
    int keyboardB[25] = {33, 64, 36, 37, 94,
                         42, 40, Qt::Key_Q, Qt::Key_W, Qt::Key_E,
                         Qt::Key_T, Qt::Key_Y, Qt::Key_I, Qt::Key_O, Qt::Key_P,
                         Qt::Key_S, Qt::Key_D, Qt::Key_G, Qt::Key_H, Qt::Key_J,
                         Qt::Key_L, Qt::Key_Z, Qt::Key_C, Qt::Key_V, Qt::Key_B};

};

#endif // MAINWINDOW_H

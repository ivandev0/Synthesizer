#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->path = path;
    ui->setupUi(this);
    constructButtonsB();
    constructButtonsW();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() & Qt::ShiftModifier)
    {
        QMap<int, QPushButton*>::const_iterator it;
        for(it = buttonsB.constBegin(); it != buttonsB.constEnd(); ++it)
        {
            if(it.key() == event->key())
            {
                it.value()->setStyleSheet(pictureBEntered);
                it.value()->clicked();
                if(record)
                    ui->textEdit->setPlainText(ui->textEdit->toPlainText() + QString(it.key()));
                return;
            }
        }
    }
    QMap<int, QPushButton*>::const_iterator it;
    for(it = buttonsW.constBegin(); it != buttonsW.constEnd(); ++it)
    {
        if(it.key() == event->key())
        {
            it.value()->setStyleSheet(pictureWEntered[switchOctave(it.value()->objectName())]);
            it.value()->clicked();
            if(record)
                ui->textEdit->setPlainText(ui->textEdit->toPlainText() + QString(it.key()).toLower());
            return;
        }
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->modifiers() & Qt::ShiftModifier)
    {
        QMap<int, QPushButton*>::const_iterator it;
        for(it = buttonsB.constBegin(); it != buttonsB.constEnd(); ++it)
        {
            if(it.key() == event->key())
            {
                it.value()->setStyleSheet(pictureB);
                return;
            }
        }
    }
    QMap<int, QPushButton*>::const_iterator it;
    for(it = buttonsW.constBegin(); it != buttonsW.constEnd(); ++it)
    {
        if(it.key() == event->key())
        {
            it.value()->setStyleSheet(pictureW[switchOctave(it.value()->objectName(), 1)]);
            return;
        }
    }
}

void MainWindow::on_but_clicked()
{
    QPushButton* but = qobject_cast<QPushButton*>(sender());
    QSound::play(path + "notes\\" + but->objectName() + ".wav");
}

void MainWindow::constructButtonsW()
{
    for(int i = 0; i < 35; i++)
    {
        QPushButton *but;
        but = new QPushButton(ui->centralWidget);
        but->setGeometry(QRect(10 + 40*i, 0, 40, 300));
        but->setObjectName(octavesW[maximum(7, i)] + QString::number(int(i/7) + 2));
        but->setStyleSheet(pictureW[maximum(7, i)]);
        but->setText("\n\n\n\n\n\n\n\n\n" + QString(keyboardW[i]).toLower());
        but->setStatusTip("Нажмите " + QString(keyboardW[i]).toLower());
        //but->setToolTip("Для воспроизведения нажмите на клавишу");
        but->lower();
        connect(but, SIGNAL(clicked()), this, SLOT(on_but_clicked()));
        buttonsW.insert(keyboardW[i], but);
    }
}
void MainWindow::constructButtonsB()
{
    for(int i = 0; i < 25; i++)
    {
        QPushButton *but;
        but = new QPushButton(ui->centralWidget);
        but->setGeometry(QRect(pos_y[maximum(5, i)] + 280*int(i/5), 0, 20, 191));
        but->setObjectName(octavesB[maximum(5, i)] + QString::number(int(i/5) + 2));
        but->setStyleSheet(pictureB);
        but->setText("\n\n\n\n\n\n\n" + QString(keyboardB[i]));
        but->setStatusTip("Нажмите Shift+" + QString(keyboardB[i]));
        //but->setToolTip("Для воспроизведения нажмите на клавишу");
        but->raise();
        connect(but, SIGNAL(clicked()), this, SLOT(on_but_clicked()));
        buttonsB.insert(keyboardB[i], but);
    }
}

void MainWindow::on_open_triggered()
{
    if(!window)
        openTextEdit();
    if(ui->textEdit->toPlainText() != "" &&  text != ui->textEdit->toPlainText())
    {
        int n = QMessageBox::question(this, "Сохранение", "Товарищ, вы хотите сохранить данные?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
        if (n == QMessageBox::Yes)
        {
            on_save_triggered();
        }
    }
    QString FullFileName = QFileDialog::getOpenFileName(this, "title", "", "Text file (*.txt);;All file (*.*)");
    QFile file(FullFileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Ошибка №1", "Файл не был открыт");
        return;
    }
    QString text = file.readAll().constData();
    ui->textEdit->setPlainText(text);
    this->text = text;
    file.close();
    QString FileName = QFileInfo(FullFileName).fileName();
    this->setWindowTitle(FileName);
}
void MainWindow::on_save_triggered()
{
    if(text == ui->textEdit->toPlainText() || ui->textEdit->toPlainText() == "" || !window)
    {
        QMessageBox::information(this, "Ошибка №3", "Нечего сохранять :)");
        return;
    }
    QString FullFileName = QFileDialog::getSaveFileName(this, "title", "", "Text file (*.txt);;All file (*.*)");
    if(FullFileName == "")
    {
        QMessageBox::warning(this, "Ошибка №2", "Неверное имя файла");
        return;
    }
    QFile file(FullFileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Ошибка №1", "Файл не был открыт или не существует");
        return;
    }
    QTextStream stream(&file);
    stream << ui->textEdit->toPlainText();
    stream.flush();
    text = ui->textEdit->toPlainText();
    file.close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ui->textEdit->toPlainText() == "" || text == ui->textEdit->toPlainText())
    {
        event->accept();
        return;
    }
    int n = QMessageBox::question(this, "Выход", "Товарищ, вы хотите сохранить данные перед выходом?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);
    switch (n)
    {
    case QMessageBox::Yes:
        //event->ignore(); //окно не закроется
        on_save_triggered();
        //this->close();
        event->accept();
        break;
    case QMessageBox::No:
        event->accept(); //окно закроется
        break;
    case QMessageBox::Cancel:
        event->ignore(); //окно не закроется
        break;
    }
}
void MainWindow::on_close_triggered()
{
    if(!window)
    {
        QMessageBox::warning(this, "Ошибка №4", "Нотный стан не открыт");
    }
    if(window)
    {
        if(text != ui->textEdit->toPlainText())
        {
            int n = QMessageBox::question(this, "Сохранение", "Товарищ, вы хотите сохранить данные перед выходом?", QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
            if(n == QMessageBox::Yes)
                on_save_triggered();
        }
        this->setFixedSize(1418, 353);
        QMap<int, QPushButton*>::const_iterator it;
        for(it = buttonsB.constBegin(); it != buttonsB.constEnd(); ++it)
        {
            it.value()->setGeometry(QRect(it.value()->geometry().x(),0, 20, 191));
        }
        for(it = buttonsW.constBegin(); it != buttonsW.constEnd(); ++it)
        {
            it.value()->setGeometry(QRect(it.value()->geometry().x(),0, 40, 300));
        }
        ui->textEdit->setFixedSize(0,0);
        ui->textEdit->clear();
        window = false;
        record = false;
    }
}
void MainWindow::openTextEdit()
{
    if(!window)
    {
        this->setFixedSize(1418, 503);
        QMap<int, QPushButton*>::const_iterator it;
        for(it = buttonsB.constBegin(); it != buttonsB.constEnd(); ++it)
        {
            it.value()->setGeometry(QRect(it.value()->geometry().x(),150, 20, 191));
        }
        for(it = buttonsW.constBegin(); it != buttonsW.constEnd(); ++it)
        {
            it.value()->setGeometry(QRect(it.value()->geometry().x(),150, 40, 300));
        }
        ui->textEdit->setFixedSize(741,141);
        window = true;
    }
}

void MainWindow::on_beginRecord_triggered()
{
    if(record)
    {
        QMessageBox::warning(this, "Ошибка №5", "Запись уже начата");
        return;
    }
    if(!window)
        openTextEdit();
    record = true;
}
void MainWindow::on_stopRecord_triggered()
{
    if(!record)
    {
        QMessageBox::warning(this, "Ошибка №6", "Запись не начата");
        return;
    }
    record = false;
}

void MainWindow::on_about_triggered()
{
    QMessageBox::information(this, "О программе", "Synthesizer v. 1.01\nАвтор Кыльчик Иван Викторович\nСделано для практической работы\n2016 г");
}
void MainWindow::on_help_triggered()
{
    QMessageBox::information(this, "Справка", "Для игры на фортепиано воспользуйтесь мышью или соответствующими клавишами на клавиатуре\
                                               Для игры черными клавишами зажмите клавишу Shift");
}

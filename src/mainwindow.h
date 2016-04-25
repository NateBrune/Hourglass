#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"
#include "avgthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyThread *mThread;
    AvgThread *aThread;
    unsigned long long hashseconds = 1; // hashes per second

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_3_clicked();

    void on_stop_button_clicked();

    void on_avgBUtton_clicked();

public slots:
    void onValueChanged(int);
    void onStatusChanged(QString);
    void onSecondsChanged(QString);
    void onavgValue(unsigned long long);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "mythread.h"
#include <QFileDialog>
#include <QTextStream>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include "big_number.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aThread = new AvgThread(this);
    connect(aThread, SIGNAL(avgValue(unsigned long long)), this, SLOT(onavgValue(unsigned long long)));
    aThread->hashes=1000000;
    aThread->seed=ui->lineEdit_2->text();
    aThread->start();

    //connect(sender, SIGNAL (progressChanged(int percent)), receiver, SLOT, (updateProgress(int percent)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSecondsChanged(QString sec){
    ui->remaining->setText(sec);
}

void MainWindow::onValueChanged(int count){
    ui->progressBar->setValue(count);
}

void MainWindow::onStatusChanged(QString status){
    ui->lineEdit_2->setText(status);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->Hash_label->setText( QString::number(value) + " Hashes"); // Hash Number Label
    if(hashseconds!=1){
        unsigned long long tSeconds = (value)/hashseconds;
        unsigned long long seconds = tSeconds%60;
        unsigned long long tMinutes = tSeconds / 60;
        unsigned long long minutes = tMinutes % 60;
        unsigned long long hours = tMinutes / 60;
        ui->calculated_seconds->setText(QString::number(seconds)+ "s " + QString::number(minutes) + "m " + QString::number(hours) + "h");
        //qDebug() << tSeconds << " tSeconds" << seconds << " seconds";
    }


}


void MainWindow::on_pushButton_2_clicked()   //Encrypt Button
{
    mThread = new MyThread(this);
    connect(mThread, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(mThread, SIGNAL(statusChanged(QString)), this, SLOT(onStatusChanged(QString)));
    connect(mThread, SIGNAL(secondsChanged(QString)), this, SLOT(onSecondsChanged(QString)));
    mThread->Encrypt=true;
    mThread->filename=ui->lineEdit->text();
    mThread->hashes=ui->horizontalSlider->value();
    mThread->seed=ui->lineEdit_2->text();
    mThread->start();
}

void MainWindow::on_pushButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),QCoreApplication::applicationDirPath());
    ui->lineEdit->setText(fileNames.first());
}

void MainWindow::on_pushButton_3_clicked() //Decrypt Button
{
    mThread = new MyThread(this);
    connect(mThread, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(mThread, SIGNAL(statusChanged(QString)), this, SLOT(onStatusChanged(QString)));
    connect(mThread, SIGNAL(secondsChanged(QString)), this, SLOT(onSecondsChanged(QString)));
    mThread->Encrypt=false;
    mThread->filename=ui->lineEdit->text();
    QString fileName = ui->lineEdit->text();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        ui->lineEdit_2->setText("Failed to open file.");
        qDebug() << "Failed to open file...";
        return;
    }
    QTextStream in(&file);
    QString fileContentAll = in.readAll();
    QStringList pieces = fileContentAll.split( ":" );
    QString numHashes = pieces.value(1);

    mThread->hashes=numHashes.toInt();
    QString numSeed = pieces.value(2);
    mThread->seed=numSeed;
    qDebug() << numHashes << " " << numSeed;
    mThread->start();

}

void MainWindow::on_stop_button_clicked()
{
    mThread->Stop=true;
    mThread->quit();
}

void MainWindow::onavgValue(unsigned long long value){
    hashseconds = value;
}
void MainWindow::on_avgBUtton_clicked(){}


// Hash
/*
QString fileName = ui->lineEdit->text();
QFile file(fileName);
if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    return;

QTextStream in(&file);
QString fileContent = in.readAll();
QString seed = ui->lineEdit_2->text();
QString hash = seed;
for(int i = 0; i<ui->horizontalSlider->value(); i++){
    hash = QString(QCryptographicHash::hash((hash.toStdString().c_str()),QCryptographicHash::Sha3_512).toHex());
    //blah = QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Md5).toHex())
}
ui->lineEdit_2->setText(hash);
*/

// Read file
/*
QString fileName = ui->lineEdit->text();
QFile file(fileName);
if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    return;

QTextStream in(&file);
QString fileContent = in.readAll();
ui->lineEdit->setText(fileContent);
*/

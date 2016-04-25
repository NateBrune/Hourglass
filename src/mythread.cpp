#include "mythread.h"
#include <QDebug>
#include <QMutex>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QTime>
#include <assert.h>
#include <QFile>
#include <QTextStream>
#include <simplecrypt.h>

MyThread::MyThread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
}

// run() will be called when a thread starts
void MyThread::run()
{
    QString seed = this->seed;
    QString hash = seed;
    int currentValue = 0;
    unsigned long int miliseconds = 0;
    QTime myTimer;
    emit statusChanged("Hashing...");
    myTimer.start();
    for(unsigned long long int i = 0; i<hashes; i++){
        QMutex mutex;
        // prevent other threads from changing the "Stop" value
        mutex.lock();
        if(this->Stop){
            emit valueChanged(0);
            emit statusChanged("");
            emit secondsChanged("0 Seconds");
            mutex.unlock();
            break;
        }
        mutex.unlock();
        hash = QString(QCryptographicHash::hash((hash.toStdString().c_str()),QCryptographicHash::Sha3_512).toHex());
        //blah = QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Md5).toHex())
        if(((i)%(hashes/100))==0){
            currentValue+=1;
            emit valueChanged(currentValue);
        }
        //qDebug() << QString::number(i) << " " << hash;
        if((i%100000)==0 && i>1){
            miliseconds = myTimer.elapsed();
            myTimer.restart();
            assert(miliseconds>0);
            //qDebug() << QString::number(100000) + "/" + QString::number(miliseconds) + "=" + QString::number((100000)/(miliseconds));
            unsigned long long khpm = (100000)/(miliseconds); //hashes per milisecond
            unsigned long long hps = khpm*1000; // hashes per second
            unsigned long int hashesremaining = hashes-i;
            unsigned long int tSeconds = hashesremaining/hps;
            unsigned long long seconds = tSeconds%60;
            unsigned long long tMinutes = tSeconds / 60;
            unsigned long long minutes = tMinutes % 60;
            unsigned long long hours = tMinutes / 60;
            //QString status = seconds;
            qDebug() << tSeconds << " tSeconds" << seconds << " seconds";
            //ui->calculated_seconds->setText(QString::number(seconds)+ "s " + QString::number(minutes) + "m " + QString::number(hours) + "h");
            emit secondsChanged(QString::number(seconds)+ "s " + QString::number(minutes) + "m " + QString::number(hours) + "h");
        }
    }
    emit valueChanged(0);
    emit statusChanged("Reading File...");
    QString fileName = this->filename;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&file);
    emit valueChanged(5);
    QString result;
    QString fileContent = in.readAll();
    in.flush();
    file.flush();
    file.close();

    emit valueChanged(15);
    bool ok;
    if(this->Encrypt){
        qDebug() << fileContent << " 1";
        fileContent = fileContent.split( ":" ).value(0);
        qDebug() << fileContent << " 2";
        emit statusChanged("Encrypting...");
        msleep(1000);
        SimpleCrypt crypto(hash.left(4).toUInt(&ok, 16));
        result = crypto.encryptToString(fileContent);
        result.append(":" + QString::number(this->hashes) + ":" + this->seed);
    }
    else{
        qDebug() << fileContent << " 1";
        fileContent = fileContent.split( ":" ).value(0);
        qDebug() << fileContent << " 2";

        emit statusChanged("decrypting...");
        msleep(1000);
        SimpleCrypt crypto(hash.left(4).toUInt(&ok, 16));
        result = crypto.decryptToString(fileContent);
    }
    QMutex mutex;
    valueChanged(90);
    for(int i = 5; i>0; i--){
        mutex.lock();
        if(this->Stop){
            emit valueChanged(0);
            emit statusChanged("");
            emit secondsChanged("0 Seconds");
            mutex.unlock();
            break;
        }
        mutex.unlock();
        QString str = "Writing to file in ";
        str.append(QString::number(i));
        str.append(".");
        emit statusChanged(str);
        msleep(333);
        str.append(".");
        emit statusChanged(str);
        msleep(333);
        str.append(".");
        emit statusChanged(str);
        msleep(333);
        emit valueChanged(100-((i*2)-2));
    }
    mutex.lock();
    if(this->Stop){
        emit valueChanged(0);
        emit statusChanged("");
        emit secondsChanged("0 Seconds");
        mutex.unlock();
        return;
    }
    mutex.unlock();
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        return;
    in << result;
    emit valueChanged(100);
    emit statusChanged("Done.");
    file.flush();
    file.close();
    return;
}
/*
if(((i)%(hashes/100))==0){
    currentValue+=1;
    emit valueChanged(currentValue);
}
if(((i)%100000)==0){
    unsigned long int hps = (10000*1000)/miliseconds*1000; //hashes per second
    unsigned long int hashesremaining = hashes-i;
    unsigned long int secondsremaining = hashesremaining/hps;
    emit statusChanged(QString::number(secondsremaining) + " Seconds Remaining");
}
if((i%10000)==0){
    miliseconds  = myTimer.elapsed();
    myTimer.restart();
}

     if(((i)%(hashes/100))==0){
            currentValue+=1;
            emit valueChanged(currentValue);
        }
        if(((i)%100)==0){
            unsigned long int remaining = (hashes-i)%(nMilliseconds*1000)
            emit statusChanged(QString::number(remaining));
        }
        if((i%1000)==0){
            nMilliseconds = myTimer.elapsed();
            myTimer.stop();
        }
        */

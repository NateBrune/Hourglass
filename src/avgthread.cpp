#include "avgthread.h"
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

AvgThread::AvgThread(QObject *parent, bool b) :
    QThread(parent), Stop(b){}

void AvgThread::run()
{
    QString seed = this->seed;
    QString hash = seed;
    int currentValue = 0;
    unsigned long int miliseconds = 0;
    QTime myTimer;
    myTimer.start();
    for(unsigned long long int i = 0; i<=hashes; i++){
        QMutex mutex;
        mutex.lock();
        if(this->Stop){
            mutex.unlock();
            break;
        }
        mutex.unlock();
        hash = QString(QCryptographicHash::hash((hash.toStdString().c_str()),QCryptographicHash::Sha3_512).toHex());
        if(((i)%(hashes/100))==0){
            currentValue+=1;
        }
        if((i%1000000)==0 && i>1){
            miliseconds = myTimer.elapsed();
            myTimer.restart();
            assert(miliseconds>0);
            //qDebug() << QString::number(100000) + "/" + QString::number(miliseconds) + "=" + QString::number((100000)/(miliseconds));
            unsigned long long khpm = (1000000)/(miliseconds); //hashes per milisecond
            unsigned long long hps = khpm*1000; // hashes per second
            emit avgValue(hps);
        }
    }

}

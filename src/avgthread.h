#ifndef AVGTHREAD_H
#define AVGTHREAD_H

#include <QThread>

class AvgThread : public QThread
{
    Q_OBJECT
public:
    explicit AvgThread(QObject *parent = 0, bool b = false);
    void run();

    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool Stop;
    unsigned long long int hashes;
    QString seed;

signals:
    // To communicate with Gui Thread
    // we need to emit a signal
    void avgValue(unsigned long long);

public slots:

};

#endif // AVGTHREAD_H

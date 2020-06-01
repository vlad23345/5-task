#ifndef LONGPROCESS_H
#define LONGPROCESS_H

#include <QObject>

class LongProcess : public QObject
{
    Q_OBJECT
public:
    LongProcess(int n);
signals:
    void send(int,int);
    void finished(int);
public slots:
    void doWork();
private:
    int n;
};

#endif // LONGPROCESS_H

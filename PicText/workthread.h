#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QImage>
#include <mainwindow.h>

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread();
    void work(QImage ima);
signals:
    void setRange(int minimum, int maximum);
    void setValue(int value);
    void setButtonEnabled(bool enable);
private:
    QImage image;
protected:
    void run();
};

#endif // WORKTHREAD_H

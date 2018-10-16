#include "workthread.h"
#include "textpic.h"

WorkThread::WorkThread()
{
    
}

void WorkThread::work(QImage ima)
{
    image = ima;
    start();
}

void WorkThread::run()
{
    TextPic test(image);
    QObject::connect(&test, &TextPic::setRange, [this](int minimum, int maximum){emit this->setRange(minimum, maximum);});
    QObject::connect(&test, &TextPic::setValue, [this](int value){emit this->setValue(value);});
    QObject::connect(&test, &TextPic::setButtonEnabled, [this](bool enable){emit this->setButtonEnabled(enable);});
    test.toString();
}

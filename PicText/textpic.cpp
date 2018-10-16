#include "textpic.h"
#include <QDebug>
#include <QFile>

QString TextPic::greyLevelString  = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

TextPic::TextPic(QImage picture) :
    image(picture)
{

}

void TextPic::toString()
{
    emit setButtonEnabled(false);
    //mainWindow->setSelectEnable(false);
    QString text = "";
    QSize imageSize = image.size();
    int imageWidth = imageSize.width();
    int imageHeight = imageSize.height();
    unsigned char *picData = image.bits();
    //mainWindow->setProgressBarRange(0, imageHeight - 1);
    emit setRange(0, imageHeight - 1);
    for(int i  = 0; i < imageHeight; i++)
    {
        for(int j = 0; j < imageWidth; j++)
        {
            text = text + getGreyLevelChar(static_cast<int>(*picData), static_cast<int>(*(picData + 1)), static_cast<int>(*(picData + 2)));
            picData += 4;
        }
        text += "\r\n";
        emit setValue(i);
        //mainWindow->setProgressBarValue(i);
    }
    //qDebug() << imageHeight << imageWidth << text.length();
    //int temp = 0;
    QString t = "";
    //QChar *it = text.data();
    QFile data("file.txt");
    data.open(QIODevice::WriteOnly);
    QTextStream out(&data);
    /*for(int i = 0; i < text.length(); i++)
    {
        if(i != 0)
            it++;
        temp++;
        if(temp <= imageWidth + 2)
            t = t + (*it);
            //t = t + text.at(i);
        else
        {
            out << t;
            //qDebug() << t << t.length();
            if(i != text.length() - 1)
                t = *it;
            //t = text.at(i);
            temp = 1;
        }
    }*/
    out << text;
    data.close();
    //mainWindow->setSelectEnable(true);
    emit setButtonEnabled(true);
}

QChar TextPic::getGreyLevelChar(int r, int g, int b)
{
    int greyLevel = ((static_cast<quint32>((r << 5) + (r << 2) + (r << 1)))+ static_cast<quint32>((g << 6) + (g << 3) + (g << 1) + g) + static_cast<quint32>((b << 4) - b)) >> 7;
    int length = greyLevelString.length();
    double unit = 256.00 / static_cast<double>(length);
    int pos = static_cast<int>(greyLevel / unit);
    if(pos >= length)
        pos = length - 1;
    /*if(greyLevel > 230)
        pos = length - 1;*/
    return greyLevelString.at(pos);
}

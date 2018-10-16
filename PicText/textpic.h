#ifndef TEXTPIC_H
#define TEXTPIC_H

#include <QImage>
#include <QString>
#include <QSize>
#include <QChar>

class TextPic : public QObject
{
    Q_OBJECT
public:
    TextPic() = delete;
    TextPic(QImage picture);
    void toString();
signals:
    void setRange(int minimum, int maximum);
    void setValue(int value);
    void setButtonEnabled(bool enable);
private:
    QImage image;
    //the definition of "imageSize" must be put in the behind of the definition of "image"
    QString text;
    static QChar getGreyLevelChar(int r, int g, int b);
    static QString greyLevelString;
};

#endif // TEXTPIC_H

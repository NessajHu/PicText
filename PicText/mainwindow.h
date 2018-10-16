#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QImage>
#include <QString>
#include <QLabel>
#include <QProgressBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSelectEnable(bool enable);
    void setProgressBarRange(int minimum, int maximum);
    void setProgressBarValue(int values);
private slots:
    void select();
private:
    QPushButton *selectPicture;
    QImage image;
    QString imageName;
    QLabel *imageLabel;
    QLabel *explainLabel;
    QProgressBar *progressBar;
};

#endif // MAINWINDOW_H

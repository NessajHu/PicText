#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include "textpic.h"
#include "workthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      selectPicture(new QPushButton(this)),
      imageLabel(new QLabel(this)),
      explainLabel(new QLabel(this)),
      progressBar(new QProgressBar(this))
{
    setWindowTitle("PicToText");
    QString explainText = "This app will new-built a \"file.txt\" in the current directory.\r\n";
    explainText += "I suggest not to put picture with too big size.\r\n";
    explainText += "The suggested biggest size is 500*500\r\n";
    explainText += "The suffix we support is png, bmp, jpg, jpeg\r\n";
    explainText += "You had better use monospaced font";
    setFixedSize(600, 650);
    imageLabel->setGeometry(0, 70, 600, 530);
    explainLabel->setGeometry(100, 0, 500, 70);
    explainLabel->setText(explainText);
    //imageLabel->setScaledContents(true);
    selectPicture->setGeometry(0, 0, 100, 70);
    selectPicture->setText("Select");
    progressBar->setGeometry(0, 600, 600, 50);
    progressBar->setTextVisible(false);
    connect(selectPicture, &QPushButton::clicked, this, &MainWindow::select);

}

void MainWindow::select()
{
    imageName = "";
    imageName = QFileDialog::getOpenFileName(this,
        tr("Select Picture"),
        "",
        tr("Images (*.png *.bmp *.jpg *.jpeg)"));
    //imageName = "D:/f636afc379310a55a12f0d2eb54543a9832610e4.jpg";
    if(imageName == "")
        return;
    else
    {
        if(!(image.load(imageName)))
        {
            QMessageBox::information(this, "Open Failed", "Open Failed");
            return;
        }
    }
    imageLabel->setPixmap(QPixmap::fromImage(image));
    //imageLabel ->setText(TextPic::toString(image));
    WorkThread *workThread = new WorkThread;
    QObject::connect(workThread, &WorkThread::finished, workThread, &WorkThread::deleteLater);
    QObject::connect(workThread, &WorkThread::setRange, progressBar, &QProgressBar::setRange, Qt::QueuedConnection);
    QObject::connect(workThread, &WorkThread::setValue, progressBar, &QProgressBar::setValue, Qt::QueuedConnection);
    QObject::connect(workThread, &WorkThread::setButtonEnabled, selectPicture, &QPushButton::setEnabled, Qt::QueuedConnection);
    workThread->work(image);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setSelectEnable(bool enable)
{
    selectPicture->setEnabled(enable);
}

void MainWindow::setProgressBarRange(int minimum, int maximum)
{
    progressBar->setRange(minimum, maximum);
}

void MainWindow::setProgressBarValue(int value)
{
    progressBar->setValue(value);
}

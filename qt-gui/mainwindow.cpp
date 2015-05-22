#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <QUrl>
qint64 frametimeBuffer[100];
int count =0;
qint64 prev =0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    glwidget = new Widget(this);
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateMe()));
        timer->start(0);

    ui->verticalLayout1->addWidget(glwidget);
        startTimer(10);
        ui->webView->setUrl(QUrl("http://www.google.com/"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateMe()
{
  //qDebug("%llu wut",QDateTime::currentMSecsSinceEpoch());
}

void MainWindow::timerEvent(QTimerEvent *event)
{


   qDebug("%llu before",QDateTime::currentMSecsSinceEpoch());
    glwidget->update();
    qDebug("%llu after",QDateTime::currentMSecsSinceEpoch());
    qDebug("%llu prev",prev);
    qDebug("%llu current", QDateTime::currentMSecsSinceEpoch());
    qDebug("%llu delta", QDateTime::currentMSecsSinceEpoch()-prev);
    frametimeBuffer[count]=QDateTime::currentMSecsSinceEpoch()-prev;
    qint64 sum =0;
    for(int i=0;i<100;i++)
    {
        sum+=frametimeBuffer[i];
    }
    qDebug("sum: %llu", sum);
    prev = QDateTime::currentMSecsSinceEpoch();
    count =(count+1) % 100;

}

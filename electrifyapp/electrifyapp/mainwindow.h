#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "symmetryglwidget.h"

#include "globals.h"
#include "opc_client.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     unique_ptr<SymmetryGLWidget> glwidget;
     unique_ptr<Engine> engine;
     unique_ptr<Output> output;
     unique_ptr<Output> output2;
     unique_ptr<OPCClient> opc;
     std::vector<uint8_t> frameBuffer= {0};
     int modelsize;

protected:

    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

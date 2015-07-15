#ifndef DESIGNERWINDOW_H
#define DESIGNERWINDOW_H

#include <QMainWindow>

#include "globals.h"
#include "output.h"
#include "engine.h"

namespace Ui {
class DesignerWindow;
}

class DesignerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DesignerWindow(QWidget *parent = 0);
    ~DesignerWindow();

    unique_ptr<Engine> engine;
    unique_ptr<Output> output;

private:
    Ui::DesignerWindow *ui;
};

#endif // DESIGNERWINDOW_H

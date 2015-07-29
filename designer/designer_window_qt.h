#ifndef DESIGNERWINDOWQT_H
#define DESIGNERWINDOWQT_H

#include "globals.h"

#include "output.h"
#include "engine.h"
#include "engine_ui.h"

#include <QMainWindow>

namespace Ui {
class DesignerWindowQt;
}

class DesignerWindowQt : public QMainWindow
{
  Q_OBJECT

public:
  explicit DesignerWindowQt(QWidget *parent = 0);
  ~DesignerWindowQt();

  unique_ptr<Engine> engine;
  unique_ptr<EngineUi> engineUi;
  unique_ptr<Output> output;

private:
  Ui::DesignerWindowQt *ui;
};

#endif // DESIGNERWINDOWQT_H

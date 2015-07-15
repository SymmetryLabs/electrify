#include "designer_window_qt.h"
#include "ui_designerwindow.h"

#include <iostream>

#include "color.h"
#include "constant_color_component.h"
#include "color_doubler.h"
#include "signal.h"
#include "pixel.h"
#include "group.h"
#include "frame_context.h"
#include "square_wave.h"
#include "incrementer.h"
#include "engine.h"
#include "loader.h"
#include "compound_component.h"
#include "blueprint.h"
#include "hsv_component.h"
#include "saw_wave.h"
#include "constant_component.h"
#include "perlin_noise_component.h"
#include "time_component.h"
#include "scale_transform.h"

DesignerWindow::DesignerWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DesignerWindowQt)
{
  ui->setupUi(this);

  auto blueprint = make_unique<Blueprint>();

  /* file loading */
  Loader loader = Loader();
  unique_ptr<Model> model = loader.loadJSON("data/cubesExport2.json");
  qDebug() << "file loaded";

  output = make_unique<Output>();
  for (auto pixel : model->pixels) {
    output->colorBuffer.push_back(Color(0xFFFFFFFF));
  }

  OutputSimulationWidget* osWidget = findChild<OutputSimulationWidget*>("outputSimulationWidget");
  osWidget->setModel(model.get());
  osWidget->setOutput(output.get());


  auto compound = blueprint->makeSubcomponent<CompoundComponent>();
  compound->registerWirableOutput<Color>("color");

  auto constantColor = compound->makeSubcomponent<ConstantColorComponent>();
  auto incrementer = compound->makeSubcomponent<Incrementer>();

  compound->wireSubcomponents(*constantColor, "output", *incrementer, "color");
  compound->wireOutput("color", *incrementer, "output");


  auto compound2 = blueprint->makeSubcomponent<CompoundComponent>();
  compound2->registerWirableOutput<Color>("color");

  auto hsvComponent = compound2->makeSubcomponent<HsvComponent>();
  auto sawWaveComponent = compound2->makeSubcomponent<SawWave>();
  auto timeComponent = compound2->makeSubcomponent<TimeComponent>();
  auto scaleTransform = compound2->makeSubcomponent<ScaleTransform>();
  auto multiplyAmountComponent = compound2->makeSubcomponent<ConstantComponent<float>>(1.0 / 10);
  auto perlinNoiseComponent = compound2->makeSubcomponent<PerlinNoiseComponent>();
  auto frequency = compound2->makeSubcomponent<ConstantComponent<float>>(1.0 / 10);

  compound->wireSubcomponents(*frequency, "output", *sawWaveComponent, "frequency");
  compound->wireSubcomponents(*multiplyAmountComponent, "output", *scaleTransform, "multiplier");
  compound->wireSubcomponents(*timeComponent, "output", *scaleTransform, "input");
  compound->wireSubcomponents(*scaleTransform, "output", *perlinNoiseComponent, "zInput");
  compound->wireSubcomponents(*perlinNoiseComponent, "output", *hsvComponent, "hue");

  compound2->wireOutput("color", *hsvComponent, "output");

  blueprint->wireOutput("color", *compound2, "color");

  engine = make_unique<Engine>(std::move(blueprint), std::move(model));
  // engine->setProfilerEnabled(true);
  osWidget->engine = engine.get();
  engine->start();
}

DesignerWindow::~DesignerWindow()
{
  delete ui;
  engine->stopAndWait();
}

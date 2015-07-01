#include "mainwindow.h"
#include "ui_mainwindow.h"

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    glwidget = make_unique<SymmetryGLWidget>(this);
    ui->setupUi(this);

     string color("color"); //same name for I and O

     auto blueprint = make_unique<Blueprint>();

     /* file loading */
      qDebug() << "trying to load json file\n";
      Loader loader = Loader();
      string filename("data/cubesExport2.json");
      qDebug() << "file loaded\n";


     unique_ptr<Model> model = loader.loadJSON(filename);

    qDebug() << "model pixels size:" << model->pixels.size();

      output = make_unique<Output>();
      for(auto pixel : model->pixels)
      {
            output->colorBuffer.push_back(Color(0xFFFFFFFF));
      }

        glwidget->setModel(model.get());
        glwidget->setOutput(output.get());


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

    qDebug() << "Is blueprint fully wired:" << blueprint->isFullyWired();

    engine = make_unique<Engine>(std::move(blueprint), std::move(model));
    glwidget->engine = engine.get();
    engine->start();

    ui->verticalLayout->addWidget(glwidget.get());
    startTimer(16);
}

void MainWindow::timerEvent(__attribute__((unused)) QTimerEvent *event)
{
    glwidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
    engine->stopAndWait();
}

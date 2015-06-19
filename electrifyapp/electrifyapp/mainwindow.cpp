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


    auto compound = make_unique<CompoundComponent>();
    compound->registerWirableOutput<Color>("color");

    auto constantColor = make_unique<ConstantColorComponent>();
    auto incrementer = make_unique<Incrementer>();

    incrementer->wireInput("color", constantColor->getOutput<Color>("value"));
    compound->wireOutput("color", incrementer->getOutput<Color>("value"));

    compound->addSubcomponent(std::move(incrementer));
    compound->addSubcomponent(std::move(constantColor));


    auto compound2 = make_unique<CompoundComponent>();
    compound2->registerWirableOutput<Color>("color");

    auto hsvComponent = make_unique<HsvComponent>();
    auto sawWaveComponent = make_unique<SawWave>();
    auto frequency = make_unique<ConstantComponent<double>>(1.0 / 10);

    sawWaveComponent->wireInput("frequency", frequency->getOutput<double>("value"));
    hsvComponent->wireInput("hue", sawWaveComponent->getOutput<Color>("value"));
    compound2->wireOutput("color", hsvComponent->getOutput<Color>("value"));

    compound2->addSubcomponent(std::move(frequency));
    compound2->addSubcomponent(std::move(sawWaveComponent));
    compound2->addSubcomponent(std::move(hsvComponent));

    blueprint->wireOutput("color", compound2->getOutput<Color>("color"));
    blueprint->addSubcomponent(std::move(compound));
    blueprint->addSubcomponent(std::move(compound2));

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

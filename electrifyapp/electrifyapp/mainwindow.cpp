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
#include "multiply_component.h"
#include <iostream>
#include <vector>
#include <unistd.h>

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

     unique_ptr<Model> model = loader.loadJSON(filename);
     qDebug() << "file loaded\n";

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

    incrementer->wireInput("color", constantColor->getOutput<Color>("primary"));
    compound->wireOutput("color", incrementer->getOutput<Color>("primary"));

    compound->addSubcomponent(std::move(incrementer));
    compound->addSubcomponent(std::move(constantColor));


    auto compound2 = make_unique<CompoundComponent>();
    compound2->registerWirableOutput<Color>("color");

    auto hsvComponent = make_unique<HsvComponent>();
    auto sawWaveComponent = make_unique<SawWave>();
    auto timeComponent = make_unique<TimeComponent>();
    auto multiplyComponent = make_unique<MultiplyComponent>();
    auto multiplyAmountComponent = make_unique<ConstantComponent<double>>(1.0 / 10);
    auto perlinNoiseComponent = make_unique<PerlinNoiseComponent>();
    auto frequency = make_unique<ConstantComponent<double>>(1.0 / 10);

    sawWaveComponent->wireInput("frequency", frequency->getOutput<double>("primary"));
    multiplyComponent->wireInput("multiplyAmount", multiplyAmountComponent->getOutput<double>("primary"));
    multiplyComponent->wireInput("signalInput", timeComponent->getOutput<double>("primary"));
    perlinNoiseComponent->wireInput("zInput", multiplyComponent->getOutput<double>("primary"));
    hsvComponent->wireInput("hue", perlinNoiseComponent->getOutput<Color>("primary"));
    compound2->wireOutput("color", hsvComponent->getOutput<Color>("primary"));

    compound2->addSubcomponent(std::move(frequency));
    compound2->addSubcomponent(std::move(sawWaveComponent));
    compound2->addSubcomponent(std::move(timeComponent));
    compound2->addSubcomponent(std::move(multiplyComponent));
    compound2->addSubcomponent(std::move(multiplyAmountComponent));
    compound2->addSubcomponent(std::move(perlinNoiseComponent));
    compound2->addSubcomponent(std::move(hsvComponent));

    blueprint->wireOutput("color", compound2->getOutput<Color>("color"));
    blueprint->addSubcomponent(std::move(compound));
    blueprint->addSubcomponent(std::move(compound2));

    qDebug() << "Is blueprint fully wired:" << blueprint->isFullyWired();
    modelsize = model->pixels.size();
    engine = make_unique<Engine>(std::move(blueprint), std::move(model));
    glwidget->engine = engine.get();
    engine->start();

    ui->verticalLayout->addWidget(glwidget.get());

     opc = make_unique<OPCClient>();
     frameBuffer.resize(sizeof(OPCClient::Header) + modelsize*3);
     opc->resolve("10.200.1.44", 7890);
    startTimer(32);
}

void MainWindow::timerEvent(__attribute__((unused)) QTimerEvent *event)
{

    if(opc->tryConnect())
    {
        engine->copyColorBuffer(output->colorBuffer);
        std::vector<uint8_t>::iterator it = frameBuffer.begin();
        it += sizeof(OPCClient::Header);
            for(auto c: output->colorBuffer)
            {
                *(it++) = (c.asRGBA() >> 16) & 255;
                *(it++) = (c.asRGBA() >> 24) & 255;
                *(it++) =(c.asRGBA() >> 8) & 255;
                if(it == frameBuffer.end() ) {break;};
            }
        OPCClient::Header::view(frameBuffer).init(0, opc->SET_PIXEL_COLORS, modelsize*3);
        bool res = opc->write(frameBuffer);
    }
    glwidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
    engine->stopAndWait();
}

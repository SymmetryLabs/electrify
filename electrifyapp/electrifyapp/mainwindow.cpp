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
    glwidget = unique_ptr<SymmetryGLWidget> {new SymmetryGLWidget(this)};
    ui->setupUi(this);

     string color("color"); //same name for I and O

     unique_ptr<Blueprint> blueprint {new Blueprint()};

     /* file loading */
      qDebug() << "trying to load json file\n";
      Loader loader = Loader();
      string filename("data/cubesExport2.json");
      qDebug() << "file loaded\n";


     unique_ptr<Model> model = loader.loadJSON(filename);

    qDebug() << "model pixels size:" << model->pixels.size();

      output = unique_ptr<Output> {new Output()};
      for(auto pixel : model->pixels)
      {
            output->colorBuffer.push_back(Color(0xFFFFFFFF));
      }

        glwidget->setModel(model.get());
        glwidget->setOutput(output.get());



//         FrameContext f;
//         FragmentContext frag {Pixel()};

//         ConstantColorComponent c;
//         cout << c.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

//         ColorDoubler colorDoubler;
//         colorDoubler.wireInput("color", c.getOutput<Color>("color"));
//         cout << colorDoubler.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

//         SquareWave sq;

//         Signal<double> *ds = sq.getOutput<double>("value");

//         double d = ds->calculate(frag);
//         cout << d << endl;

//         frag.time = 0.8;

//         cout << sq.getOutput<double>("value")->calculate(frag) << endl;

//         Incrementer incr;
//         incr.wireInput("color", colorDoubler.getOutput<Color>("color"));
//         cout << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

//         incr.update(f);
//         cout << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;

//         incr.update(f);
//         cout << incr.getOutput<Color>("color")->calculate(frag).asRGBA() << endl;



//         auto compound = unique_ptr<CompoundComponent> {new CompoundComponent()};
//         auto comp = unique_ptr<ConstantColorComponent> {new ConstantColorComponent()};
//         compound->addSubcomponent(move(comp));
//         blueprint->outputSocket.signal = compound->getOutput<Color>("color");
//         blueprint->addSubcomponent(move(compound));

    unique_ptr<CompoundComponent> compound {new CompoundComponent()};
    compound->registerWirableOutput<Color>("color");

    unique_ptr<ConstantColorComponent> constantColor {new ConstantColorComponent()};
    unique_ptr<Incrementer> incrementer {new Incrementer()};

    incrementer->wireInput("color", constantColor->getOutput<Color>("value"));
    compound->wireOutput("color", incrementer->getOutput<Color>("value"));

    compound->addSubcomponent(std::move(incrementer));
    compound->addSubcomponent(std::move(constantColor));


    unique_ptr<CompoundComponent> compound2 {new CompoundComponent()};
    compound2->registerWirableOutput<Color>("color");

    unique_ptr<HsvComponent> hsvComponent {new HsvComponent()};
    unique_ptr<SawWave> sawWaveComponent {new SawWave()};
    unique_ptr<ConstantComponent<double>> frequency {new ConstantComponent<double>(1.0 / 10)};

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

    engine = unique_ptr<Engine> {new Engine(std::move(blueprint), std::move(model))};
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

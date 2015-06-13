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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    glwidget = unique_ptr<SymmetryGLWidget> {new SymmetryGLWidget(this)};
    ui->setupUi(this);

     string color("color"); //same name for I and O

     unique_ptr<Blueprint> blueprint {new Blueprint()};
     unique_ptr<Model> model {new Model()};

    float edge = 2.0;
    float per_edge = 8.0;
    float step = edge/per_edge;

   for(int i=0; i<per_edge;i++)
   {
       for(int j=0; j<per_edge; j++)
       {
           for(int k=0; k<per_edge; k++)
           {
            model->pixels.push_back(Pixel(step*j, step*i, step*k));
           }
       }
   }
    qDebug() << "model pixels size:" << model->pixels.size();

      output = unique_ptr<Output> {new Output()};
      for(auto pixel : model->pixels)
      {

          unsigned long red = (unsigned long) ((pixel.x/edge)*255) << 24 & 0xFF000000;
          unsigned long green = (unsigned long) ((pixel.z/edge)*255) << 16 & 0xFF0000;
          unsigned long blue = (unsigned long) ((pixel.y/edge)*255) << 8 & 0xFF00;

           output->colorBuffer.push_back(Color(pixel.x + pixel.y + pixel.z < 0.1 ? 0xFFFFFFFF : red + green + blue + 255));
      }

        glwidget->setModel(model.get());
        glwidget->setOutput(output.get());


        /* file loading */
       //  cout << "trying to load file\n";
       //  Loader loader = Loader();
       //  string filename("data/dummydata.json");
       //  loader.loadJSON(filename);
       //  cout << "file loaded\n";

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

    incrementer->wireInput("color", constantColor->getOutput<Color>("color"));
    compound->wireOutput("color", incrementer->getOutput<Color>("color"));

    compound->addSubcomponent(std::move(incrementer));
    compound->addSubcomponent(std::move(constantColor));

    blueprint->wireOutput("color", compound->getOutput<Color>("color"));
    blueprint->addSubcomponent(std::move(compound));

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

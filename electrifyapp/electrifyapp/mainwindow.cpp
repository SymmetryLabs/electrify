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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    glwidget = new SymmetryGLWidget(this);
    ui->setupUi(this);

     string color("color"); //same name for I and O


    auto blueprint = make_shared<Blueprint>();
    auto model = make_shared<Model>();
    float edge = 2.0;
    float per_edge = 8.0;
    float step = edge/per_edge;

   for(int i=0; i<per_edge;i++)
   {
       for(int j=0; j<per_edge; j++)
       {
           for(int k=0; k<per_edge; k++)
           {
            model->pixels.push_back(make_shared<Pixel>(step*j, step*i, step*k));
           }
       }
   }
    qDebug() << "model pixels size:" << model->pixels.size();

    auto comp = make_shared<ConstantColorComponent>();
    blueprint->addComponent(comp);
    blueprint->outputSocket.signal = comp->getOutput<Color>(color);

      auto output = make_shared<Output>();
      for(auto pixel : model->pixels)
      {

          unsigned long red = (unsigned long) ((pixel->x/edge)*255) << 24 & 0xFF000000;
          unsigned long green = (unsigned long) ((pixel->z/edge)*255) << 16 & 0xFF0000;
          unsigned long blue = (unsigned long) ((pixel->y/edge)*255) << 8 & 0xFF00;

           output->colorBuffer.push_back(Color(pixel->x + pixel->y + pixel->z < 0.1 ? 0xFFFFFFFF : red + green + blue + 255));
      }

        glwidget->setModel(model);
        glwidget->setOutput(output);


    /* file loading */
      qDebug() << "trying to load file\n";
      Loader loader = Loader();
      //This path is relative to the working directory of the app
      string filename("../data/dummydata.json");
      loader.loadJSON(filename);
      qDebug() << "file loaded\n";

      FrameContext f;

      ConstantColorComponent c;

      qDebug() << c.getOutput<Color>(color)->calculate(f).asRGBA();
      ColorDoubler colorDoubler;
      colorDoubler.wireInput(color, c.getOutput<Color>(color));
      qDebug() << colorDoubler.getOutput<Color>(color)->calculate(f).asRGBA();

      SquareWave sq;
      string value("value");

      Signal<double> *ds = sq.getOutput<double>(value);

      double d = ds->calculate(f);
      qDebug() << d;

      f.time = 0.8;

      qDebug() << sq.getOutput<double>(value)->calculate(f);
      qDebug();

      Incrementer incr;
      incr.wireInput(color, colorDoubler.getOutput<Color>(color));
      qDebug() << incr.getOutput<Color>(color)->calculate(f).asRGBA();

      incr.update(f);
      qDebug() << incr.getOutput<Color>(color)->calculate(f).asRGBA();

      incr.update(f);
      qDebug() << incr.getOutput<Color>(color)->calculate(f).asRGBA();

      ui->verticalLayout->addWidget(glwidget);
      startTimer(16);
}

void MainWindow::timerEvent(__attribute__((unused)) QTimerEvent *event)
{
    glwidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

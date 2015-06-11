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
    model->pixels = {make_shared<Pixel>(0.0,0.0,0.0), make_shared<Pixel>(1.0,0.0,0.0), make_shared<Pixel>(1.0,1.0,0.0), make_shared<Pixel>(0.0,1.0,0.0) };
    qDebug() << "model pixels size:" << model->pixels.size();

    auto comp = make_shared<ConstantColorComponent>();
    blueprint->addComponent(comp);
    blueprint->outputSocket.input_signal = comp->getOutput<Color>(color);

      auto output = make_shared<Output>();
      for(auto pixel : model->pixels)
      {

          unsigned long int red = (((long int)pixel->x)*255) << 24;
          unsigned long int blue = (((long int) pixel->y)*255) << 8;
           output->colorBuffer.push_back(Color(pixel->x + pixel->y ==0.0 ? 0xFFFFFFFF :red+blue+255));
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

      FrameContext f = FrameContext();

      ConstantColorComponent c =  ConstantColorComponent();

      qDebug() << c.getOutput<Color>(color)->calculate_function(f).asRGBA();
      ColorDoubler colorDoubler = ColorDoubler();
      colorDoubler.wireInput<Color>(color, c.getOutput<Color>(color));
      qDebug() << colorDoubler.getOutput<Color>(color)->calculate_function(f).asRGBA();

      SquareWave sq = SquareWave();
      string value("value");

      Signal<double> *ds = sq.getOutput<double>(value);

      double d = ds->calculate_function(f);
      qDebug() << d;

      f.time = 0.8;

      qDebug() << sq.getOutput<double>(value)->calculate_function(f);
      qDebug();

      Incrementer incr = Incrementer();
      incr.wireInput<Color>(color, colorDoubler.getOutput<Color>(color));
      qDebug() << incr.getOutput<Color>(color)->calculate_function(f).asRGBA();

      incr.update(f);
      qDebug() << incr.getOutput<Color>(color)->calculate_function(f).asRGBA();

      incr.update(f);
      qDebug() << incr.getOutput<Color>(color)->calculate_function(f).asRGBA();

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

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
    ui->setupUi(this);
    /* file loading */
      cout << "trying to load file\n";
      Loader loader = Loader();
      //This is the path to the data dir from:
      //electrify/electrifyapp/build-electrifyapp-Desktop_Qt_5_4_1_clang_64bit-Debug/electrifyapp.app/Contents/MacOS
      //could be cleaner by setting PATH or something
      string filename("../data/dummydata.json");
      loader.loadJSON(filename);
      cout << "file loaded\n";

      FrameContext f = FrameContext();

      ConstantColorComponent c =  ConstantColorComponent();
      string color("color"); //same name for I and O
      cout << c.getOutput<Color>(color)->calculate_function(f).asRGBA();
      cout << '\n';
      ColorDoubler colorDoubler = ColorDoubler();
      colorDoubler.wireInput<Color>(color, c.getOutput<Color>(color));
      cout << colorDoubler.getOutput<Color>(color)->calculate_function(f).asRGBA();
      cout << '\n';

      SquareWave sq = SquareWave();
      string value("value");

      Signal<double> *ds = sq.getOutput<double>(value);

      double d = ds->calculate_function(f);
      cout << d;
      cout << '\n';

      f.time = 0.8;

      cout << sq.getOutput<double>(value)->calculate_function(f);
      cout << '\n';

      Incrementer incr = Incrementer();
      incr.wireInput<Color>(color, colorDoubler.getOutput<Color>(color));
      cout << incr.getOutput<Color>(color)->calculate_function(f).asRGBA();
      cout << '\n';

      incr.update(f);
      cout << incr.getOutput<Color>(color)->calculate_function(f).asRGBA();
      cout << '\n';

      incr.update(f);
      cout << incr.getOutput<Color>(color)->calculate_function(f).asRGBA();
      cout << '\n';

      auto blueprint = make_shared<Blueprint>();
      auto model = make_shared<Model>();
      model->pixels = {make_shared<Pixel>()};
      cout << model->pixels.size();

      auto comp = make_shared<ConstantColorComponent>();
      blueprint->addComponent(comp);
      blueprint->outputSocket.input_signal = comp->getOutput<Color>(color);

      //Engine e(blueprint, model);
      //e.outputs.push_back(make_shared<Output>());
      //e.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef SIGNAL_H
#define SIGNAL_H

class Signal
{
  public:
    void (*calculate_function)(Pixel *pixel, Group *topLevel /*, frameContext */);
};

#endif // SIGNAL_H
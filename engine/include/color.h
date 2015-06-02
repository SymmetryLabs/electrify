#ifndef COLOR_H
#define COLOR_H

class Color
{
  private:
    unsigned int _rgba;
  public: 
    void* asHSB(); //TODO pick a data format
    void* asHSL(); //TODO pick a data format
    void* asRGB(); //TODO pick a data format
    void fromHSB(double h, double s, double b);
    void fromHSL(double h, double s, double l);
    void fromRGB(double r, double g, double b);

};

#endif // COLOR_H
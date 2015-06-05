#pragma once

class Color
{
  private:
    unsigned int _rgba =0;
  public: 
  	int test =99;
    void* asHSB(); //TODO pick a data format
    void* asHSL(); //TODO pick a data format
    void* asRGB(); //TODO pick a data format
    void fromHSB(double h, double s, double b);
    void fromHSL(double h, double s, double l);
    void fromRGB(double r, double g, double b);

};


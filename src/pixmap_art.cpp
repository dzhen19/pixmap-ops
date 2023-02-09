#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   // todo: make at least one artwork!
   Image image;
   image.load("../images/earth.png");

   Image other;
   other.load("../images/shrek.png");

   // Image result = image.invert();
   // Image result = image.swirl(); 
   Image blend = image.alphaBlend(other, 0.5f);

   blend.save("test_earth.png");
   return 0;
}


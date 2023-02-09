#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char **argv)
{
   // todo: make at least one artwork!
   Image image;
   image.load("../images/earth.png");

   Image other;
   other.load("../images/flare.png");

   // Image result = image.rotate90();

   // Image blend = image.alphaBlend(other, 0.5f);
   Image blend = image.lightest(other);
   blend.save("test_earth.png");

   // result.save("flipped.png");
   return 0;
}

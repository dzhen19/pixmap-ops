#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char **argv)
{
   // todo: make at least one artwork!
   Image image;
   image.load("../images/earth.png");

   // Image other;
   // other.load("../images/flare.png");

   // Image blend = image.lightest(other);
   // blend.save("test_earth.png");

   // Pixel white = {(unsigned char)255,
   //                (unsigned char)255,
   //                (unsigned char)255};
   // image.fill(white);

   Image result = image.gaussian();
   result.save("test.png");
   return 0;
}

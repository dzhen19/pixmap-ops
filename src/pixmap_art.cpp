#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char **argv)
{
   // todo: make at least one artwork!
   Image image;
   image.load("../images/markiplier.png");

   // Image other;
   Image earth;
   earth.load("../images/earth.png");

   // Image blend = image.lightest(other);
   // blend.save("test_earth.png");

   // Pixel white = {(unsigned char)255,
   //                (unsigned char)255,
   //                (unsigned char)255};
   // image.fill(white);

   // Image result = image.gaussian();
   // Image resized = image.resize(400, 400);
   // Image result = resized.greenscreen(earth);
   Image result = earth.gaussian();
   result.save("test.png");
   return 0;
}

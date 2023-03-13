#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char **argv)
{
   Image shrek;
   shrek.load("../images/shrek.png");
   Image mark;
   mark.load("../images/markiplier.png");
   Image earth;
   earth.load("../images/earth.png");
   Image resized_mark = mark.resize(400, 400);
   resized_mark.save("resized_mark.png");
   resized_mark.greenscreen(earth).save("greenscreen.png");

   // Horizontal flip
   earth.flipHorizontal().save("flipped_horizontal.png");
   // Vertical flip
   earth.flipVertical().save("flipped_vertical.png");
   // Rotate 90 degrees
   earth.rotate90().save("rotate_90.png");
   // Swirl
   earth.swirl().save("swirl.png");
   // Invert
   earth.invert().save("invert.png");

   // Add
   earth.add(shrek).save("earth_add.png");
   // Subtract
   earth.subtract(shrek).save("earth_subtract.png");
   // Multiply
   earth.multiply(shrek).save("earth_multiply.png");
   // Difference
   earth.difference(shrek).save("earth_diff.png");
   // Lightest
   earth.lightest(shrek).save("earth_lightest.png");
   // Darkest
   earth.darkest(shrek).save("earth_darkest.png");

   Image tokyo;
   tokyo.load("../images/tokyo.png");
   Image result = tokyo.gaussian(7);
   result.save("gaussian.png");

   return 0;
}

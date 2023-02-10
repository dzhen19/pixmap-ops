#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char **argv)
{
   Image mark;
   mark.load("../images/markiplier.png");
   Image earth;
   earth.load("../images/earth.png");
   Image resized_mark = mark.resize(400, 400);
   resized_mark.greenscreen(earth);

   Image scenic;
   scenic.load("../images/scenic.png");
   Image result = scenic.gaussian();
   scenic.save("scenic_gaussian.png");

   return 0;
}

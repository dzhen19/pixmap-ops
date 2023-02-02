// Copyright 2021, Aline Normoyle, alinen

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace agl
{

   Image::Image()
   {
   }

   Image::Image(int width, int height)
   {
      image_width = width;
      image_height = height;
      original_channel_no = 3;
      image_data = new unsigned char [width * height * 3];
   }

   // copy constructor
   Image::Image(const Image &orig)
   {
      this->image_width = orig.image_width;
      this->image_height = orig.image_height;
      this->image_data = orig.image_data;
   }

   // assignment constructor
   Image &Image::operator=(const Image &orig)
   {
      if (&orig == this)
      {
         return *this;
      }

      this->image_width = orig.image_width;
      this->image_height = orig.image_height;
      this->image_data = orig.image_data;

      return *this;
   }

   Image::~Image()
   {
      delete[] image_data;
   }

   int Image::width() const
   {
      return image_width;
   }

   int Image::height() const
   {
      return image_height;
   }

   unsigned char *Image::data() const
   {
      return image_data;
   }

   // set entire image to another
   void Image::set(int width, int height, unsigned char *data)
   {
      image_width = width;
      image_height = width;
      image_data = data;
   }

   bool Image::load(const std::string &filename, bool flip)
   {
      image_data = stbi_load(filename.c_str(), &image_width, &image_height, &original_channel_no, 3);
      if (!image_data)
         return false;
      return true;
   }

   // todo make safe
   bool Image::save(const std::string &filename, bool flip) const
   {
      stbi_write_png(filename.c_str(), image_width, image_height, 3, image_data, 0);
      return true;
   }

   // todo make safe
   Pixel Image::get(int row, int col) const
   {
      int index = 3 * (row * image_width + col);
      return Pixel{image_data[index], image_data[index + 1], image_data[index + 2]};
   }

   // set one specific pixel
   void Image::set(int row, int col, const Pixel &color)
   {
      int index = 3 * (row * image_width + col);
      image_data[index] = color.r;
      image_data[index + 1] = color.g;
      image_data[index + 2] = color.b;
   }

   Pixel Image::get(int i) const
   {
      return Pixel{0, 0, 0};
   }

   // set ith pixel to &c
   void Image::set(int i, const Pixel &c)
   {
   }

   Image Image::resize(int w, int h) const
   {
      Image result(w, h);

      for (int r = 0; r < h; r++)
      {
         for (int c = 0; c < w; c++)
         {
            float r_pct = r * 1.0 / h;
            float c_pct = c * 1.0 / w;
            int orig_c = floor(c_pct * image_width);
            int orig_r = floor(r_pct * image_height);
            
            Pixel pix = get(orig_r, orig_c);
            result.set(r, c, pix);
         }
      }

      return result;
   }

   Image Image::flipHorizontal() const
   {
      Image result(0, 0);
      return result;
      //             for (int r = 0; r < h; r++)
      // {
      //    for (int c = 0; c < w; c++)

      
   }

   Image Image::flipVertical() const
   {
      Image result(0, 0);
      return result;
   }

   Image Image::rotate90() const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::subimage(int startx, int starty, int w, int h) const
   {

      Image sub(0, 0);
      return sub;
   }

   void Image::replace(const Image &image, int startx, int starty)
   {
   }

   Image Image::swirl() const
   {
      Image result(0, 0);
      return result;
   }

   Image Image::add(const Image &other) const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::subtract(const Image &other) const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::multiply(const Image &other) const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::difference(const Image &other) const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::lightest(const Image &other) const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::darkest(const Image &other) const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::gammaCorrect(float gamma) const
   {

      Image result(0, 0);

      return result;
   }

   Image Image::alphaBlend(const Image &other, float alpha) const
   {
      Image result(0, 0);

      return result;
   }

   Image Image::invert() const
   {
      Image image(0, 0);

      return image;
   }

   Image Image::grayscale() const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         { 
            Pixel pix = get(r, c);
            float red = (float)(pix.r);
            float blue = (float)(pix.g);
            float green = (float)(pix.b);

            int avg = (red * .2126 + blue *.7152 + green* .0722);
            // 0.2126 * R + 0.7152 * G + 0.0722 * B 

            Pixel grayed = {avg, avg, avg};
            result.set(r, c, grayed);
         }
      }
      return result;
   }

   Image Image::colorJitter(int size) const
   {
      Image image(0, 0);

      return image;
   }

   Image Image::bitmap(int size) const
   {
      Image image(0, 0);

      return image;
   }

   void Image::fill(const Pixel &c)
   {
   }

} // namespace agl
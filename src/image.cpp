// Copyright 2021, Aline Normoyle, alinen
/**
 * This file defines methods for the Image class. 
 * 
 * @author: Derrick Zhen
 * @version: 2/2/2023
 *
 */

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int clamp(int value)
{
   if (value < 0)
   {
      return 0;
   }
   if (value > 255)
   {
      return 255;
   }
   return value;
}

int min(int a, int b)
{
   if (a < b)
      return a;
   return b;
}

int max(int a, int b)
{
   if (a > b)
      return a;
   return b;
}

namespace agl
{

   Image::Image()
   {
      image_width = 0;
      image_height = 0;
      original_channel_no = 3;
   }

   Image::Image(int width, int height)
   {
      image_width = width;
      image_height = height;
      original_channel_no = 3;
      image_data = new unsigned char[width * height * 3];
   }

   // copy constructor
   Image::Image(const Image &orig)
   {
      this->image_width = orig.image_width;
      this->image_height = orig.image_height;

      int size = orig.image_width * orig.image_height * 3;
      this->image_data = new unsigned char[size];
      for (int i = 0; i < size; i++)
      {
         this->image_data[i] = orig.image_data[i];
      }
   }

   // assignment operator
   Image &Image::operator=(const Image &orig)
   {
      this->image_width = orig.image_width;
      this->image_height = orig.image_height;
      // this->image_data = orig.image_data;
      int size = orig.image_width * orig.image_height * 3;
      delete[] this->image_data;
      this->image_data = new unsigned char[size];

      for (int i = 0; i < size; i++)
      {
         this->image_data[i] = orig.image_data[i];
      }

      this->original_channel_no = orig.original_channel_no;

      if (&orig == this)
      {
         return *this;
      }

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
      Image result(image_width, image_height);
      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, image_width - c);
            result.set(r, c, pix);
         }
      }

      return result;
   }

   Image Image::flipVertical() const
   {
      Image result(image_width, image_height);
      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(image_height - r, c);
            result.set(r, c, pix);
         }
      }

      return result;
   }

   // todo: finish
   Image Image::rotate90() const
   {
      Image result(image_height, image_width);
      for (int c = 0; c < image_width; c++)
      {
         for (int r = 0; r < image_height; r++)
         {
            Pixel pix = get(image_height - r, c);
            result.set(c, r, pix);
         }
      }

      return result;
   }

   Image Image::subimage(int startx, int starty, int w, int h) const
   {
      Image result(w, h);

      for (int r = 0; r < h; r++)
      {
         for (int c = 0; c < w; c++)
         {
            Pixel pix = get(starty + r, startx + c);
            result.set(r, c, pix);
         }
      }

      return result;
   }

   void Image::replace(const Image &image, int startx, int starty)
   {
      // loop through and replace
      int replace_width = image.image_width;
      int replace_height = image.image_height;
      for (int r1 = 0; r1 < replace_height; r1++)
      {
         for (int c1 = 0; c1 < replace_width; c1++)
         {
            Pixel new_pix = image.get(r1, c1);
            set(startx + r1, starty + c1, new_pix);
         }
      }
   }

   Image Image::swirl() const
   {
      Image result(image_width, image_height);
      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            float red = 255 - (pix.r);
            float blue = 255 - (float)(pix.b);
            float green = 255 - (float)(pix.g);

            Pixel swirled = {pix.g, pix.b, pix.r};

            result.set(r, c, swirled);
         }
      }

      return result;
   }

   Image Image::add(const Image &other) const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            Pixel new_pix = other.get(r, c);

            float red = clamp(new_pix.r + pix.r);
            float blue = clamp(new_pix.b + pix.b);
            float green = clamp(new_pix.g + pix.g);

            Pixel added = {red, green, blue};
            result.set(r, c, added);
         }
      }

      return result;
   }

   Image Image::subtract(const Image &other) const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            Pixel new_pix = other.get(r, c);

            float red = clamp(pix.r - new_pix.r);
            float blue = clamp(pix.b - new_pix.b);
            float green = clamp(pix.g - new_pix.g);

            Pixel subtract = {red, green, blue};
            result.set(r, c, subtract);
         }
      }

      return result;
   }

   Image Image::multiply(const Image &other) const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            Pixel new_pix = other.get(r, c);

            int red = clamp((int)new_pix.r * pix.r);
            int blue = clamp((int)new_pix.b * pix.b);
            int green = clamp((int)new_pix.g * pix.g);

            Pixel multiplied = {red, green, blue};
            result.set(r, c, multiplied);
         }
      }

      return result;
   }

   Image Image::difference(const Image &other) const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            Pixel new_pix = other.get(r, c);

            float red = std::abs(new_pix.r - pix.r);
            float blue = std::abs(new_pix.b - pix.b);
            float green = std::abs(new_pix.g - pix.g);

            Pixel blended = {red, green, blue};
            result.set(r, c, blended);
         }
      }

      return result;
   }

   Image Image::lightest(const Image &other) const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            Pixel new_pix = other.get(r, c);

            float red = max(new_pix.r, pix.r);
            float blue = max(new_pix.b, pix.b);
            float green = max(new_pix.g, pix.g);

            Pixel lightest = {red, green, blue};
            result.set(r, c, lightest);
         }
      }

      return result;
   }

   Image Image::darkest(const Image &other) const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            Pixel new_pix = other.get(r, c);

            float red = min(new_pix.r, pix.r);
            float blue = min(new_pix.b, pix.b);
            float green = min(new_pix.g, pix.g);

            Pixel darkest = {red, green, blue};
            result.set(r, c, darkest);
         }
      }

      return result;
   }

   Image Image::gammaCorrect(float gamma) const
   {
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            float red = (float)(pix.r) / 255;
            float blue = (float)(pix.b) / 255;
            float green = (float)(pix.g) / 255;
            Pixel corrected = {pow(red, 1 / gamma) * 255, pow(green, 1 / gamma) * 255, pow(blue, 1 / gamma) * 255};
            result.set(r, c, corrected);
         }
      }
      return result;
   }

   Image Image::alphaBlend(const Image &other, float alpha) const
   {
      float orig_alpha = 1 - alpha;
      Image result(image_width, image_height);

      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            Pixel new_pix = other.get(r, c);
            float faded_orig_red = (float)(pix.r) * orig_alpha;
            float faded_orig_green = (float)(pix.g) * orig_alpha;
            float faded_orig_blue = (float)(pix.b) * orig_alpha;

            float faded_new_red = (float)(new_pix.r) * alpha;
            float faded_new_green = (float)(new_pix.g) * alpha;
            float faded_new_blue = (float)(new_pix.b) * alpha;

            float blended_red = faded_orig_red + faded_new_red;
            float blended_green = faded_orig_green + faded_new_green;
            float blended_blue = faded_orig_blue + faded_new_blue;

            Pixel blended = {blended_red, blended_green, blended_blue};
            result.set(r, c, blended);
         }
      }

      return result;
   }

   Image Image::invert() const
   {
      Image result(image_width, image_height);
      for (int r = 0; r < image_height; r++)
      {
         for (int c = 0; c < image_width; c++)
         {
            Pixel pix = get(r, c);
            float red = 255 - (float)(pix.r);
            float blue = 255 - (float)(pix.b);
            float green = 255 - (float)(pix.g);

            Pixel inverted = {red, green, blue};

            result.set(r, c, inverted);
         }
      }

      return result;
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

            int avg = (red * .2126 + blue * .7152 + green * .0722);

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

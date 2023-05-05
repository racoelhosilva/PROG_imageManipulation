#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

#include <string>

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      // Color Fields
      rgb_value R;
      rgb_value G;
      rgb_value B;
      
    public:
      // Constructors
      Color(); // Default (0, 0, 0)
      Color(const Color& c); // Copy Constructor
      Color(rgb_value r, rgb_value g, rgb_value b);
      // Accessors and Mutators
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();
      // Helper functions for image manipulation
      void invert();
      void to_gray_scale();
      bool is_equal(Color& arg_color);
  };

}
#endif

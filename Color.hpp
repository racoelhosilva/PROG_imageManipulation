/*  File: Color.hpp

    ██████╗ ██████╗  ██████╗  ██████╗ 
    ██╔══██╗██╔══██╗██╔═══██╗██╔════╝ 
    ██████╔╝██████╔╝██║   ██║██║  ███╗
    ██╔═══╝ ██╔══██╗██║   ██║██║   ██║
    ██║     ██║  ██║╚██████╔╝╚██████╔╝
    ╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ 

Class:
    - FEUP-L.EIC009-2022/2023-2S (Programação)
Group:
    - 13.10
Students:
    - Gonçalo Morais Magalhães
    - Rodrigo Albergaria Coelho e Silva
    - Tiago Morais de Pimentel Teixeira

Tip: the implementation of the functions on the .cpp files are in the same order as they appear defined in the corresponding .hpp header file
*/

#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

#include <string>
#include <cctype>

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      // Private Color Fields
      rgb_value R;
      rgb_value G;
      rgb_value B;
      
    public:

      // Constructors
      Color(); // Default (0, 0, 0)
      Color(const Color& c); // Copy Constructor
      Color(rgb_value r, rgb_value g, rgb_value b); // Constructor given values for each field
      
      // Accessors and Mutators for each color field
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();

      // Helper functions (for image manipulation)
      void invert();
      void to_gray_scale();
      bool is_equal(const Color& arg_color);
  };

}
#endif

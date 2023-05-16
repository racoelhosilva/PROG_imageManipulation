/*  File: Image.hpp

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

#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__

#include "Color.hpp"
#include <vector>
#include <algorithm>

namespace prog
{
  // Type definitions for comprehension and abstraction
  
  // One vector of Colors represents a row in the image
  typedef std::vector<Color> row;
  // One vector of rows of Colors is a matrix that represents all pixels in the image
  typedef std::vector< std::vector <Color> > matrix;
  
  class Image
  {
  private:
    // Private Image Fields
    
    // Image dimensions (Width and Heigth)
    int W; int H;
    // Vector of vectors of colors to represent each pixel in the image (see typedef above)
    matrix M;

  public:
    // Constructor given size and (optional) fill color
    Image(int w, int h, const Color &fill = {255, 255, 255});
    // Destructor does not need explicit definition
    //~Image();

    // Accessors for dimensions
    int width() const;
    int height() const;

    // Accessor and mutator pixel/color
    Color &at(int x, int y);
    const Color &at(int x, int y) const;

    // Image Manipulation (Maintaining size)
    void invert();
    void to_gray_scale();
    void replace(Color initial_color, Color final_color);
    void fill(int x, int y, int w, int h, Color fill_color);
    void h_mirror();
    void v_mirror();
    void add(Image* image_copy, Color neutral_color, int x, int y);

    // Image Manipulation (Changing size)
    void crop(int x, int y, Image* image_cropped);
    void rotate_left(Image* image_rotated);
    void rotate_right(Image* image_rotated);

    // Advanced Functionality
    void median_filter(int n, Image* image_filtered);
  };

  // Helper functions for the median_filter
  Color color_median(std::vector<Color> vec);
  rgb_value median(std::vector<rgb_value> values);
}
#endif

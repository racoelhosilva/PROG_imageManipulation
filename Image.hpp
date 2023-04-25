#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>
#include <algorithm>

namespace prog
{
  typedef std::vector<Color> row;
  typedef std::vector< std::vector <Color> > matrix;
  class Image
  {
  private:
    // TODO: define private fields for image state
    int W; int H;
    matrix M;

  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;

    // Image Manipulation (Maintain size)
    void invert();
    void to_gray_scale();
    void replace(Color initial_color, Color final_color);
    void fill(int x, int y, int w, int h, Color fill_color);
    void h_mirror();
    void v_mirror();
    void add(Image* image_copy, Color neutral_color, int x, int y);

    // Image Manipulation (Change size)
    void crop(int x, int y, Image* image_cropped);
    void rotate_left(Image* image_rotated);
    void rotate_right(Image* image_rotated);

    // Advanced Functionality
    void median_filter(int n, Image* image_filtered);
  };

  Color color_median(std::vector<Color> vec);

}
#endif

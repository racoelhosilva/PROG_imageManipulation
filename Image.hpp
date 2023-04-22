#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>

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
  };
}
#endif

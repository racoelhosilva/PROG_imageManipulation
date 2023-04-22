#include "Image.hpp"

namespace prog
{
  // Constructor
  Image::Image(int w, int h, const Color &fill){
    W = w; H = h;
    M = matrix(H, row(W, fill));
  }
  // Destructor
  Image::~Image(){ 
    // is it necessary??
  }

  // Size Accessors
  int Image::width() const{
    return W;
  }
  int Image::height() const{
    return H;
  }

  // Pixel Accessor
  const Color& Image::at(int x, int y) const{
    return M[y][x];
  }

  // Pixel Mutator
  Color& Image::at(int x, int y){
    return M[y][x];
  }

  // Image Manipulation
  void Image::invert() {
    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        (M[row][col]).invert();
      }
    }
  }

  void Image::to_gray_scale(){
    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        (M[row][col]).to_gray_scale();
      }
    }
  }

  void Image::replace(Color initial_color, Color final_color){
    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        if (M[row][col].is_equal(initial_color)){
          M[row][col] = (final_color);
        }
      }
    }    
  }

  void Image::fill(int x, int y, int w, int h, Color fill_color){
    for (int row = y; row < (y + h); row++){
      for (int col = x; col < (x + w); col++){
        M[row][col] = fill_color;
      }
    }
  }
}

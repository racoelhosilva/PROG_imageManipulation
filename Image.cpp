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

  void Image::h_mirror(){
    for (int row = 0; row < H; row++){
      for (int col = 0; col < (W / 2); col++){
        Color temp = M[row][col];
        M[row][col] = M[row][W - 1 - col];
        M[row][W - 1 - col] = temp;
      }
    }
  }

  void Image::v_mirror(){
    for (int row = 0; row < (H/ 2); row++){
      for (int col = 0; col < W; col++){
        Color temp = M[row][col];
        M[row][col] = M[H - 1 - row][col];
        M[H - 1 - row][col] = temp;
      }
    }
  }

  void Image::add(Image* image_copy, Color neutral_color, int x, int y){
    for (int row = 0; row < image_copy->H; row++){
      for (int col = 0; col < image_copy->W; col++){
        if (!((image_copy->M)[row][col].is_equal(neutral_color))){
          M[row + y][col + x] = (image_copy->M)[row][col];
        }
      }
    }
  }

  void Image::crop(int x, int y, Image* image_cropped){
    for (int row = 0; row < image_cropped->H; row++){
      for (int col = 0; col < image_cropped->W; col++){
        (image_cropped->M)[row][col] = M[row + y][col + x];
      }
    }
  }

}


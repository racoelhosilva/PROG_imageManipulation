#include "Image.hpp"
#include <algorithm>
#include <iostream>

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

  void Image::rotate_left(Image* image_rotated){
    for (int row = 0; row < image_rotated->H; row++){
      for (int col = 0; col < image_rotated->W; col++){
        (image_rotated->M)[row][col] = M[col][image_rotated->H - 1 - row];
      }
    }
  }

  void Image::rotate_right(Image* image_rotated){
    for (int row = 0; row < image_rotated->H; row++){
      for (int col = 0; col < image_rotated->W; col++){
        (image_rotated->M)[row][col] = M[image_rotated->W - 1 - col][row];
      }
    }
  }

    void Image::median_filter(int n, Image* image_filtered){
    int amp = (n - 1) / 2; 
    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        // for every pixel, fix a square with n.n squares and center in the pixel
        std::vector<Color> square;
        for (int s_row = row - amp; s_row <= row + amp; s_row++){
          for (int s_col = col - amp; s_col <= col + amp; s_col++){
            bool check_vertical = (s_row >= 0) && (s_row < H);
            bool check_horizontal = (s_col >= 0) && (s_col < W);
            if (check_horizontal && check_vertical){
              square.push_back(M[s_row][s_col]);
              // square[0] = M[s_row][s_col];
              continue;
            }
          }
        }
        (image_filtered->M)[row][col] = color_median(square);
      }
    }
  }

  // Should this helper function be defined *here* and as *private*
  rgb_value median(std::vector<rgb_value> values){
    std::sort(values.begin(), values.end());
    rgb_value result;
    int vectorSize = values.size();
    if (vectorSize % 2 == 1){
        result = values[(vectorSize/2)];
    }
    else {
        result = (values[(vectorSize + 1) / 2] + values[(vectorSize - 1) / 2]) / 2;
    }
    return result;
  }
  

  Color color_median(std::vector<Color> square){
    std::vector<rgb_value> reds(square.size()), greens(square.size()), blues(square.size());
    for (int v_idx = 0; v_idx < (int)square.size(); v_idx++){
      reds[v_idx] = square[v_idx].red();
      greens[v_idx] = square[v_idx].green();
      blues[v_idx] = square[v_idx].blue();
    }
    rgb_value mr, mg, mb;
    mr = median(reds);
    mg = median(greens);
    mb = median(blues);
    return {mr, mg, mb};
  }

  
}


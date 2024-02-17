/*  File: Image.cpp

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

#include "Image.hpp"
#include <algorithm>
#include <iostream>

namespace prog
{
  Image::Image(int w, int h, const Color &fill){
    // Constructor given dimensions and (optional) fill color; if no fill color is given, uses "white" (255, 255, 255) 
    W = w; H = h;
    M = matrix(H, row(W, fill));
  }

  // Destructor doesn't need explicit definition
  // Image::~Image(){ }

  // Accessors for dimensions

  int Image::width() const{
    // Accessor for image width (already a field of Image)
    return W;
  }
  int Image::height() const{
    // Accessor for image height (already a field of Image)
    return H;
  }

  const Color& Image::at(int x, int y) const{
    // Pixel/Color Accessor
    return M[y][x];
  }
  Color& Image::at(int x, int y){
    // Pixel/Color Mutator
    return M[y][x];
  }


  // Image Manipulation (Maintaining Size)

  void Image::invert() {
    // Inverts every Color in an Image object (255 - rgb_value)
    // Uses the helper method Color::invert()

    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        (M[row][col]).invert();
      }
    }
  }

  void Image::to_gray_scale(){
    // Changes every Color in an Image object to its gray-scaled value 
    // Uses the helper function Color::to_gray_scale()

    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        (M[row][col]).to_gray_scale();
      }
    }
  }

  void Image::replace(Color initial_color, Color final_color){
    // Changes every pixel in an Image that matches  the initial_color by the final_color
    // Uses the helper function Color::is_equal() to compare two Colors

    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        if (M[row][col].is_equal(initial_color)){
          M[row][col] = (final_color);
        }
      }
    }    
  }

  void Image::fill(int x, int y, int w, int h, Color fill_color){
    // Fills a rectangle on top of the current Image using fill_color
    // The rectangle is given by the coordinates of the top left corner and the dimensions
    
    for (int row = y; row < (y + h); row++){
      for (int col = x; col < (x + w); col++){
        M[row][col] = fill_color;
      }
    }
  }

  void Image::h_mirror(){
    // Mirrors the image horizontally

    for (int row = 0; row < H; row++){
      for (int col = 0; col < (W / 2); col++){
        Color temp = M[row][col];
        M[row][col] = M[row][W - 1 - col];
        M[row][W - 1 - col] = temp;
      }
    }
  }

  void Image::v_mirror(){
    // Mirrors the image vertically

    for (int row = 0; row < (H/ 2); row++){
      for (int col = 0; col < W; col++){
        Color temp = M[row][col];
        M[row][col] = M[H - 1 - row][col];
        M[H - 1 - row][col] = temp;
      }
    }
  }

  void Image::add(Image* image_copy, Color neutral_color, int x, int y){
    // Pastes image_copy on top of current image (everything is else is kept)
    // The position is given by the coordinates of the top left corner
    // A neutral_color is passed as parameter and is ignored when pasting the image
    // Uses the helper function Color::is_equal() to compare two Colors
    

    for (int row = 0; row < image_copy->H; row++){
      for (int col = 0; col < image_copy->W; col++){
        if (!((image_copy->M)[row][col].is_equal(neutral_color))){
          M[row + y][col + x] = (image_copy->M)[row][col];
        }
      }
    }
  }

  // Image Manipulations (Changing Size)

  void Image::crop(int x, int y, Image* image_cropped){
    // Crop the current Image into a smaller rectangle, storing it in image_cropped
    // The rectangle is given by the coordinates of top left corner (dimensions are already specified by the image_cropped)

    for (int row = 0; row < image_cropped->H; row++){
      for (int col = 0; col < image_cropped->W; col++){
        (image_cropped->M)[row][col] = M[row + y][col + x];
      }
    }
  }

  void Image::rotate_left(Image* image_rotated){
    // Rotate the Image 90 degrees to the left
    // The resulting image is stored in image_rotated, which should already have the correct dimensions

    for (int row = 0; row < image_rotated->H; row++){
      for (int col = 0; col < image_rotated->W; col++){
        (image_rotated->M)[row][col] = M[col][image_rotated->H - 1 - row];
      }
    }
  }

  void Image::rotate_right(Image* image_rotated){
    // Rotate the Image 90 degrees to the right
    // The resulting image is stored in image_rotated, which should already have the correct dimensions

    for (int row = 0; row < image_rotated->H; row++){
      for (int col = 0; col < image_rotated->W; col++){
        (image_rotated->M)[row][col] = M[image_rotated->W - 1 - col][row];
      }
    }
  }

  // Advanced Functionality

  void Image::median_filter(int n, Image* image_filtered){
    // Applies a median filter of square size given by n
    // Stores the result Image in image_filtered
    // Uses the helper function color_median to calculate the median of each square

    int amp = (n - 1) / 2; 
    // Calculates the amplitude of the square (number of Colors to consider in each direction)

    for (int row = 0; row < H; row++){
      for (int col = 0; col < W; col++){
        // For every pixel, creates a vector with n.n Colors and center in the pixel
        // Only adds the Colors if they are within the limits of the Image

        std::vector<Color> square;
        for (int s_row = row - amp; s_row <= row + amp; s_row++){
          for (int s_col = col - amp; s_col <= col + amp; s_col++){
            bool check_vertical = (s_row >= 0) && (s_row < H);
            bool check_horizontal = (s_col >= 0) && (s_col < W);
            // Conditions for the Color to be added (the coordinates must be inside the image)
            
            if (check_horizontal && check_vertical){
              square.push_back(M[s_row][s_col]);
              // Adds the color to the square
            }
          }
        }
        (image_filtered->M)[row][col] = color_median(square);
        // Changes the Color of the pixel in the resulting image to the median of the Colors in the initial image
        // Uses the color_median to calculate
      }
    }
  }

  // Helper functions for the median filter
  
  Color color_median(std::vector<Color> square){
    // Process the median of a vector of colors by splitting colors their fields and uses the helper function median to calculate the median of each field
    // Returns the corresponding Color object 

    std::vector<rgb_value> reds(square.size()), greens(square.size()), blues(square.size());
    // Creates vectors for each color Field

    for (int v_idx = 0; v_idx < (int)square.size(); v_idx++){
      // Separates the vector of Colors into vectors of fields of the Colors (rgb_values)
      reds[v_idx] = square[v_idx].red();
      greens[v_idx] = square[v_idx].green();
      blues[v_idx] = square[v_idx].blue();
    }
    rgb_value mr, mg, mb;
    mr = median(reds);
    mg = median(greens);
    mb = median(blues);
    // Calculates the median of each vector of Color fields
    // Uses the helper function median to calculate the median of each vector of rgb_values (Color fields)

    return {mr, mg, mb};
    // Returns the Color with the median of each field
  }

    rgb_value median(std::vector<rgb_value> values){
    // Calculate the median of a vector of rgb_values

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
}


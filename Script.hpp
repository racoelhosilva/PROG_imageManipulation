/*  File: Script.hpp

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

#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    // Initial (given) functions
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Private parameters

    // Current image
    Image *image;
    // Input stream for reading script commands
    std::ifstream input;
  private:
    // Private functions

    // Initial (given) functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();

    // Image Manipulations (Maintaining Size)
    void invert();
    void to_gray_scale();
    void replace();
    void fill();
    void h_mirror();
    void v_mirror();
    void add();

    // Image Manipulations (Changing Size)
    void crop();
    void rotate_left();
    void rotate_right();

    // Advanced Functionality
    void median_filter();

    // Processing XPM2 Files
    void xpm2_open();
    void xpm2_save();
  };
}
#endif

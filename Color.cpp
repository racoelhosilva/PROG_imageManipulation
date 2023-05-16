/*  File: Color.cpp

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

#include "Color.hpp"
#include <string>
#include <cctype>

namespace prog {

    // Constructors
    
    Color::Color() {
        // Default Constructor (0 ,0 ,0)
        R = 0; G = 0; B = 0;
    }
    Color::Color(const Color& other) {
        // Copy Constructor
        R = other.R; G = other.G; B = other.B;
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        // Constructor given values for each field
        R = red; G = green; B = blue;
    }

    // Accessors (for each color field)

    rgb_value Color::red() const {
        // Accessor for red color field
        return R;
    }
    rgb_value Color::green() const {
        // Accessor for green color field
        return G;
    }
    rgb_value Color::blue() const {
        // Accessor for blue color field
        return B;
    }

    // Mutators (for each color field)
    
    rgb_value& Color::red()  {
        // Mutator for red color field
        return R;
    }
    rgb_value& Color::green()  {
        // Mutator for green color field
        return G;
    }
    rgb_value& Color::blue()  {
        // Mutator for blue color field
        return B;
    }

    // Helper functions (for image manipulation)

    
    void Color::invert(){
        // Inverts one color (used in Image::invert())
        R = 255 - R; G = 255 - G; B = 255 - B;
    }

    void Color::to_gray_scale(){
        // Change one color to grayscale (used in Image::to_gray_scale())
        rgb_value gray = (R + G + B) / 3;
        R = gray; G = gray; B = gray;
    }
    
    bool Color::is_equal(const Color& arg_color){
        // Checks if two colors are equal (used in Image::add() and Image::replace())
        return (R == arg_color.R) && (G == arg_color.G) && (B == arg_color.B);
    }
}

#include "Color.hpp"

namespace prog {
    // Constructors
    Color::Color() {
        R = 0; G = 0; B = 0;
    }
    Color::Color(const Color& other) {
        R = other.R; G = other.G; B = other.B;
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        R = red; G = green; B = blue;
    }

    // Accessors
    rgb_value Color::red() const {
        return R;
    }
    rgb_value Color::green() const {
        return G;
    }
    rgb_value Color::blue() const {
        return B;
    }

    // Mutators
    rgb_value& Color::red()  {
        return R;
    }
    rgb_value& Color::green()  {
        return G;
    }
    rgb_value& Color::blue()  {
        return B;
    }

    // Helper functions for image manipulation
    void Color::invert(){
        R = 255 - R; G = 255 - G; B = 255 - B;
    }
    void Color::to_gray_scale(){
        rgb_value gray = (R + G + B) / 3;
        R = gray; G = gray; B = gray;
    }

    bool Color::is_equal(Color& arg_color){
        return (R == arg_color.R) && (G == arg_color.G) && (B == arg_color.B);
    }
}

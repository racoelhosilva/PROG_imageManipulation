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
}

#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include "Image.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>


namespace prog {
    Image* loadFromXPM2(const std::string &file);
    // Helper function for load
    rgb_value hex_to_dec(std::string& hex_value);

    void saveToXPM2(const std::string& file, const Image* img);

    // Helper function for save
    bool operator<(const Color& c1, const Color& c2);
    std::string dec_to_hex(rgb_value c);

    

}
#endif

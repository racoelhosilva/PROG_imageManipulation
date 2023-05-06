#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include "Image.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <map>


namespace prog {
    // Load an image from XPM2 file
    Image* loadFromXPM2(const std::string &file);
    // Helper function for load
    rgb_value hex_to_dec(std::string& hex_value);


    // Save an image into XPM2 file
    void saveToXPM2(const std::string& file, const Image* img);
    // Helper functions for save
    bool operator<(const Color& c1, const Color& c2);
    std::string dec_to_hex(rgb_value c);
}
#endif

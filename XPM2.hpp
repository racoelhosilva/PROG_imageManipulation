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

    void saveToXPM2(const std::string& file, const Image* img);

    bool operator<(const Color& c1, const Color& c2);

    std::string lowercase(const std::string& word);

}
#endif

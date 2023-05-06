/*  File: XPM2.cpp

    ██████╗ ██████╗  ██████╗  ██████╗ 
    ██╔══██╗██╔══██╗██╔═══██╗██╔════╝ 
    ██████╔╝██████╔╝██║   ██║██║  ███╗
    ██╔═══╝ ██╔══██╗██║   ██║██║   ██║
    ██║     ██║  ██║╚██████╔╝╚██████╔╝
    ╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ 
                                  
Group:
    - 13.10
Students:
    - Gonçalo Morais Magalhães
    - Rodrigo Albergaria Coelho e Silva
    - Tiago Morais de Pimentel Teixeira

Tip: the implementation of the functions on the .cpp files are in the same order as they appear defined in the corresponding .hpp header file
*/
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
    // Helper function for loadFromXPM2
    rgb_value hex_to_dec(std::string& hex_value);

    // Save an image into XPM2 file
    void saveToXPM2(const std::string& file, const Image* img);
    // Helper functions for saveToXPM2
    bool operator<(const Color& c1, const Color& c2);
    std::string dec_to_hex(rgb_value c);
}
#endif

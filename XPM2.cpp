#include "XPM2.hpp"

namespace prog {
    Image* loadFromXPM2(const std::string& file) {
        // Load the dimensions of the image 
        // Create an image with that size

        // Load the nº of colors
        // Loop through the index appending every correspondence to a map symbol to color

        // Loop through the nº of lines (dimension)
        // For every line, create a vector of colors
        // For every symbol read, create a color

        // Push back the vector into the Image

        return nullptr;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        // Generate a map of color to symbol
        // Create the header with the dimensions and nº of colors
        // Create the index for the colors 

        // Loop through each line
            // Loop through each color
                // Add the symbol corresp. to a string
            // Add the whole string to the file
            // Go to the next line
            
    }
}

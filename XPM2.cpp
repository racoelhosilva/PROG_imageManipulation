#include "XPM2.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <cctype>

namespace prog {
    Image* loadFromXPM2(const std::string& file) {
        // Load the dimensions of the image 
        // Create an image with that size

        std::ifstream fileReader(file);
        std::string generalInput;
        // Skip the header
        fileReader >> generalInput; fileReader >> generalInput;
        // Load the dimensions
        int width, height;
        fileReader >> width; fileReader >> height;
        Image* resultImage = new Image(width, height);

        // Load the nº of colors
        int numberOfColors;
        fileReader >> numberOfColors;
        fileReader >> generalInput;
        // Loop through the index appending every correspondence to a map symbol to color
        std::map<char, Color> indexSymbolColor;
        for (int _ = 0; _ < numberOfColors; _++){
            char symbol; 
            std::string hexcode;
            fileReader >> symbol; 
            fileReader >> generalInput;
            fileReader >> hexcode;
            // Color currentColor = hex_to_dec(hexcode);
            indexSymbolColor.insert({symbol, Color()});
            // Creates and empty color *fix later*
            // std::cout << symbol << " " << hexcode << "\n";
        }

        // Loop through the nº of lines (dimension)
        // For every line, create a vector of colors
        // For every symbol read, create a color
        std::getline (fileReader, generalInput);
        // Push back the vector into the Image
        for (int lineIndex = 0; lineIndex < height; lineIndex++){
            std::string currentLine;
            std::getline (fileReader, currentLine);
            // std::cout << currentLine << "\n";
            for (int colIndex = 0; colIndex < width; colIndex++){
                char symbolRead = currentLine.at(colIndex);
                Color currentColor = indexSymbolColor[symbolRead];
                resultImage->at(colIndex, lineIndex) = currentColor;
            }
        }

        return resultImage;
    }

    std::string lowercase(const std::string& word){
        std::string result;
        for (int idx = 0; idx < (int)word.size(); idx++){
            result.push_back(tolower((char)word[idx]));
        }
        return result;
    }

    Color hex_to_dec(std::string hexcode){
        std::string hexlower = lowercase(hexcode);
        std::string red = hexlower.substr(1, 1+2);
        std::string green = hexlower.substr(3, 3+2);
        std::string blue = hexlower.substr(5, 5+2);
        int red_ = 0, blue_ = 0, green_ = 0; int sixteen = 16; int temp = 0;
        for (char i : red){
            temp += (i >= 'A') ? (i >= 'a') ? (i - 'a' + 10) : (i - 'A' + 10) : (i - '0');
            red_ += sixteen * temp;
            sixteen = 1; }
        sixteen = 16; temp = 0;
        for (char i : green){
            temp += (i >= 'A') ? (i >= 'a') ? (i - 'a' + 10) : (i - 'A' + 10) : (i - '0');
            green_ += sixteen * temp;
            sixteen = 1; }
        sixteen = 16; temp = 0;
        for (char i : blue){
            temp += (i >= 'A') ? (i >= 'a') ? (i - 'a' + 10) : (i - 'A' + 10) : (i - '0');
            blue_ += sixteen * temp;
            sixteen = 1;
        }
        return Color(red_, green_, blue_);
    }



    bool operator<(const Color& c1, const Color& c2){
        bool red_check = c1.red() < c2.red();
        bool green_check =  c1.red() == c2.red() && c1.green() < c2.green();
        bool blue_check = c1.red() == c2.red() && c1.green() == c2.green() && c1.blue() < c2.blue();
        return red_check || green_check || blue_check;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        // Generate a map of color to symbol
        std::map<Color, char> indexColorSymbol;
        char symbols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        int symbolsCounter = 0;

        for (int row = 0; row < image->height(); row++){
            for (int col = 0; col < image->width(); col++){
                Color currentColor = image->at(col, row);
                if (!(indexColorSymbol.count(currentColor))){
                    char symbol = symbols[symbolsCounter];
                    indexColorSymbol.insert({currentColor, symbol});
                    symbolsCounter++;
                }
            }
        }

        // Create the header with the dimensions and nº of colors 
        std::ofstream fileWriter(file);
        fileWriter << "! XPM2" << '\n';
        fileWriter << image->width() << ' ' << image->height() << ' ' << symbolsCounter << " 1" << '\n';

        // Create the index for the colors
        for (const auto& indexItr : indexColorSymbol){
            // std::string hexcode = (indexItr.first);
            fileWriter << indexItr.second << " c " << "#HEXCODE" << '\n';
        }
        // Loop through each line
            // Loop through each color
                // Add the symbol corresp. to a string
            // Add the whole string to the file
            // Go to the next line
        
        for (int row = 0; row < image->height(); row++){
            for (int col = 0; col < image->width(); col++){
                Color currentColor = image->at(col, row);
                char symbolToWrite = indexColorSymbol[currentColor];
                fileWriter << symbolToWrite;
            }
            fileWriter << '\n';
        }
        // This can be improved if we append strings over and over and only send to the file in the end
    }
}

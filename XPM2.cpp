/*  File: XPM2.cpp

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

#include "XPM2.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

namespace prog {
    Image* loadFromXPM2(const std::string& file) {
        // Reads an XPM2 file (with filename <file>)
        // Returns a pointer to an Image object containing the corresponding image

        std::ifstream fileReader(file);

        std::string generalInput;
        fileReader >> generalInput; fileReader >> generalInput;
        // Note: this generalInput will be used throughout the function to skip/ignore unnecessary text from the XMP2 file
        // These include: the header, the "1" on the second line and the "c" used in every color correspondence

        int width, height;
        fileReader >> width; fileReader >> height;
        Image* resultImage = new Image(width, height);
        // After reading the dimensions, creates a blank image

        int numberOfColors;
        fileReader >> numberOfColors;
        fileReader >> generalInput;

        std::map<char, Color> indexSymbolColor;
        // Creates a map to store the color correspondences

        for (int _ = 0; _ < numberOfColors; _++){
            char symbol; 
            std::string hexcode;
            fileReader >> symbol; 
            fileReader >> generalInput;
            fileReader >> hexcode;
            // Reads the line for one color correspondence

            std::string red_hex = (hexcode.substr(1, 2));
            std::string green_hex = (hexcode.substr(3, 2));
            std::string blue_hex = (hexcode.substr(5, 2));
            // Splits the hex code into the components

            Color currentColor = Color(hex_to_dec(red_hex), hex_to_dec(green_hex),hex_to_dec(blue_hex));
            // Converts the hex codes into rgb_values using hex_to_dec and uses them to initialize the Color
            
            indexSymbolColor.insert({symbol, currentColor});
            // Inserts the {symbol, Color} pair into the map
        }
        // Knowing the number of colors, creates a map of symbols (stored as chars) to Color objects
        // Note: converts the hexcode given in the file into rgb_values, using an auxiliar function (see comments above)

        std::getline (fileReader, generalInput);
        // Move into the line where the image is represented

        for (int lineIndex = 0; lineIndex < height; lineIndex++){
            std::string currentLine;
            std::getline (fileReader, currentLine);
            // Processes every line, line by line

            for (int colIndex = 0; colIndex < width; colIndex++){
                char symbolRead = currentLine.at(colIndex);
                Color currentColor = indexSymbolColor[symbolRead];
                // Processes every symbol the line and gets the corresponding Color

                resultImage->at(colIndex, lineIndex) = currentColor;
                // Changes the Color of the Image in that position to the new Color
            }
        }
        // Processes every symbol and changes the color in the Image to the color of the corresponding symbol

        return resultImage;
    }

    rgb_value hex_to_dec(std::string& hex_value){
        // Auxiliar function to convert a 2-char string containing a hexadecimal value into an rgb_value (0-255)

        rgb_value result = 0;
        for (char symbol : hex_value){
            result *= 16;
            switch (symbol){
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                result += (symbol - '0'); break;
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                result += (symbol - 'a' + 10); break;
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                result += (symbol - 'A' + 10); break;
            default:
                result += 0; break;
            }
        }
        return result;
    }


    void saveToXPM2(const std::string& file, const Image* image) {
        // Stores an Image object (passed as a pointer) into an XPM2 file (with filename <file>)

        std::map<Color, char> indexColorSymbol;
        // Creates a map to store the color correspondences
        
        int symbolsCounter = 0;
        char symbols[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
        // Creates a 64 char array of the symbols that will be used to store the colors in the file
        // Disclaimer: It is assumed that the image will not have more than 64 colors (Base64), however more symbols can easily be added by changing the array size, and the verification in the loop below

        for (int row = 0; row < image->height(); row++){
            for (int col = 0; col < image->width(); col++){
                // Processes every color in the image

                if (symbolsCounter >= 64)  { 
                    // Verification: too many colors to process (Base 64 assumed - see disclaimer above)
                    break;
                }

                Color currentColor = image->at(col, row);                
                if (!(indexColorSymbol.count(currentColor))){
                    char symbol = symbols[symbolsCounter];
                    indexColorSymbol.insert({currentColor, symbol});
                    // If the color is not already in the map, pairs it with a symbol and inserts the pair into the map
                    
                    symbolsCounter++;
                }
            }
        }
        // Processes every Color in the image, pairs it with symbol and stores it in the map
        // Counts how many colors exist and doesn't map duplicates 
 
        std::ofstream fileWriter(file);
        fileWriter << "! XPM2" << '\n';
        fileWriter << image->width() << ' ' << image->height() << ' ' << symbolsCounter << " 1" << '\n';
        // Writes the first two lines (Header and Specifications)

        for (auto& indexItr : indexColorSymbol){
            std::string red_hex = dec_to_hex(indexItr.first.red());
            std::string green_hex = dec_to_hex(indexItr.first.green());
            std::string blue_hex = dec_to_hex(indexItr.first.blue());
            // Obtains the hexcodes of every field of the colors stored in the map, using the auxiliar funciton dec_to_hex

            fileWriter << indexItr.second << " c #" << red_hex << green_hex << blue_hex << '\n';
            // Writes the correspondences of symbol and Color to the file
        }
        // Writes every symbol and color correspondence previously obtained (map)
        // Note: converts the color into hexadecimal using an auxiliar function (see comments above)

        for (int row = 0; row < image->height(); row++){
            for (int col = 0; col < image->width(); col++){
                Color currentColor = image->at(col, row);
                char symbolToWrite = indexColorSymbol[currentColor];
                // Processes every color in the Image object, obtaining the corresponding symbol

                fileWriter << symbolToWrite;
                // Writes the symbol into the file
            }
            fileWriter << '\n';
            // Advances one line in the file
        }
        // Processes every color in the Image saving the corresponding symbol in the file
    }

    std::string dec_to_hex(rgb_value c){
        // Auxiliar function to convert an rgb_value (0-255) into a hexadecimal 2-char string

        std::string result = "";

        rgb_value first = c / 16;
        if (first >= 10){ result.push_back(char(first - 10 + 'A')); }
        else { result.push_back(char(first + '0')); }
        
        rgb_value second = c % 16;
        if (second >= 10){ result.push_back(char(second - 10 + 'A')); }
        else { result.push_back(char(second + '0')); }
        // Note: since it is only two characters, processes one at a time
        
        return result;
    }

    bool operator<(const Color& c1, const Color& c2){
        // Operator defined to allow storing a map<Color,char> since the keys (Color) need to be comparable

        bool red_check = c1.red() < c2.red();
        bool green_check =  c1.red() == c2.red() && c1.green() < c2.green();
        bool blue_check = c1.red() == c2.red() && c1.green() == c2.green() && c1.blue() < c2.blue();
        return red_check || green_check || blue_check;
    }
}

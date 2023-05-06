#include "XPM2.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

namespace prog {
    Image* loadFromXPM2(const std::string& file) {
        std::ifstream fileReader(file);
        std::string generalInput;
        fileReader >> generalInput; fileReader >> generalInput;

        int width, height;
        fileReader >> width; fileReader >> height;
        Image* resultImage = new Image(width, height);

        int numberOfColors;
        fileReader >> numberOfColors;
        fileReader >> generalInput;

        std::map<char, Color> indexSymbolColor;
        for (int _ = 0; _ < numberOfColors; _++){
            char symbol; 
            std::string hexcode;
            fileReader >> symbol; 
            fileReader >> generalInput;
            fileReader >> hexcode;

            std::string red_hex = (hexcode.substr(1, 2));
            std::string green_hex = (hexcode.substr(3, 2));
            std::string blue_hex = (hexcode.substr(5, 2));

            Color currentColor = Color(hex_to_dec(red_hex), hex_to_dec(green_hex),hex_to_dec(blue_hex));
            indexSymbolColor.insert({symbol, currentColor});
        }

        std::getline (fileReader, generalInput);

        for (int lineIndex = 0; lineIndex < height; lineIndex++){
            std::string currentLine;
            std::getline (fileReader, currentLine);
            for (int colIndex = 0; colIndex < width; colIndex++){
                char symbolRead = currentLine.at(colIndex);
                Color currentColor = indexSymbolColor[symbolRead];
                resultImage->at(colIndex, lineIndex) = currentColor;
            }
        }

        return resultImage;
    }

    rgb_value hex_to_dec(std::string& hex_value){
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

//===========================================================//

    void saveToXPM2(const std::string& file, const Image* image) {

        std::map<Color, char> indexColorSymbol;
        char symbols[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
        int symbolsCounter = 0;

        for (int row = 0; row < image->height(); row++){
            for (int col = 0; col < image->width(); col++){
                Color currentColor = image->at(col, row);
                if (symbolsCounter >= 64)  { 
                    // Too many colors to process (Base64 assumed)
                    break;
                }
                if (!(indexColorSymbol.count(currentColor))){
                    char symbol = symbols[symbolsCounter];
                    indexColorSymbol.insert({currentColor, symbol});
                    symbolsCounter++;
                }
            }
        }
 
        std::ofstream fileWriter(file);
        fileWriter << "! XPM2" << '\n';
        fileWriter << image->width() << ' ' << image->height() << ' ' << symbolsCounter << " 1" << '\n';

        for (auto& indexItr : indexColorSymbol){
            std::string red_hex = dec_to_hex(indexItr.first.red());
            std::string green_hex = dec_to_hex(indexItr.first.green());
            std::string blue_hex = dec_to_hex(indexItr.first.blue());

            fileWriter << indexItr.second << " c #" << red_hex << green_hex << blue_hex << '\n';
        }

        for (int row = 0; row < image->height(); row++){
            for (int col = 0; col < image->width(); col++){
                Color currentColor = image->at(col, row);
                char symbolToWrite = indexColorSymbol[currentColor];
                fileWriter << symbolToWrite;
            }
            fileWriter << '\n';
        }
    }

    std::string dec_to_hex(rgb_value c){
        std::string result = "";

        rgb_value first = c / 16;
        if (first >= 10){ result.push_back(char(first - 10 + 'A')); }
        else { result.push_back(char(first + '0')); }
        
        rgb_value second = c % 16;
        if (second >= 10){ result.push_back(char(second - 10 + 'A')); }
        else { result.push_back(char(second + '0')); }

        return result;
    }



    bool operator<(const Color& c1, const Color& c2){
        bool red_check = c1.red() < c2.red();
        bool green_check =  c1.red() == c2.red() && c1.green() < c2.green();
        bool blue_check = c1.red() == c2.red() && c1.green() == c2.green() && c1.blue() < c2.blue();
        return red_check || green_check || blue_check;
    }
}

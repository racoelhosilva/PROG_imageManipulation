/*  File: Script.cpp

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

#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 

            // Implemented commands
            if (command == "invert") {
                invert();
                continue;
            }
            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }
            if (command == "replace"){
                replace();
                continue;
            }
            if (command == "fill"){
                fill();
                continue;
            }
            if (command == "h_mirror"){
                h_mirror();
                continue;
            }
            if (command == "v_mirror"){
                v_mirror();
                continue;
            }
            if (command == "add"){
                add();
                continue;
            }
            if (command == "crop"){
                crop();
                continue;
            }
            if (command == "rotate_left"){
                rotate_left();
                continue;
            }
            if (command == "rotate_right"){
                rotate_right();
                continue;
            }
            if (command == "median_filter"){
                median_filter();
                continue;
            }
            if (command == "xpm2_open"){
                xpm2_open();
                continue;
            }
            if (command == "xpm2_save"){
                xpm2_save();
                continue;
            }
        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    // Image Manipulations (Maintaining Size)

    void Script::invert() {
        // Inverts the value of each Color in the Image (255 - rgb_value)
        
        image->invert();
    }

    void Script::to_gray_scale(){
        // Grayscales each Color of the Image
        
        image->to_gray_scale();
    }

    void Script::replace(){
        // Replaces every Color in the Image that matches  the initial_color by the final_color 
        
        Color initial_color, final_color;
        input >> initial_color >> final_color;
        // Loads the necessary parameters
        
        image->replace(initial_color, final_color);
    }

    void Script::fill(){
        // Fills a rectangle in the Image with a Color
        
        int x, y, w, h;
        Color fill_color;
        input >> x >> y >> w >> h >> fill_color;
        // Loads the necessary parameters

        image->fill(x, y, w, h, fill_color);
    }

    void Script::h_mirror(){
        // Mirrors the image horizontally
        
        image->h_mirror();
    }
    void Script::v_mirror(){
        // Mirrors the image vertically

        image->v_mirror();
    }

    void Script::add(){
        // Pastes image from filename on top of current image (everything is else is kept)

        string filename;
        Image *image_copy;
        input >> filename;
        image_copy = loadFromPNG(filename);
        // Loads the new Image
        
        Color neutral_color; int x, y;
        input >> neutral_color >> x >> y;
        // Loads the necessary parameters

        image->add(image_copy, neutral_color, x, y);

        if (image_copy != nullptr) {
            delete image_copy;
            image_copy = nullptr;
        }
        // Deletes the new Image (already pasted)
    }

    // Image Manipulations (Changing Size)

    void Script::crop(){
        // Crop the current Image into a smaller rectangle

        int x, y, w, h;
        input >> x >> y >> w >> h;
        Image *image_cropped = new Image(w, h);
        // Loads the necessary parameters and creates a new Image to store the cropped image

        image->crop(x, y, image_cropped);

        if (image != nullptr) {
            delete image;
            image = image_cropped;
            image_cropped = nullptr;
        }
        // Deletes the previous Image and makes the cropped Image the new current Image
    }

    void Script::rotate_left(){
        // Rotate the Image 90 degrees to the left
        
        Image *image_rotated = new Image(image->height(), image->width());
        // Creates a new Image to store the rotated Image

        image->rotate_left(image_rotated);

        if (image != nullptr) {
            delete image;
            image = image_rotated;
            image_rotated = nullptr;
        }
        // Deletes the previous Image and makes the rotated Image the new current Image
    }

    void Script::rotate_right(){
        // Rotate the image 90 degrees to the right

        Image *image_rotated = new Image(image->height(), image->width());
        // Creates a new Image to store the rotated Image

        image->rotate_right(image_rotated);

        if (image != nullptr) {
            delete image;
            image = image_rotated;
            image_rotated = nullptr;
        }
        // Deletes the previous Image and makes the rotated Image the new current Image
    }

    // Advanced Functionality

    void Script::median_filter(){
        // Apply a median filter of n to the Image
        
        Image *image_filtered = new Image(image->width(), image->height());
        // Creates a new Image to store the filtered Image

        int n;
        input >> n;
        // Loads the necessary parameters

        image->median_filter(n, image_filtered);

        if (image != nullptr) {
            delete image;
            image = image_filtered;
            image_filtered = nullptr;
        }
        // Deletes the previous Image and makes the filtered Image the new current Image
    }

    // Processing XPM2 Files

    void Script::xpm2_open(){
        // Open XPM2 files to an image object
        
        clear_image_if_any();
        // Deletes the current image

        string inputFilename;
        input >> inputFilename;
        // Loads the necessary parameters

        image = loadFromXPM2(inputFilename);
    }
    
    void Script::xpm2_save(){
        // Save image object into XPM2 file
        
        string outputFilename;
        input >> outputFilename;
        // Loads the necessary parameters

        saveToXPM2(outputFilename, image);
    }
}

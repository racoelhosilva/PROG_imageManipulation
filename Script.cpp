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
            // TODO ...
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

    void Script::invert() {
        // Inverts the value of each pixel (255 - value)
        image->invert();
    }

    void Script::to_gray_scale(){
        // Grayscales each pixel of the image
        image->to_gray_scale();
    }

    void Script::replace(){
        // Replaces every pixel of the initial color by the final color
        Color initial_color, final_color;
        input >> initial_color >> final_color;
        image->replace(initial_color, final_color);
    }

    void Script::fill(){
        // Fills a rectangle with a color
        int x, y, w, h;
        Color fill_color;
        input >> x >> y >> w >> h >> fill_color;
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
        // Pastes image from filename on top of current image
        string filename;
        Image *image_copy;
        input >> filename;
        image_copy = loadFromPNG(filename);
        Color neutral_color; int x, y;
        input >> neutral_color >> x >> y;
        image->add(image_copy, neutral_color, x, y);
        if (image_copy != nullptr) {
            delete image_copy;
            image_copy = nullptr;
        }
    }
}

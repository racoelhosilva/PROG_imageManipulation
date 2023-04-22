# Project for Programming (FEUP-L.EIC009)

## Basic Description

In this project you will use C++ to represent and process RGB color images with 8-bits per RGB channel. For that you will work (mainly) with 3 separate types of classes:
 * <prog::Color> to represent **RGB colors**;
 * <prog::Image> to represent **images** as 2D Matrix where individual pixels are represented by _Color_;
 * <prog::Script> to process scripts that contain **image manipulation commands**;

Initial files are already provided and some of them mustn't (and needn't) be changed.

## Files to Change and To-Do List

> **Color Class**
  * Color.cpp: class implementation of Color.h
  * Color.hpp: header file for class declaration (Interface)
  1. Default Constructor
  2. Copy Constructor
  3. Constructor with values
  4. Accessors for each attribute
  5. Mutators for each attribute
  6. ...
> **Image Class**
  * Image.cpp: class implementation of Image.h
  * Image.hpp: header file for class declaration (Interface)
  1. Constructor with (width, height, possible initial color)
  2. Destructor (especially if dynamically allocated)
  3. Accessors for width and height
  4. Mutator for a specific Color pixel (element)
  5. Accessor for a specific Color pixel (element)
  6. ...
> **Script Class**
  * Script.cpp: class implementation of Script.h
  * Script.hpp: header file for class declaration (Interface)
  1. ~~Constructor and Destructor~~
  2. ~~Initializationa and I/O~~
  3. run() : Command processor
  4. Image manipulation (keeping dimensions)
     1. Invert the colors
     2. Grayscale the colors
     3. Replace one color by other
     4. Mirror image horizontally
     5. Mirror image vertically
     6. Copy all (non-neutral) pixels from an image into another image
  5. Image manipulation (changing dimensions)
     1.  Crop the image
     2.  Rotate to the left
     3.  Rotate to the right
  6. Median Filter (advanced functionality)
> **XPM2 Class (advanced functionality)**
  * XPM2.cpp: class implementation of Color.h
  * XPM2.hpp: header file for class declaration (Interface)
  1. Opening an XPM2 file into an object of Image
  2. Save an Image object into an XPM2 file
  
## Useful Links
* Project Description and Details: [ CLICK HERE ](https://moodle.up.pt/pluginfile.php/218459/mod_resource/content/11/index.html)

Note: make sure you are **logged in** to [Moodle UP](https://moodle.up.pt/my/).

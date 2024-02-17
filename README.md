<h1 align="center">PROG - Image Manipulation</h1>

> Command-based image manipulation tool for 8-bit RGB images in PNG and XPM2 format.

<h2>Table of Contents</h2>

- [Usage](#usage)
- [Commands/Features](#commandsfeatures)
    - [Basic Operations](#basic-operations)
    - [Image Manipulation (Maintaining Size)](#image-manipulation-maintaining-size)
    - [Image Manipulation (Changing Size)](#image-manipulation-changing-size)
    - [Advanced Functionality](#advanced-functionality)


## Usage

The program runs based on the scripts passed that are written in the scripts directory. These are plaintext files that contain a series of command for the tool to parse and compute.  
The images can be loaded either from the input folder (in PNG format or XPM2) or created from scratch as blank.  
After executing the commands, the images can be stored again both in PNG or XPM2.  

## Commands/Features

#### Basic Operations

| Syntax | Description |
| --- | --- | 
| `open <filepath>` | Replace current image (if any) with image read from PNG file
| `blank <width> <height> <color>` | Replace current image (if any) with blank image
| `save <filepath>` | Save current image to PNG file

#### Image Manipulation (Maintaining Size)

| Syntax | Description |
| --- | --- | 
| `invert` | Inverts the value of each Color in the Image (255 - rgb_value)
| `to_gray_scale` | Grayscales each Color of the Image
| `replace <initial-color> <final-color>` | Replaces every Color in the Image that matches  the initial_color by the final_color
| `fill <width> <height> <x> <y> <color>` | Fills a rectangle on top of the current Image with a Color
| `h_mirror` | Mirrors the image horizontally
| `v_mirror` | Mirrors the image vertically
| `add <filepath>` | Pastes image from filename on top of current image (everything else is kept) |

#### Image Manipulation (Changing Size)

| Syntax | Description |
| --- | --- | 
| `crop <x> <y> <width> <height>` | Crop the current Image into a smaller rectangle
| `rotate_left` | Rotate the Image 90 degrees to the left
| `rotate_right` | Rotate the Image 90 degrees to the right

#### Advanced Functionality

| Syntax | Description |
| --- | --- | 
| `median_filter <n>` | Apply a median filter of n to the Image
| `xpm2_open <filepath>` | Open XPM2 files to an image object
| `xpm2_save <filepath>` | Save image object into XPM2 file

---

> Class: 1LEIC13 Group: 10  
> Final Grade: 20.0  
> Created in April 2023 for PROG (Programação) [FEUP-L.EIC009]  
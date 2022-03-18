// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <string>
#include <fstream>
#include "Image.h"
#include "Matrix.h"
#include "processing.h"
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

int main(int argc, char *argv[]){
    string oriFilename = argv[1];
    string finFilename = argv[2];
    int width = stoi(argv[3]);
    int height = stoi(argv[4]);
    if(argc<4||argc>5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
    ifstream x;
    x.open(oriFilename);
    if(!x.is_open()){
        cout << "Error opening file: " << oriFilename << endl;
        return 1;
    }
    Image* img = new Image;
    Image_init(img,x);
    
    int oriheight = Image_height(img);
    int oriwidth = Image_width(img);
    
    if((height <= 0 && height > oriheight) ||
      ( width <= 0 && width > oriwidth)){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        }
    if(height == 0){
        seam_carve_width(img,width);
    }
    else{
        seam_carve(img,width,height);
    }
    ofstream os(finFilename);
   
    if(!os.is_open()){
        cout << "Error opening file: " << finFilename << endl;
        return 1;
    }
    Image_print(img,os);
    delete img;
}

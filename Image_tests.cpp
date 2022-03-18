// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

void test_Image_init();
void test_Image_print();
void test_Image_width();
void test_Image_height();
void test_Image_get_pixel();
void test_Image_set_pixel();
void test_Image_fill();

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

void test_Image_init(){
    //Pixel red = {255, 0, 0};
    //Pixel green = {0, 255, 0};
    Image *img = new Image;
    Image_init(img, 3, 4);
    ASSERT_EQUAL(Image_width(img),3);
    ASSERT_EQUAL(Image_height(img),4);
    delete img;
}
/*void test_Image_init_2(){
    Image *img = new Image;
    Image_init(img, 3, 4);
    
}*/
void test_Image_print(){
    Image *img = new Image;

    // A very poorly behaved input PPM.
    string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
    std::istringstream ss_input(input);
    Image_init(img, ss_input);

    // Should be well behaved when you print it though!
    string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
    std::ostringstream ss_output;
    Image_print(img, ss_output);
    string actual = ss_output.str();
    std::cout << actual << std::endl;
    ASSERT_EQUAL(actual, output_correct);

    
    string input2 = "P3 0 0\t255 0 0 0\n";
    std::istringstream ss_input2(input2);
    Image_init(img, ss_input2);

    // Should be well behaved when you print it though!
    string output_correct2 = "P3\n0 0\n255\n0 0 0\n";
    std::ostringstream ss_output2;
    Image_print(img, ss_output2);
    string actual2 = ss_output2.str();
    std::cout << actual2 << std::endl;
    ASSERT_EQUAL(actual2, output_correct2);
    
    delete img;
}
void test_Image_width(){
    Image* img = new Image;
    Image_init(img, 0, 0);
    ASSERT_EQUAL(Image_width(img),0);
    
    Image_init(img, 1, 1);
    ASSERT_EQUAL(Image_width(img),1);
    
    Image_init(img, 1, 500);
    ASSERT_EQUAL(Image_width(img),1);
    
    Image_init(img, 500, 1);
    ASSERT_EQUAL(Image_width(img),500);
    
    Image_init(img, 500, 500);
    ASSERT_EQUAL(Image_width(img),500);
    
    delete img;
}
void test_Image_height(){
    Image* img = new Image;
    Image_init(img, 0, 0);
    ASSERT_EQUAL(Image_height(img),0);
    
    Image_init(img, 1, 1);
    ASSERT_EQUAL(Image_height(img),1);
    
    Image_init(img, 1, 500);
    ASSERT_EQUAL(Image_height(img),500);
    
    Image_init(img, 500, 1);
    ASSERT_EQUAL(Image_height(img),1);
    
    Image_init(img, 500, 500);
    ASSERT_EQUAL(Image_height(img),500);
    
    delete img;
}

void test_Image_get_pixel(){
    cout << "test_Image_get_pixel" << endl;
    Pixel red = {255, 0, 0};
    Pixel green = {0, 255, 0};
    Pixel color1{0,0,0};
    Pixel color2{0,255,255};
    Pixel color3{255,255,255};
    
    Image *img = new Image;
    Image_init(img, 3, 4);
    
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 4, 3, green);
    Image_set_pixel(img, 1, 1, color1);
    Image_set_pixel(img, 0, 1, color2);
    Image_set_pixel(img, 3, 3, color3);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 4, 3), green));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), color1));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), color2));
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 3), color3));
    
    delete img;
}

void test_Image_set_pixel(){
    cout << "test_Image_set_pixel" << endl;
    Pixel color1{0,0,0};
    Pixel color2{0,255,255};
    Pixel color3{255,255,255};
    Image* img = new Image;
    
    Image_init(img, 0, 0);
    Image_set_pixel(img, 0, 0, color1);
    //Pixel_equal(Image_get_pixel(img, 0, 0), color1));
    Pixel_equal(Image_get_pixel(img, 0, 0), color1);
    
    Image_init(img, 1, 1);
    Image_set_pixel(img, 1, 0, color2);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 0), color2));
    
    Image_init(img, 10, 10);
    Image_set_pixel(img, 10, 10, color3);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 10, 10), color3));
    
    Image_init(img, 1, 500);
    Image_set_pixel(img, 1, 500, color1);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 500), color1));
    Image_set_pixel(img, 1, 0, color2);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 0), color2));
    
    Image_init(img, 500, 500);
    Image_set_pixel(img, 0, 0, color1);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), color1));
    Image_set_pixel(img, 10, 0, color2);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 10, 0), color2));
    Image_set_pixel(img, 500, 500, color3);
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 500, 500), color3));
    
    delete img;
}

void test_Image_fill(){
    cout << "test_Image_fill" << endl;
    Pixel color1{0,0,0};
    Pixel color2{0,255,255};
    Pixel color3{255,255,255};
    Image* img = new Image;
    
    Image_init(img, 0, 0);
    Image_fill(img, color1);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), color1));
        }
    }
    
    Image_init(img, 1, 1);
    Image_fill(img, color2);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), color2));
        }
    }
    
    Image_init(img, 1, 500);
    Image_fill(img, color3);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 500), color3));
        }
    }
    
    Image_init(img, 500, 1);
    Image_fill(img, color3);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 500, 1), color3));
        }
    }
    
    Image_init(img, 500, 500);
    Image_fill(img, color1);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 500, 500), color1));
        }
    }
    
    delete img;
}
 
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

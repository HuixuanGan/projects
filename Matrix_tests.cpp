// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;

void test_Matrix_init();
void test_Matrix_print();
void test_Matrix_width();
void test_Matrix_height();
void test_Matrix_row();
void test_Matrix_column();
void test_Matrix_at();
void test_const_Matrix_at();
void test_Matrix_fill();
void test_Matrix_fill_border();
void test_Matrix_max();
void test_Matrix_column_of_min_value_in_row();
void test_Matrix_min_value_in_row();
// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

void test_Matrix_init(){
    cout << "test_Matrix_init" << endl;
    
    const int width = 10;
    const int height = 15;
    Matrix *mat = new Matrix;
    Matrix_init(mat, 10, 15);
    
    for(int r = 0; r < height; ++r){
      for(int c = 0; c < width; ++c){
        ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
      }
    }
    delete mat;
}
void test_Matrix_print(){
    cout << "test_Matrix_print" << endl;
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 2);
    *Matrix_at(mat, 0, 0) = 0;
    *Matrix_at(mat, 0, 1) = 1;
    *Matrix_at(mat, 0, 2) = 2;
    *Matrix_at(mat, 1, 0) = 12;
    *Matrix_at(mat, 1, 1) = 88;
    *Matrix_at(mat, 1, 1) = 100;
    ostringstream expected;
    expected << "3 2\n"
             << "0 1 2\n"
             << "12 88 100\n";
    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    delete mat;
}
void test_Matrix_width(){
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 0, 0);
    ASSERT_EQUAL(Matrix_width(mat),0);
    
    Matrix_init(mat, 1, 1);
    ASSERT_EQUAL(Matrix_width(mat),1);
    
    Matrix_init(mat, 10, 10);
    ASSERT_EQUAL(Matrix_width(mat),10);
    
    Matrix_init(mat, 1, 500);
    ASSERT_EQUAL(Matrix_width(mat),1);
    
    Matrix_init(mat, 500, 1);
    ASSERT_EQUAL(Matrix_width(mat),500);
    
    Matrix_init(mat, 500, 500);
    ASSERT_EQUAL(Matrix_width(mat),500);
    
    delete mat;
}
void test_Matrix_height(){
    Matrix *mat = new Matrix;
    
    Matrix_init(mat, 0, 0);
    ASSERT_EQUAL(Matrix_height(mat),0);
    
    Matrix_init(mat, 1, 1);
    ASSERT_EQUAL(Matrix_height(mat),1);
    
    Matrix_init(mat, 10, 10);
    ASSERT_EQUAL(Matrix_height(mat),10);
    
    Matrix_init(mat, 1, 500);
    ASSERT_EQUAL(Matrix_height(mat),500);
    
    Matrix_init(mat, 500, 1);
    ASSERT_EQUAL(Matrix_height(mat),1);
    
    Matrix_init(mat, 500, 500);
    ASSERT_EQUAL(Matrix_height(mat),500);
    
    delete mat;
}
void test_Matrix_row(){
    
    const int width = 10;
    const int height = 15;
    Matrix *mat = new Matrix;
    Matrix_init(mat, 10, 15);
    int *ptr = Matrix_at(mat, 0, 0);
    for(int r = 0; r < height; ++r){
      for(int c = 0; c < width; ++c){
          ptr = Matrix_at(mat, r, c);
          ASSERT_EQUAL(Matrix_row(mat, ptr), r);
      }
    }
    delete mat;
}
void test_Matrix_column(){
    const int width = 10;
    const int height = 15;
    Matrix *mat = new Matrix;
    Matrix_init(mat, 10, 15);
    int *ptr = Matrix_at(mat, 0, 0);
    for(int r = 0; r < height; ++r){
      for(int c = 0; c < width; ++c){
          ptr = Matrix_at(mat, r, c);
          ASSERT_EQUAL(Matrix_row(mat, ptr), c);
      }
    }
    delete mat;
}
void test_Matrix_at(){
    Matrix *mat = new Matrix;
    const int width = 15;
    const int height = 51;
    const int value = 42;
    Matrix_init(mat, 15, 51);
    Matrix_fill(mat, value);

    for(int r = 0; r < height; ++r){
      for(int c = 0; c < width; ++c){
        ASSERT_EQUAL(*Matrix_at(mat, r, c), mat[r*c]);// c*r???
      }
    }

    delete mat;
}
void test_const_Matrix_at(){
    Matrix *mat = new Matrix;
    const int width = 15;
    const int height = 51;
    const int value = 42;
    Matrix_init(mat, 15, 51);
    Matrix_fill(mat, value);

    for(int r = 0; r < height; ++r){
      for(int c = 0; c < width; ++c){
        ASSERT_EQUAL(*Matrix_at(mat, r, c), mat[r*c]);
      }
    }

    delete mat;
}
void test_Matrix_fill(){
    Matrix *mat = new Matrix;
    const int width = 15;
    const int height = 51;
    const int value = 42;
    Matrix_init(mat, 15, 51);
    Matrix_fill(mat, value);

    for(int r = 0; r < height; ++r){
      for(int c = 0; c < width; ++c){
        ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
      }
    }

    delete mat;
}
void test_Matrix_fill_border(){
    Matrix *mat = new Matrix;
    Matrix_init(mat, 10, 15);
    Matrix_fill_border(mat, 30);
    
    for (int i = 0; i < mat->height; i++) {
        if (i == 0 || i == (mat->height)-1) {
            for (int j = 0; j < mat->width; j++) {
                ASSERT_EQUAL(*Matrix_at(mat, i, j), 30);
            }
        }
        else {
            for (int j = 0; j < mat->width; j++) {
                if (j == 0 || j == (mat->width)-1) {
                    ASSERT_EQUAL(*Matrix_at(mat, i, j), 30);
                }
            }
        }
    }
    delete mat;
}
void test_Matrix_max(){
    Matrix *mat = new Matrix;
    Matrix_init(mat, 10, 15);
    for (int i = 0; i < mat->height; i++) {
        for (int j = 0; j < mat->width; j++) {
            *Matrix_at(mat, i, j) = i+j;
        }
    }
    ASSERT_EQUAL(Matrix_max(mat), 23);
    delete mat;
}
void test_Matrix_column_of_min_value_in_row(){
    Matrix *mat = new Matrix;
    Matrix_init(mat, 5, 2);
    for (int r = 0; r < mat->height; r++) {
        for (int c = 0; c < mat->width; c++) {
            *Matrix_at(mat, r, c) = r+c;
            if (c > 0) {
                ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, r, c-1, c), c-1);
            }
            ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, r, 0, c), 0);
        }
    }
    for (int r = 0; r < mat->height; r++) {
        for (int c = 0; c < mat->width; c++) {
            int j = 25 - c;
            int i = 20 - r;
            *Matrix_at(mat, r, c) = i+j;
            if (c > 0) {
                ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, r, c-1, c), c);
            }
            ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, r, 0, c), c);
        }
    }
    *Matrix_at(mat, 0, 0) = 1;
    *Matrix_at(mat, 0, 1) = 2;
    *Matrix_at(mat, 0, 2) = 3;
    *Matrix_at(mat, 0, 3) = 2;
    *Matrix_at(mat, 0, 4) = -1;
    *Matrix_at(mat, 1, 0) = 2;
    *Matrix_at(mat, 1, 1) = 2;
    *Matrix_at(mat, 1, 2) = 1;
    *Matrix_at(mat, 1, 3) = 1;
    *Matrix_at(mat, 1, 4) = 2;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 4), 4);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 1, 3), 1);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 4), 2);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 3, 4), 3);
    delete mat;
}
void test_Matrix_min_value_in_row(){
    Matrix *mat = new Matrix;
    Matrix_init(mat, 10, 15);
    for (int r = 0; r < mat->height; r++) {
        for (int c = 0; c < mat->width; c++) {
            int j = 14 - c;
            int i = 9 - r;
            *Matrix_at(mat, r, c) = i+j;
            if (c > 0) {
                ASSERT_EQUAL(Matrix_min_value_in_row(mat, r, c-1, c), c+r);
            }
            ASSERT_EQUAL(Matrix_min_value_in_row(mat, r, 0, c), c+r);
        }
        
    }
    for (int r = 0; r < mat->height; r++) {
        for (int c = 0; c < mat->width; c++) {
            *Matrix_at(mat, r, c) = r+c;
            if (c > 0) {
                ASSERT_EQUAL(Matrix_min_value_in_row(mat, r, c-1, c), c-1+r);
            }
            ASSERT_EQUAL(Matrix_min_value_in_row(mat, r, 0, c), r);
        }
    }
    Matrix_init(mat, 5, 2);
    *Matrix_at(mat, 0, 0) = 1;
    *Matrix_at(mat, 0, 1) = 2;
    *Matrix_at(mat, 0, 2) = 3;
    *Matrix_at(mat, 0, 3) = 2;
    *Matrix_at(mat, 0, 4) = -1;
    *Matrix_at(mat, 1, 0) = 2;
    *Matrix_at(mat, 1, 1) = 2;
    *Matrix_at(mat, 1, 2) = 1;
    *Matrix_at(mat, 1, 3) = 1;
    *Matrix_at(mat, 1, 4) = 2;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4), -1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 1, 3), 2);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 4), 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 3, 4), 1);
    delete mat;
}
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

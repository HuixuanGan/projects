/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;
const double epsilon = 0.001;

// Add prototypes for you test functions here.
void test_sum_small_data_set();
void test_summarize() ;
void test_count() ;
void test_count() ;
void test_sum();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev() ;
void test_percentile();

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

void  test_summarize() {
    vector<double> data ={1,1,2,3,4,5};
 cout << " test_summarize" << endl;
        vector<vector<double>> correct{{1,2},{2,1},{3,1},{4,1},{5,1}};
        if (correct == summarize(data)) {
            cout << "equal" << endl;
          }
        else {
            cout << "not equal" << endl;
        }
}
void test_count() {
    vector<double> data = {1,2,3,4,5};
cout << "test_count" << endl;
        assert(count(data) == 5);
cout << "PASS!" << endl;
}
void test_sum(){
    vector<double> data = {1,2,3,4,5};
cout << "test_sum" << endl;
        assert(sum(data) == 15);
cout << "PASS!" << endl;
}
void test_mean() {
    vector<double>data = {1,2,3,4,5};
cout << "test_mean1" << endl;
        assert(mean(data) == 3);
cout << "PASS!" << endl;
    vector<double>data1 = {1,2,3,4,5,6,7,8};
cout << "test_mean2" << endl;
        assert(mean(data1) == 4.5);
cout << "PASS!" << endl;
}
void test_median(){
    vector<double> data1 ={1,2,3,4,5};
cout << "test_median1" << endl;
        assert(median(data1) == 3);
cout << "PASS!" << endl;
    vector<double> data2 ={1,2,3,4};
cout << "test_median2" << endl;
        assert(median(data2) == 2.5);
cout << "PASS!" << endl;
}
void test_mode() {
    vector<double> data1 = {1,1,2,3,4,5};
cout << "test_mode1" << endl;
        assert(mode(data1)==1);
cout << "PASS!" << endl;
    vector<double> data2 = {1,1,2,3,5,4,2};
cout << "test_mode2" << endl;
        assert(mode(data2)==1);
cout << "PASS!" << endl;
}
void test_min(){
    vector<double> data = {1,2,3,4,5};
cout << "test_min" << endl;
         assert(min(data) == 1);
cout << "PASS!" << endl;
}
void test_max() {
    vector<double> data = {1,2,3,4,5};
cout << "test_max" << endl;
          assert(max(data) == 5);
cout << "PASS!" << endl;
}
void test_stdev() {
    vector<double> data = {1,2,3,4,5};
cout << "test_stdev" << endl;
        if (fabs(stdev(data) - 1.5811) < epsilon) {
           cout << "equal" << endl;
         }
        else {
           cout << "not equal" << endl;
    }
}
void test_percentile(){
    vector<double> data1 = {1,2,3,4,5,6};
        int p1 = 25;
cout << "test_percentile1" << endl;
        assert(percentile(data1,p1) == 1);
cout << "PASS!" << endl;
        int p2;
        p2 = 100;
cout << "test_percentile2" << endl;
        assert(percentile(data1,p2) == 5);
cout << "PASS!" << endl;
        int p3;
        p3 = 0;
cout << "test_percentile3" << endl;
    assert(percentile(data1,p3) == 1);
cout << "PASS!" << endl;
}
              
int main(){
        test_sum_small_data_set();
        test_summarize();
        test_count();
        test_sum();
        test_mean();
        test_median();
        test_mode();
        test_min();
        test_max();
        test_stdev();
        test_percentile();
      return 0;
}

    

// Add the test function implementations here.

//
//  main.cpp
//  p1-stats
//
//  Created by Skylar Gan on 1/14/22.
//

#include <stdio.h>
// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
using namespace std;
int main() {
    cout << "enter a filename" << endl;
    std::string name;
    std::string col;
    cin >> name;
    cout << "enter a column name" << endl;
    cin >> col;
    vector<double> v = extract_column(name,col);
    cout << "reading column " << col << " from " << name << endl << endl;
    cout << "Summary (value: frequency)" << endl;
    vector<vector<double>>summar = summarize(v);
    for (size_t i = 0; i < summar.size(); i += 1) {
        cout << summar[i][0] << ": "<< summar[i][1] << "\n";
      }
    cout << endl;
    cout << "count = ";
    cout << count(v);
    cout << endl;
    cout << "sum = ";
    cout << sum(v);
    cout << endl;
    cout << "mean = ";
    cout << mean(v);
    cout << endl;
    cout << "stdev = ";
    cout << stdev(v);
    cout << endl;
    cout << "median = ";
    cout << median(v);
    cout << endl;
    cout << "mode = ";
    cout << mode(v);
    cout << endl;
    cout << "min = ";
    cout << min(v);
    cout << endl;
    cout << "max = ";
    cout << max(v);
    cout << endl;
    cout << "  " << 0 << "th percentile = ";
    cout << percentile(v,0);
    cout << endl;
    cout << " " << 25 << "th percentile = ";
    cout << percentile(v,25);
    cout << endl;
    cout << " " << 50 << "th percentile = ";
    cout << percentile(v,50);
    cout << endl;
    cout << " " << 75 << "th percentile = ";
    cout << percentile(v,75);
    cout << endl;
    cout << 100 << "th percentile = ";
    cout << percentile(v,100);
    cout << endl;
}

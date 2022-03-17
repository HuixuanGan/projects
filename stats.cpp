//
//  stats.cpp
//  p1-stats
//
//  Created by Skylar Gan on 1/14/22.
//
#include <stdio.h>
#include "p1_library.h"
// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
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
vector<vector<double> > summarize(vector<double> v) {
    vector<vector<double>> outside;
    double time = 1;
    sort(v);
    for (int i = 1; i < (int)v.size(); i++) {
        if (v[i] != v[i - 1]) {
        vector<double> temp;
            temp.push_back(v[i - 1]);
            temp.push_back(time);
            time = 1;
            outside.push_back(temp);
            }
        else {
            time++;
        }
        if (i == (int)v.size() - 1) {
            vector<double> temp;
            temp.push_back(v[i]);
            temp.push_back(time);
            outside.push_back(temp);
        }
        
    }
    return outside;
}

int count(vector<double> v) {
    int total = static_cast<int>(v.size());
    return total;
}
double sum(vector<double> v) {
      double total = 0;
      for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        total += v[i];
      }
      return total;
}
double mean(vector<double> v) {
    return sum(v)/count(v);
}
double median(vector<double> v) {
    sort(v);
    double m = static_cast<double>(v.size())/2;
    int n = static_cast<int>(v.size())/2;
    if (static_cast<double>(n) == m){
        return (v[n-1]+v[n])/2;
    }
    else{
        return v[static_cast<double>(n)];
    }
}
double mode(vector<double> v) {
    double modes = v[0];
    double time = 0;
    vector<vector<double>> summar = summarize(v);
    for (int i = 0; i < static_cast<int>(summar.size()); i++) {
        if (time < summar[i][1]) {
        modes = summar[i][0];
        time = summar[i][1];
        }
    }
    return modes;
}
double min(vector<double> v) {
    double min = 10000;
    for (int i = 0; i< static_cast<int>(v.size()); ++i){
        if (v.at(i)<min){
        min = v.at(i);
        }
    }
    return min;
}
double max(vector<double> v) {
    double max = 0;
    for (int i = 0; i< static_cast<int>(v.size()); ++i){
        if (v.at(i)>max){
        max = v.at(i);
    }
}
    return max;
}

double stdev(vector<double> v) {
    double s = 0;
    for (int i = 0; i< static_cast<int>(v.size()); ++i){
        s = s + pow((mean(v)-v.at(i)),2);
        }
    return sqrt(s/(static_cast<int>(v.size())-1));
}

double percentile(vector<double> v, double p) {
    sort(v);
    double temp;
    temp = p/100 * (count(v)-1)+1;
    double integer = 0;
    double decimal = 0;
    decimal = modf(temp,&integer);
    if(p!=100){
    return (v.at(integer-1)+decimal*(v.at(integer)-v.at(integer-1)));
    }
    else {
    return v[v.size() - 1];
    }
}


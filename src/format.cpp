/***************************************\
| Spectral Clustering v1.0 (2018/10/12) |
|                                       |
| Copyright (c) 2015-2018 Motomu Matsui |
|    Distributed under the GNU GPL      |
|                                       |
|    Matsui M and Iwasaki W (2018)      |
|    Systematic Biology, xx:xx-xx.      |
|                                       |
|    http://gs.bs.s.u-tokyo.ac.jp/      |
\***************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

void readMAT(ifstream& ifs, double* (&W), int& size){
  
  int x = 0; // x
  size  = 0; // size of matrix

  //Reading lines
  string line, chr;
  while(getline(ifs, line)){
    
    if(x == 0){
      istringstream stream(line);
      while(getline(stream, chr, '\t')){
	size ++;
      }
      W = new double[size*size](); // Sequence similarity matrix
    }

    //Split lines
    istringstream stream(line);
    int y = 0; // y
    while(getline(stream, chr, '\t')){
      W[x*size+y] = stod(chr);
      y ++;
    }
    x ++;
  }  
}

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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <regex>
#include <unistd.h>
#include <random>   
#include <functional>
#include <vector>
#include <tuple>

using namespace std;

/// messages.cpp
extern void print_banner();
extern void print_usage(char*&);

//sc.cpp (spectral clustering)
extern tuple<vector<int>,vector<int>> SC(double* const&, int const&);

// format.cpp
extern void readMAT(ifstream&, double*&, int&);

int main(int argc, char* argv[]){

  /*/Getopt/*/
  int ep_num  = 0; // -e

  opterr = 0; // default error messages -> OFF

  int opt;
  regex renum(R"(^[\d\.]+$)"); // -e/-r option requires an integer/flout number
  while ((opt = getopt(argc, argv, "shve:r:")) != -1){
    if(opt == 'e'){ // OK! (./gs -e 100 IN.fst)
      if(regex_match(optarg, renum)){
        ep_num = atoi(optarg);
      }
      else{ // NG! (./gs -e hundred IN.fst)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << "Option -e requires an integer argument.\n" << endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
    }
    else if (opt == '?'){
      if(optopt == 'e'){ // NG! (./gs IN.fst -e)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << "Option -e requires an integer argument.\n" << endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
      else{ // NG! (./gs -Z)
        /*PRINT*/ print_banner();
        /*PRINT*/ cerr << argv[0] << ": invalid option\n" <<  endl;
        /*PRINT*/ print_usage(argv[0]);
        return -1;
      }
    }
  }

  /*/Input file/*/
  string input = "";
  if(optind < argc){ // OK!
    input = argv[optind];
  }
  else{ // NG!
    /*PRINT*/ print_banner();
    /*PRINT*/ cerr << argv[0] << " requires an input file (matrix).\n" << endl;
    /*PRINT*/ print_usage(argv[0]);
    return -1;
  }

  /*/Variables/*/
  double* W;     // Distance matrix
  int size;      // Row size of W (W is a synmetry matrix)

  /*/File I/O/*/
  auto original_file = string(input);
  ifstream ifs1(original_file); // Matrix file (original)
  if(ifs1.fail()){
    /*PRINT*/ cerr << "\nCannot access " << original_file << "!" << endl;
    return -1;
  }

  /*/Parsing matrix file/*/
  readMAT(ifs1, W, size); 
    // ifs1: INPUT (original matrix file)
    // W:    OUTPUT (matrix)
    // size: # of factors = row size of sequence similarity matrix

  /*/Spectral Clustering/*/
  vector<int> a;
  vector<int> b;
  tie(a,b) = SC(W, size);
    // W: INPUT (sequence similarity matrix)
    // size: # of factors = row size of sequence similarity matrix

  stringstream ss;
  ss.str("");
  sort(a.begin(), a.end());
  for(int n : a){
    ss << n+1 << ",";
  }
  auto sa = ss.str();

  ss.str("");
  sort(b.begin(), b.end());
  for(int n : b){
    ss << n+1 << ",";
  }
  auto sb = ss.str();

  sa.erase(--sa.end());
  sb.erase(--sb.end());

  cout << "A:" << " " << sa << endl;
  cout << "B:" << " " << sb << endl;

  //Free
  delete[] W;
  
  return 0;
}

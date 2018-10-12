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

#include <vector>
#include <algorithm>
#include <cmath> 
#include <functional>
#include <utility>
#include <map>
#include <iterator>

using namespace std;

//Best cut position
typedef pair<double, int> P;
bool comp(const P &a, const P &b){
  return a.first > b.first;
}

void CUT(double* const (&z), int const col, double* const (&D), int*& qi, int& cut, int const N, vector<int>& a, vector<int>& b){
  vector<P> pairs(N);
  double* qs = new double[N]();

  //Inner product: <eigenvector,D>
  for(int p = 0; p < N; p++){
    pairs[p] = make_pair(z[col+p*N]*D[p], p);
  }

  //Sorting values
  sort(pairs.begin(), pairs.end(), comp);
  for(int p = 0; p < N; p++){
    qs[p] = pairs[p].first;
    qi[p] = pairs[p].second;
  }

  cut = 0;
  double best = 0;
  for(int n = 0; n < N-1; n++){
    auto def = abs(qs[n] - qs[n+1]);
    if(def > best){
      cut  = n;
      best = def;
    }
  }

  for(int p = 0; p <=cut; p++){
    a.push_back(qi[p]);
  }
  for(int p = cut+1; p < N; p++){
    b.push_back(qi[p]);
  }

  delete[] qs;
}

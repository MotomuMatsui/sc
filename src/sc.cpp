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

#include <algorithm>
#include <vector>
#include <tuple>
#include <cmath> 

using namespace std;

//eigen.cpp (Wrapper function of LAPACKE/CBLAS package)
extern int eigen_lapack(double*&, double*&, int);

//sc_functions.cpp (Split one cluster into two subclusters)
extern void CUT(double* const&, int const, double* const&, int*&, int&, int const, vector<int>&, vector<int>&);

tuple<vector<int>,vector<int>> SC(double* const (&W), int const& N){

  double* D = new double[N]();
  double* A = new double[N*N]();  

  //D
  for(int r = 0; r < N; r++){
    D[r] = 0.0;
    for(int c = 0; c < N; c++){
      D[r] += W[r*N+c];
    }
    D[r] = 1/sqrt(D[r]);
  }

  //A = E-D*W*D
  for(int x = 0; x < N; x++){
    for(int y = 0; y < x; y++){
      auto p = x*N+y;
      A[p] = -D[x]*D[y]*W[p];
    }
    auto p = x*N+x;
    A[p] = 1-D[x]*D[x]*W[p];
  }

  //Eigenvalue analysis
  double* z = new double[N*N]();     //z: eigenvector
  auto info = eigen_lapack(A, z, N); //LAPACK!
  if(info != 0){}                    //Error occurs if info>0

  //Split submatrix into two parts according to the result of spectral clustering
  int* qi = new int[N]();
  int cut = 0;
  vector<int> a, b;
  CUT(z, 0, D, qi, cut, N, a, b);
  
  //free
  delete[] D;
  delete[] A;
  delete[] z;
  delete[] qi;

  return forward_as_tuple(a,b);
}

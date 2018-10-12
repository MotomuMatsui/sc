# sc

`sc` is a software to conduct the naiive Spectral clustering (Shi and Malik, IEEE Trans. Pattern Analysis and Machine Intelligence, 2000.    
`sc` is open-source software (GPL v3.0) inplemented in C++ for <strong>Linux</strong>, <strong>Mac (macOS)</strong> and <strong>Windows (Cygwin)</strong>. 

Reference: Matsui and Iwasaki, ???, 2018  
Online tool: [GS analysis server](http://gs.bs.s.u-tokyo.ac.jp/)  
Our Laboratory: [Iwasaki Lab](http://iwasakilab.bs.s.u-tokyo.ac.jp/eindex.html)  

[![Build Status](https://travis-ci.org/MotomuMatsui/sc.svg?branch=master)](https://travis-ci.org/MotomuMatsui/sc)
[![Ubuntu](https://img.shields.io/badge/Linux-Ubuntu-green.svg)](https://www.ubuntu.com/)
[![CentOS](https://img.shields.io/badge/Linux-CentOS-green.svg)](https://www.centos.org/)
[![Mac](https://img.shields.io/badge/Mac-macOS-green.svg)](https://www.apple.com/macos/)
[![Windows](https://img.shields.io/badge/Windows-Cygwin-green.svg)](https://www.cygwin.com/)
[![Language](https://img.shields.io/badge/C%2B%2B-5.0%2B-green.svg)](https://gcc.gnu.org/)
[![LAPACK](https://img.shields.io/badge/LAPACK%2FBLAS-3.7%2B-green.svg)](http://www.netlib.org/lapack/)
[![GPL License](https://img.shields.io/badge/license-GPL-blue.svg)](LICENSE)

## History
version 1.0 (2018/10/12)   
  - Implemented in C++    

## Installation

### 0. Requirements

- [GNU GCC compiler](https://gcc.gnu.org/) (5.0+) is required to compile `sc`    

### 1. Compile from source code:

````
    $ git clone https://github.com/MotomuMatsui/sc
    $ cd sc
    $ make
````

## Usage
To get on-line help:
```
    $ ./sc -h
```

The following command enables you to calculate Spectral Clustering    
```
    $ ./sc [arguments] input
```    

## License
This software is distributed under the GNU GPL, see [LICENSE](LICENSE)   
Copyright &copy; 2018, Motomu Matsui

## Author
[Motomu Matsui](https://sites.google.com/site/motomumatsui/)

## Reference
Motomu Matsui and Wataru Iwasaki. ??? (2018)

## Acknowledgements
This package includes the LAPACKE/CBLAS (Univ. of Tennessee; Univ. of California, Berkeley; Univ. of Colorado Denver; and NAG Ltd.). The authors give special thanks to them. You can get the detailed information from http://www.netlib.org/lapack/.

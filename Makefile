#CXX   := /usr/local/bin/g++-7

CXX   := g++
TAR   := tar xzf
MKDIR := mkdir -p
CP    := cp
CMAKE := cmake

VPATH := src
INC   := -Ilib
LIB   := -Llib -llapacke -llapack -lcblas -lrefblas -lgfortran -lm

CXXFLAGS := -O3
CXXFLAGS += -std=c++11
CXXFLAGS += -march=native
CXXFLAGS += -fno-exceptions
CXXFLAGS += -Wall

OBJECTS  := messages.o
OBJECTS  += format.o
OBJECTS  += sc_functions.o
OBJECTS  += sc.o
OBJECTS  += main.o

FILE  := lapack-3.7.1/make.inc
EXIST := $(shell ls | grep ${FILE})

.PHONY: all
all: lapack sc clean

.PHONY: lapack
lapack:
	$(TAR) lapack-3.7.1.tar.gz 
	$(MKDIR) lib
    ifneq (${EXIST}, ${FILE})
	$(CP) lapack-3.7.1/make.inc.example lapack-3.7.1/make.inc
    endif
	$(MAKE) -C lapack-3.7.1 blaslib
	$(MAKE) -C lapack-3.7.1 cblaslib
	$(MAKE) -C lapack-3.7.1 lapacklib
	$(MAKE) -C lapack-3.7.1 lapackelib
	$(CP) -f lapack-3.7.1/*.a lib
	$(CP) -f lapack-3.7.1/CBLAS/include/*.h lib
	$(CP) -f lapack-3.7.1/LAPACKE/include/*.h lib

sc: eigen.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB)

eigen.o: eigen.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $<

$(OBJECTS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) eigen.o $(OBJECTS)

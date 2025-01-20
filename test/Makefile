CXX := g++
CXXFLAGS := -I../vendor/doctest

.PHONY: all test bintree_test bintreeio_test tree_test

all: test

test: bintree_test bintreeio_test tree_test

tree_test: tree
	@./tree

bintreeio_test: bintreeio
	@./bintreeio

bintree_test: bintree
	@./bintree

bintree: bintree.cc
	$(CXX) $(CXXFLAGS) -o bintree bintree.cc 

bintreeio: bintree-io.cc
	$(CXX) $(CXXFLAGS) -o bintreeio bintree-io.cc

tree: tree.cc
	$(CXX) $(CXXFLAGS) -o tree tree.cc


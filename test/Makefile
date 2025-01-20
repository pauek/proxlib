CXX := g++
CXXFLAGS := -I../vendor/doctest

.PHONY: all test bintree_test bintree-io_test tree_test tree-io_test

all: test

test: bintree_test bintree-io_test tree_test tree-io_test


bintree-io_test: bintree-io
	@./bintree-io

bintree_test: bintree
	@./bintree

tree_test: tree
	@./tree

tree-io_test: tree-io
	@./tree-io


bintree: bintree.cc ../bintree.hh
	$(CXX) $(CXXFLAGS) -o bintree bintree.cc 

bintree-io: bintree-io.cc ../bintree.hh ../bintree-io.hh
	$(CXX) $(CXXFLAGS) -o bintree-io bintree-io.cc

tree: tree.cc ../tree.hh
	$(CXX) $(CXXFLAGS) -o tree tree.cc

tree-io: tree-io.cc ../tree.hh ../tree-io.hh
	$(CXX) $(CXXFLAGS) -o tree-io tree-io.cc


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../bintree-io.hh"
#include <doctest/doctest.h>
#include "../bintree.hh"
using namespace pro2;

#include <sstream>
using namespace std;

TEST_CASE("Write empty BinTree") {
	ostringstream	   oss;
	BinTreeWriter<int> writer(oss);
	writer.write(BinTree<int>());
	CHECK(oss.str() == "#\n");
}

TEST_CASE("Write BinTree with left branch") {
	ostringstream	   oss;
	BinTreeWriter<int> writer(oss);
	writer.write(BinTree<int>(1, BinTree<int>(2), BinTree<int>()));
	CHECK(oss.str() ==
		  "1\n"
		  "|-- 2\n"
		  "'-- #\n");
}

TEST_CASE("Write BinTree with right branch") {
	ostringstream		oss;
	BinTreeWriter<char> writer(oss);
	writer.write(BinTree<char>('a', BinTree<char>(), BinTree<char>('b')));
	CHECK(oss.str() ==
		  "a\n"
		  "|-- #\n"
		  "'-- b\n");
}

TEST_CASE("Write BinTree with left and right branch") {
	ostringstream		  oss;
	BinTreeWriter<string> writer(oss);
	writer.write(BinTree<string>("ha", BinTree<string>("he"), BinTree<string>("ho")));
	CHECK(oss.str() ==
		  "ha\n"
		  "|-- he\n"
		  "'-- ho\n");
}

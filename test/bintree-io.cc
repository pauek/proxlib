#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../bintree-io.hh"
#include <doctest/doctest.h>
#include "../bintree.hh"
using namespace pro2;

#include <sstream>
using namespace std;

TEST_CASE("Write empty BinTree") {
	ostringstream oss;
	oss << BinTree<int>();
	CHECK(oss.str() == "#\n");
}

TEST_CASE("Write BinTree with left branch") {
	BinTree<int>  t1(1, BinTree<int>(2), BinTree<int>());
	ostringstream oss;
	oss << t1;
	CHECK(oss.str() ==
		  "1\n"
		  "|-- 2\n"
		  "'-- #\n");
}

TEST_CASE("Write BinTree with right branch") {
	BinTree<char> ta('a', BinTree<char>(), BinTree<char>('b'));
	ostringstream oss;
	oss << ta;
	CHECK(oss.str() ==
		  "a\n"
		  "|-- #\n"
		  "'-- b\n");
}

TEST_CASE("Write BinTree with left and right branch") {
	BinTree<string> tha("ha", BinTree<string>("he"), BinTree<string>("ho"));
	ostringstream	oss;
	oss << tha;
	CHECK(oss.str() ==
		  "ha\n"
		  "|-- he\n"
		  "'-- ho\n");
}

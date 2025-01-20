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
	writer.write(Tree<int>());
	CHECK(oss.str() == "#\n");
}

TEST_CASE("Write BinTree with left branch") {
	ostringstream	   oss;
	BinTreeWriter<int> writer(oss);
	writer.write(Tree<int>(1, Tree<int>(2), Tree<int>()));
	CHECK(oss.str() ==
		  "1\n"
		  "|-- 2\n"
		  "'-- #\n");
}

TEST_CASE("Write BinTree with right branch") {
	ostringstream		oss;
	BinTreeWriter<char> writer(oss);
	writer.write(Tree<char>('a', Tree<char>(), Tree<char>('b')));
	CHECK(oss.str() ==
		  "a\n"
		  "|-- #\n"
		  "'-- b\n");
}

TEST_CASE("Write BinTree with left and right branch") {
	ostringstream		  oss;
	BinTreeWriter<string> writer(oss);
	writer.write(Tree<string>("ha", Tree<string>("he"), Tree<string>("ho")));
	CHECK(oss.str() ==
		  "ha\n"
		  "|-- he\n"
		  "'-- ho\n");
}

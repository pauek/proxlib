#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tree-io.hh"
#include <doctest/doctest.h>
#include "../tree.hh"
using namespace pro2;

#include <sstream>
using namespace std;

TEST_CASE("Write empty Tree") {
	Tree<int> t;

	ostringstream oss;
	oss << t;

	CHECK_EQ(oss.str(), "#\n");
	oss.clear();
}

TEST_CASE("Write Tree with value 1") {
	Tree<int> t1(1);

	ostringstream oss;
	oss << t1;

	CHECK_EQ(oss.str(), "1\n");
	oss.clear();
}

TEST_CASE("Write Tree with value 2 and three children") {
	Tree<int> t;
	Tree<int> t1(1);
	Tree<int> t2(2, {t1, t, t1});

	ostringstream oss;
	oss << t2;

	CHECK_EQ(oss.str(),
			 "2\n"
			 "|-- 1\n"
			 "|-- #\n"
			 "'-- 1\n");
}

TEST_CASE("Write Tree with value 10 and many children") {
	Tree<int> t;
	Tree<int> t1(1);
	Tree<int> t2(2, {t1, t, t1});
	Tree<int> t3(10, {t, t1, t2, t2});

	ostringstream oss;
	oss << t3;

	CHECK_EQ(oss.str(),
			 "10\n"
			 "|-- #\n"
			 "|-- 1\n"
			 "|-- 2\n"
			 "|   |-- 1\n"
			 "|   |-- #\n"
			 "|   '-- 1\n"
			 "'-- 2\n"
			 "    |-- 1\n"
			 "    |-- #\n"
			 "    '-- 1\n");
}

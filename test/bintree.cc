#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../bintree.hh"
using namespace pro2;

TEST_CASE("BinTree") {
	BinTree<int> t;
	CHECK(t.empty());

	BinTree<int> t2(1);
	CHECK(!t2.empty());
	CHECK_EQ(t2.value(), 1);
	CHECK(t2.left().empty());
	CHECK(t2.right().empty());

	BinTree<int> t3(1, t2, t2);
	CHECK(!t3.empty());
	CHECK_EQ(t3.value(), 1);
	CHECK(t3.left().value() == t2.value());
	CHECK(t3.right().value() == t2.value());

	BinTree<int> t4(1, t3, t2);
	CHECK(!t4.empty());
	CHECK_EQ(t4.value(), 1);
	CHECK(t4.left().value() == t3.value());
	CHECK(t4.right().value() == t2.value());
}


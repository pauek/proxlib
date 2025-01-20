#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "bintree.hh"
#include "doctest.h"

TEST_CASE("bintree") {
	bintree<int> t;
	CHECK(t.empty());
	CHECK_THROWS(t.value());
	CHECK_THROWS(t.left());
	CHECK_THROWS(t.right());

	bintree<int> t2(1);
	CHECK(!t2.empty());
	CHECK_EQ(t2.value(), 1);
	CHECK(t2.left().empty());
	CHECK(t2.right().empty());
	CHECK_THROWS(t2.left().value());
	CHECK_THROWS(t2.right().value());

	bintree<int> t3(1, t2, t2);
	CHECK(!t3.empty());
	CHECK_EQ(t3.value(), 1);
	CHECK(t3.left().value() == t2.value());
	CHECK(t3.right().value() == t2.value());

	bintree<int> t4(1, t3, t2);
	CHECK(!t4.empty());
	CHECK_EQ(t4.value(), 1);
	CHECK(t4.left().value() == t3.value());
	CHECK(t4.right().value() == t2.value());
}

TEST_CASE("readStringTree") {
	bintree<int> t;
	std::stringstream ss("1(2,3)");
	ss >> t;
	CHECK(!t.empty());
	CHECK_EQ(t.value(), 1);
	CHECK(t.left().value() == 2);
	CHECK(t.right().value() == 3);
}

TEST_CASE("operator <<") {
	bintree<int> t(123, bintree<int>(9), bintree<int>(15));
	std::stringstream ss;
	ss << t;
	CHECK_EQ(ss.str(), "123(9,15)");
}

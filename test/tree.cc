#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tree.hh"
#include <doctest/doctest.h>
using namespace pro2;

TEST_CASE("Tree") {
	Tree<int> t;
	CHECK(t.empty());

    Tree<int> t1(1);

	Tree<int> t2(2, {t1, t, t1});
	CHECK(!t2.empty());
	CHECK_EQ(t2.value(), 2);
	CHECK_EQ(t2.child(0).value(), 1);
	CHECK(t2.child(1).empty());
	CHECK_EQ(t2.child(2).value(), 1);
    CHECK(t2.num_children() == 3);

    Tree<int> t3(10, {t, t1, t2, t2});
    CHECK(!t3.empty());
    CHECK_EQ(t3.value(), 10);
    CHECK(t3.child(0).empty());
    CHECK_EQ(t3.child(1).value(), 1);
    CHECK_EQ(t3.child(2).value(), 2);
    CHECK_EQ(t3.child(3).value(), 2);
    CHECK_EQ(t3.num_children(), 4);
}


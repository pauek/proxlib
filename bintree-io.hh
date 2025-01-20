#ifndef BINTREE_IO_HH
#define BINTREE_IO_HH

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "bintree.hh"

namespace pro2 {

template <typename T>
class BinTreeWriter {
   private:
	struct Branch_ {
		int	   curr = 0;
		size_t total = -1;

		Branch_(int _curr, size_t _total) : curr(_curr), total(_total) {}
	};

	std::ostream&		 out_;
	std::vector<Branch_> pending_;

	static constexpr const char *__through__ = "|   ";
	static constexpr const char *__fork__ = "|-- ";
	static constexpr const char *__corner__ = "'-- ";
	static constexpr const char *__empty__ = "    ";

   public:
	BinTreeWriter(std::ostream& out) : out_(out) {}

	void write(Tree<T> tree) {
		for (int i = 0; i < pending_.size(); i++) {
			bool	 is_last = i == pending_.size() - 1;
			Branch_& pend = pending_[i];
			if (pend.curr >= pend.total) {
				out_ << __empty__;
			} else if (pend.curr == pend.total - 1) {
				out_ << (is_last ? __corner__ : __through__);
			} else {
				out_ << (is_last ? __fork__ : __through__);
			}
			if (is_last) {
				pend.curr++;
			}
		}

		if (tree.empty()) {
			out_ << "#" << std::endl;
			return;
		}

		out_ << tree.value() << std::endl;

		Tree<T> left = tree.left();
		Tree<T> right = tree.right();

		if (left.empty() and right.empty()) {
			return;
		}

		// Write left
		pending_.push_back(Branch_(0, 2));
		write(left);
		pending_.pop_back();

		// Write right
		pending_.push_back(Branch_(1, 2));
		write(right);
		pending_.pop_back();
	}
};

}  // namespace pro2

#endif
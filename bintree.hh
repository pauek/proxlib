#ifndef BINTREE_HH
#define BINTREE_HH

#include <cassert>
#include <memory>

namespace pro2 {

/**
 * @file BinTree.hh
 * @class BinTree
 * @brief A class representing binary trees
 */
template <typename T>
class Tree {
   private:
	/**
	 * @brief Struct that holds the node's information
	 */
	struct Node_ {
		T					   x;
		std::shared_ptr<Node_> left;
		std::shared_ptr<Node_> right;

		Node_(const T& x, std::shared_ptr<Node_> left, std::shared_ptr<Node_> right)
			: x(x), left(left), right(right) {}
	};

	/**
	 * @brief Pointer to the node of the tree
	 */
	std::shared_ptr<Node_> pnode_;

	/**
	 * @brief Constructs a tree from a node pointer.
	 */
	Tree(std::shared_ptr<Node_> pnode) : pnode_(pnode) {}

   public:
	/**
	 * @brief Constructs an empty tree. Θ(1).
	 */
	Tree() : pnode_(nullptr) {}

	/**
	 * @brief Constructs a tree as a copy of another tree. Θ(1).
	 */
	Tree(const Tree& t) { pnode_ = t.pnode_; }

	/**
	 * @brief Constructs a tree with a value `x` and no subtrees. Θ(1).
	 */
	explicit Tree(const T& x) { pnode_ = std::make_shared<Node_>(x, nullptr, nullptr); }

	/**
	 * @brief Constructs a tree with a value `x` and two subtrees `left` and `right`. Θ(1).
	 */
	explicit Tree(const T& x, const Tree& left, const Tree& right) {
		pnode_ = std::make_shared<Node_>(x, left.pnode_, right.pnode_);
	}

	/**
	 * @brief Assigns the tree `t` to this tree, and returns the object itself. Θ(1).
	 */
	Tree& operator=(const Tree& t) {
		pnode_ = t.pnode_;
		return *this;
	}

	/**
	 * @brief Returns `true` if this tree is empty, `false` otherwise. Θ(1).
	 */
	bool empty() const { return pnode_ == nullptr; }

	/**
	 * @brief Returns the left subtree of this tree. Aborts if empty. Θ(1).
	 */
	Tree left() const {
		assert(not empty());
		return BinTree(pnode_->left);
	}

	/**
	 * @brief Returns the right subtree of this tree. Aborts if empty. Θ(1).
	 */
	Tree right() const {
		assert(not empty());
		return BinTree(pnode_->right);
	}

	/**
	 * @brief Returns the value of this tree. Aborts if empty. Θ(1).
	 */
	const T& value() const {
		assert(not empty());
		return pnode_->value;
	}
};

}  // namespace pro2

#endif
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
class BinTree {
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
	BinTree(std::shared_ptr<Node_> pnode) : pnode_(pnode) {}

   public:
	/**
	 * @brief Constructs an empty tree. Θ(1).
	 */
	BinTree() : pnode_(nullptr) {}

	/**
	 * @brief Constructs a tree as a copy of another tree. Θ(1).
	 */
	BinTree(const BinTree& t) { pnode_ = t.pnode_; }

	/**
	 * @brief Assigns the tree t to this tree. Θ(1).
	 */
	BinTree& operator=(const BinTree& t) {
		pnode_ = t.pnode_;
		return *this;
	}

	/**
	 * @brief Constructs a tree with a value x and no subtrees. Θ(1).
	 */
	explicit BinTree(const T& x) { pnode_ = std::make_shared<Node_>(x, nullptr, nullptr); }

	/**
	 * @brief Constructs a tree with a value x and two subtrees left and right. Θ(1).
	 */
	explicit BinTree(const T& x, const BinTree& left, const BinTree& right) {
		pnode_ = std::make_shared<Node_>(x, left.pnode_, right.pnode_);
	}

	/**
	 * @brief Tells if this tree is empty. Θ(1).
	 */
	bool empty() const { return pnode_ == nullptr; }

	/**
	 * @brief Returns the left subtree of this tree (cannot be empty). Θ(1).
	 */
	BinTree left() const {
		assert(not empty());
		return BinTree(pnode_->left);
	}

	/**
	 * @brief Returns the right subtree of this tree (cannot be empty). Θ(1).
	 */
	BinTree right() const {
		assert(not empty());
		return BinTree(pnode_->right);
	}

	/**
	 * @brief Returns the value of this tree (cannot be empty). Θ(1).
	 */
	const T& value() const {
		assert(not empty());
		return pnode_->x;
	}
};

}  // namespace pro2

#endif
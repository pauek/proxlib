#ifndef BINTREE_HH
#define BINTREE_HH

#ifndef NO_DIAGRAM
#include <memory>
#endif

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// A bintree<T> implements binary trees with values of type T.
template <typename T>
class bintree {
	struct Node {
		T					  value;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;

		Node(const T& value, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
			: value(value), left(left), right(right) {}
	};

	// A tree only holds a node pointer.
	std::shared_ptr<Node> p;

	// Constructs a tree from a node pointer.
	bintree(std::shared_ptr<Node> p) : p(p) {}

	static void read(int&													 itoken,
					 const std::vector<std::pair<std::string, std::string>>& vtoken,
					 bintree<T>&											 t);
	static void write(std::ostream& os, const bintree<T>& t);

   public:
	// Constructs an empty tree. Θ(1).
	bintree() : p(nullptr) {}

	bintree(const bintree& t) : p(t.p) {}

	bintree& operator=(const bintree& t) {
		p = t.p;
		return *this;
	}

	// Constructs a tree with a value x and no subtrees. Θ(1).
	explicit bintree(const T& value) : p(std::make_shared<Node>(value, nullptr, nullptr)) {}

	// Constructs a tree with a value x and two subtrees left and right. Θ(1).
	explicit bintree(const T& value, const bintree& left, const bintree& right)
		: p(std::make_shared<Node>(value, left.p, right.p)) {}

	// Tells if this tree is empty. Θ(1).
	bool empty() const { return p == nullptr; }

	// Returns the left subtree of this tree (cannot be empty). Θ(1).
	bintree left() const {
		if (empty()) {
			throw std::runtime_error("Cannot get left subtree of an empty tree");
		}
		return bintree(p->left);
	}

	// Returns the right subtree of this tree (cannot be empty). Θ(1).
	bintree right() const {
		if (empty()) {
			throw std::runtime_error("Cannot get right subtree of an empty tree");
		}
		return bintree(p->right);
	}

	// Returns the value of this tree (cannot be empty). Θ(1).
	const T& value() const {
		if (empty()) {
			throw std::runtime_error("Cannot get value of an empty tree");
		}
		return p->value;
	}

	// writing operator <<
	template <class U>
	friend std::ostream& operator<<(std::ostream& os, const bintree<U>& t);

	// reading operator >>
	template <class U>
	friend std::istream& operator>>(std::istream& is, bintree<U>& t);
};

template <typename T>
void bintree<T>::read(int&													  itoken,
					  const std::vector<std::pair<std::string, std::string>>& vtoken,
					  bintree<T>&											  t) {
	if (itoken >= int(vtoken.size()) || vtoken[itoken].first != "value") {
		t = bintree<T>();
		return;
	}
	std::istringstream mycin(vtoken[itoken].second);
	T				   value;
	mycin >> value;
	itoken++;
	if (itoken >= int(vtoken.size()) || vtoken[itoken].first != "(") {
		t = bintree<T>(value);
		return;
	}
	itoken++;
	bintree<T> left;
	read(itoken, vtoken, left);
	if (itoken >= int(vtoken.size()) || vtoken[itoken].first != ",") {
		t = bintree<T>(value, left, bintree<T>());
		if (itoken < int(vtoken.size()) && vtoken[itoken].first == ")") {
			itoken++;
		}
		return;
	}
	itoken++;
	bintree<T> right;
	read(itoken, vtoken, right);
	if (itoken < int(vtoken.size()) && vtoken[itoken].first == ")") {
		itoken++;
	}
	t = bintree<T>(value, left, right);
}

template <typename T>
void bintree<T>::write(std::ostream& os, const bintree<T>& t) {
	if (t.empty()) {
		return;
	}
	os << t.value();
	bintree<T> left = t.left();
	bintree<T> right = t.right();
	if (left.empty() && right.empty()) {
		return;
	}
	os << "(";
	write(os, left);
	os << ",";
	write(os, right);
	os << ")";
}

template <class T>
std::ostream& operator<<(std::ostream& os, const bintree<T>& t) {
	if (t.empty()) {
		os << "()";
		return os;
	}
	bintree<T>::write(os, t);
	return os;
}

template <class T>
std::istream& operator>>(std::istream& is, bintree<T>& t) {
	std::string s;
	is >> s;
	std::vector<std::pair<std::string, std::string>> vtoken;
	int												 iant = 0;
	for (int i = 0; i < int(s.size()); i++) {
		if (s[i] == ',' || s[i] == '(' || s[i] == ')') {
			if (iant < i) {
				vtoken.push_back(
					std::pair<std::string, std::string>("value", s.substr(iant, i - iant)));
			}
			iant = i + 1;
			vtoken.push_back(std::pair<std::string, std::string>(std::string(1, s[i]), ""));
		}
	}
	if (iant < int(s.size())) {
		vtoken.push_back(std::pair<std::string, std::string>("value", s.substr(iant)));
	}
	int itoken = 0;
	bintree<T>::read(itoken, vtoken, t);
	return is;
}

#endif

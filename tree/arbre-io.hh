#ifndef ARBGIOINT_HH
#define ARBGIOINT_HH

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include "arbre.hh"

// Read //////////////////////////////////////////////////////////////////////

const std::string _through = "|   ";
const std::string _fork = "|-- ";
const std::string _corner = "'-- ";
const std::string _empty = "    ";

const std::vector<std::string> _tree_pieces{_through, _fork, _corner, _empty};

bool _is_tree_piece(std::string line) {
	if (line.size() < 4) {
		return false;
	}
	const std::string prefix = line.substr(0, 4);
	for (const auto& piece : _tree_pieces) {
		if (prefix == piece) {
			return true;
		}
	}
	return false;
}

template <typename T>
struct Element {
	int level;
	T value;
};

template <typename T>
Element<T> _parse_element(std::istream& in) {
	std::string line;
	getline(in, line);

	Element<T> result{0};
	while (_is_tree_piece(line.substr(0, 4))) {
		line = line.substr(4);
		result.level++;
	}
	std::istringstream sin(line);
	sin >> result.value;
	return result;
}

template <typename T>
struct Result {
	ArbreGen<T> tree;
	int level;
	T value;
};

template <typename T>
Result<T> _parse_tree(std::istream& in, int level, T value) {
	// If the next element we see is not a child => we have no children
	auto elem = _parse_element<T>(in);
	if (elem.level <= level) {
		return {
			.tree = ArbreGen<T>(value),
			.level = elem.level,
			.value = elem.value,
		};
	}

	// Accumulate all children while the level is above ours
	Result<T> result = {
		.tree = ArbreGen<T>(value),
		.level = elem.level,
		.value = elem.value,
	};
	do {
		assert(result.level == level + 1);
		auto child_result = _parse_tree<T>(in, result.level, result.value);
		result.tree.afegir_fill(child_result.tree);
		result.level = child_result.level;
		result.value = child_result.value;
	} while (result.level > level);

	return result;
}

template <typename T>
ArbreGen<T> llegir_arbre(istream& in) {
	auto elem = _parse_element<T>(in);
	assert(elem.level == 0);
	auto result = _parse_tree<T>(in, elem.level, elem.value);
	return result.tree;
}

ArbreGen<int> llegir_arbre_int() {
	return llegir_arbre<int>(cin);
}

// Write //////////////////////////////////////////////////////////////////////

struct Branch {
	int curr = 0;
	size_t total = -1;
};

template <typename T>
void _write_tree(std::ostream& out, ArbreGen<T>& A, std::vector<Branch>& pending) {
	for (int i = 0; i < pending.size(); i++) {
		bool is_last = i == pending.size() - 1;
		Branch& pend = pending[i];
		if (pend.curr >= pend.total) {
			out << _empty;
		} else if (pend.curr == pend.total - 1) {
			out << (is_last ? _corner : _through);
		} else {
			out << (is_last ? _fork : _through);
		}
		if (is_last) {
			pend.curr++;
		}
	}

	out << A.arrel() << std::endl;

	std::vector<ArbreGen<T>> children;
	A.fills(children);
	for (int i = 0; i < children.size(); i++) {
		pending.push_back(Branch{.curr = i, .total = children.size()});
		_write_tree(out, children[i], pending);
		pending.pop_back();
	}
}

// FIXME(pauek): Writing the tree destroys it!
template <typename T>
void escriure_arbre(ArbreGen<T>& A) {
	std::vector<Branch> pending;
	_write_tree(std::cout, A, pending);
}

#endif
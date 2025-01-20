#include <random>
#include "arbre-io.hh"
#include "arbre.hh"

random_device dev;
mt19937 rng(dev());

int rnd_int(int min, int max) {
	uniform_int_distribution<mt19937::result_type> dist(min, max);
	return dist(rng);
}

string rnd_word(int size) {
	string word = "";
	for (int i = 0; i < size; i++) {
		word += char(rnd_int(97, 122));
	}
	return word;
}

ArbreGen<string> random_tree(int min_level, int max_level) {
	assert(min_level < max_level);
	string value = rnd_word(6);
	ArbreGen<string> A(value);
	if (max_level > 1) {
		int num_children = rnd_int(min_level > 0 ? 1 : 0, 4);
		for (int i = 0; i < num_children; i++) {
			A.afegir_fill(random_tree(min_level - 1, max_level - 1));
		}
	}
	return A;
}

int main() {
	auto A = random_tree(2, 9);
	escriure_arbre(A);
}

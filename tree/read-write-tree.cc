#include "arbre-io.hh"
#include "arbre.hh"

int main() {
	auto A = llegir_arbre<string>(cin);
	escriure_arbre(A);
}
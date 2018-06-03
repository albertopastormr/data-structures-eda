// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include "bintree_eda.h"

struct sol_t{
	int arbol_max, arbol_min;
	bool es_arbol_busq;
	sol_t(int max, int min, bool b) : arbol_max(max), arbol_min(min), es_arbol_busq(b) {}
};

sol_t arbol_busq(bintree<int> const & arbol){
	if (arbol.empty())
		return{ -1, -1, true };
	else if (arbol.left().empty() && arbol.right().empty())
		return{ arbol.root(), arbol.root(), true };
	else if (arbol.left().empty()){
		sol_t sol = arbol_busq(arbol.right());
		return{ std::max(sol.arbol_max, arbol.root()), std::min(sol.arbol_min, arbol.root()), sol.es_arbol_busq && arbol.root() < sol.arbol_min };
	}
	else if (arbol.right().empty()){
		sol_t sol = arbol_busq(arbol.left());
		return{ std::max(sol.arbol_max, arbol.root()), std::min(sol.arbol_min, arbol.root()), sol.es_arbol_busq && arbol.root() > sol.arbol_max };
	}
	else{
		sol_t sol_iz = arbol_busq(arbol.left());
		sol_t sol_dr = arbol_busq(arbol.right());
		return{ std::max(std::max(sol_iz.arbol_max, sol_dr.arbol_max), arbol.root()), std::min(std::min(sol_iz.arbol_min, sol_dr.arbol_min), arbol.root()), sol_iz.es_arbol_busq && sol_dr.es_arbol_busq && arbol.root() > sol_iz.arbol_max && arbol.root() < sol_dr.arbol_min };
	}
}
// función que resuelve el problema
bool resolver(bintree<int> const & arbol) {
	return arbol_busq(arbol).es_arbol_busq;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	bintree<int> arbol_d;
	// leer los datos de la entrada
	arbol_d = leerArbol(-1);

	std::cout << (resolver(arbol_d) ? "SI\n" : "NO\n");
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
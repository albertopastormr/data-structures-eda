// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

#include "bintree_eda.h"

struct tSol{
	int numGrupos = 0, numExcursionistasMax = 0;
	tSol(int ng, int ne) : numGrupos(ng), numExcursionistasMax(ne){}
};
// función que resuelve el problema
template <class T>
tSol excursion(bintree<T> const & tree) {
	if (tree.left().empty() && tree.right().empty())
		return{ (tree.root() > 0 ? 1 : 0), tree.root() };
	else if (tree.left().empty()){
		tSol dr = excursion(tree.right());
		return{ (dr.numGrupos == 0 ? (tree.root() > 0 ? 1 : 0) : dr.numGrupos), dr.numExcursionistasMax + tree.root() };
	}
	else if (tree.right().empty()){
		tSol iz = excursion(tree.left());
		return{ (iz.numGrupos == 0 ? (tree.root() > 0 ? 1 : 0) : iz.numGrupos), iz.numExcursionistasMax + tree.root()};
	}
	else{
		tSol iz = excursion(tree.left());
		tSol dr = excursion(tree.right());
		return{ ((iz.numGrupos == 0 && dr.numGrupos == 0) ? (tree.root() > 0 ? 1 : 0) : iz.numGrupos + dr.numGrupos), std::max(iz.numExcursionistasMax, dr.numExcursionistasMax) + tree.root() };
	}

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	auto tree = leerArbol(-1);
	tSol sol = excursion(tree);
	// escribir sol
	std::cout << sol.numGrupos << " " << sol.numExcursionistasMax << "\n";
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
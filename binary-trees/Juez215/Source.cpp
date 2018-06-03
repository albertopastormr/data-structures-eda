// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

#include "bintree_eda.h"

struct tSol{
	int numNavegables = 0, caudal = 0;
	tSol(int nn, int c) : numNavegables(nn), caudal(c){}
};
// función que resuelve el problema
template <class T>
tSol aguaslimpias(bintree<T> const & tree) {
	if (tree.left().empty() && tree.right().empty())
		return{ 0, (tree.root() > 0 ? 0 : 1)};
	else if (tree.left().empty()){
		tSol dr = aguaslimpias(tree.right());
		return{ dr.numNavegables + (dr.caudal >= 3 ? 1 : 0), std::max(dr.caudal - tree.root(), 0)};
	}
	else if (tree.right().empty()){
		tSol iz = aguaslimpias(tree.left());
		return{ iz.numNavegables + (iz.caudal >= 3 ? 1 : 0), std::max(iz.caudal - tree.root(), 0)};
	}
	else{
		tSol iz = aguaslimpias(tree.left());
		tSol dr = aguaslimpias(tree.right());
		return{ iz.numNavegables + dr.numNavegables + (iz.caudal >= 3 ? 1 : 0) + (dr.caudal >= 3 ? 1 : 0), std::max(iz.caudal + dr.caudal - tree.root(),0) };
	}

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	auto tree = leerArbol(-1);
	tSol sol = aguaslimpias(tree);
	// escribir sol
	std::cout << sol.numNavegables << "\n";
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
// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "bintree_eda.h"

struct tSol{
	int numNodos = 0, numHojas = 0, altura = 0;
	tSol(int nn, int nh, int a) : numNodos(nn),numHojas(nh), altura(a) {};
};

// función que resuelve el problema
template <class T>
tSol resolver(bintree<T> const & tree) {
	if (tree.empty()){
		return{ 0, 0, 0};
	}
	else{
		tSol iz = resolver(tree.left());
		tSol dr = resolver(tree.right());
		return{ iz.numNodos + dr.numNodos + 1, iz.numHojas + dr.numHojas + (tree.left().empty() && tree.right().empty() ? 1 : 0), std::max(iz.altura, dr.altura) + 1 };
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	auto tree = leerArbol('.');

	tSol sol = resolver(tree);
	std::cout << sol.numNodos << " " << sol.numHojas << " " << sol.altura << '\n';
	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datostxt.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();
	
	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
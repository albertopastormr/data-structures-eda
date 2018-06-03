// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "bintree_eda.h"


void print(std::vector<int> const & v){
	if (v.size() > 0){
		std::cout << v[0];
		for (int i = 1; i < v.size(); i++)
			std::cout << " " << v[i];
	}
	std::cout << '\n';
}
// función que resuelve el problema
template <class T>
void resolver(bintree<T> const & tree, std::vector<int> & sol) {
	if (!tree.empty()){
		if (tree.left().empty() && tree.right().empty()){
			sol.push_back(tree.root());
		}
		else{
			resolver(tree.left(), sol);
			resolver(tree.right(), sol);
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	auto tree = leerArbol(-1);
	std::vector<int> sol;
	resolver(tree, sol);
	print(sol);
	return true;
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
	for (int i = 0; i < numCasos; i++)
		resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
// Alberto Pastor Moreno
// E46

#include <memory>
#include <stdexcept>
#include <stack>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>

#include "bintree_eda.h"

template<class T>
T menor_elem(bintree<T> const & tree){
	if (tree.left().empty() && tree.right().empty())
		return tree.root();
	else if (tree.left().empty())
		return std::min(menor_elem(tree.right()), tree.root());
	else if (tree.right().empty())
		return std::min(menor_elem(tree.left()), tree.root());
	else{
		return std::min( std::min(menor_elem(tree.left()), menor_elem(tree.right())), tree.root());
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	char tipo;
	std::cin >> tipo;
	if (!std::cin)
		return false;
	switch (tipo){
	case('N') : {
		int vacio = -1;
		auto tree = leerArbol(vacio);
		std::cout << menor_elem(tree) << '\n';
	} break;
	case('P') : {
		std::string vacio = "#";
		auto tree = leerArbol(vacio);
		std::cout << menor_elem(tree) << '\n';
	} break;
	}
	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
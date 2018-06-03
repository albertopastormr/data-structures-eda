// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include "bintree_eda.h"

// Estructura auxiliar para la resolucion del problema
struct sol_t{
	bool es_zurdo;
	int num_nodos_descendientes;
	sol_t(bool z, int nnd) : es_zurdo(z), num_nodos_descendientes(nnd){}
};

// Funcion recursiva que resuelve el problema visitando todos los nodos utilizando la estructura 'sol_t'
sol_t arboles_zurdos(bintree<char> const & arbol_d){ // O(N) siendo N el numero de nodos del arbol 'arbol_d'
	if (arbol_d.empty())
		return{ true, 0 };
	else if (arbol_d.left().empty() && arbol_d.right().empty())
		return{ true, 1 };
	else if (arbol_d.left().empty()){
		return{ false, 1 };
	}
	else if (arbol_d.right().empty()){
		sol_t sol =  arboles_zurdos(arbol_d.left());
		return{ sol.es_zurdo, sol.num_nodos_descendientes + 1 };
	}
	else{
		sol_t sol_iz = arboles_zurdos(arbol_d.left());
		sol_t sol_dr = arboles_zurdos(arbol_d.right());
		return{ sol_iz.es_zurdo && sol_dr.es_zurdo && sol_iz.num_nodos_descendientes > sol_dr.num_nodos_descendientes, sol_iz.num_nodos_descendientes + sol_dr.num_nodos_descendientes + 1 };
	}
}

// función que llama a la funcion recursiva 'arboles_zurdos()' que resuelve el problema
bool resolver(bintree<char> const & arbol_d) {
	return arboles_zurdos(arbol_d).es_zurdo;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	bintree<char> arbol_datos = leerArbol('.');
	std::cout << (resolver(arbol_datos) ? "SI\n" : "NO\n");
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
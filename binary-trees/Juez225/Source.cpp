// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include "bintree_eda.h"

struct sol_t{
	int valor_hoja = -1, num_dragones = -1;
	sol_t(int vh, int nd) : valor_hoja(vh), num_dragones(nd){}
};


// función que resuelve el problema
sol_t hoja_camino_menor_num_dragones(bintree<int> const & arbol_tesoro) {
	if (arbol_tesoro.left().empty() && arbol_tesoro.right().empty())
		return{ arbol_tesoro.root(), 0 };
	else if (arbol_tesoro.left().empty()){
		sol_t sol = hoja_camino_menor_num_dragones(arbol_tesoro.right());
		return{ sol.valor_hoja, (arbol_tesoro.root() == 1 ? sol.num_dragones + 1 : sol.num_dragones)};
	}
	else if (arbol_tesoro.right().empty()){
		sol_t sol = hoja_camino_menor_num_dragones(arbol_tesoro.left());
		return{ sol.valor_hoja, (arbol_tesoro.root() == 1 ? sol.num_dragones + 1 : sol.num_dragones) };
	}
	else{
		sol_t sol_izq = hoja_camino_menor_num_dragones(arbol_tesoro.left());
		sol_t sol_der = hoja_camino_menor_num_dragones(arbol_tesoro.right());
		sol_izq.num_dragones += (arbol_tesoro.root() == 1 ? 1 : 0);
		sol_der.num_dragones += (arbol_tesoro.root() == 1 ? 1 : 0);
		return (sol_izq.num_dragones <= sol_der.num_dragones ? sol_izq : sol_der);
	}
}

int resolver(bintree<int> const & arbol_tesoro){
	return hoja_camino_menor_num_dragones(arbol_tesoro).valor_hoja;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree<int> arbol_tesoro = leerArbol(-1);
	// procesa la entrada e imprime la salida
	std::cout << resolver(arbol_tesoro) << "\n";
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
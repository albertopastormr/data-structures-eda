// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

#include "bintree_eda.h"

bool es_primo(long int elem){
	int i = elem/2;
	while (i > 1 && elem % i != 0){
		i--;
	}
	return i == 1;
}

struct tSol{
	int mult7masCercano = -1, profundidad = 0;
	tSol(int mmc, int p) : mult7masCercano(mmc), profundidad(p){}
};
// función que resuelve el problema
template <class T>
tSol primos(bintree<T> const & tree, int nivel) {
	if (!tree.empty() && !es_primo(tree.root())){
			bool es_raiz_valida = tree.root() % 7 == 0;
		if (tree.left().empty() && tree.right().empty())
			return{ (es_raiz_valida ? tree.root() : -1), (es_raiz_valida ? nivel : 0) };
		else if (tree.left().empty()){
			tSol dr = primos(tree.right(), nivel + 1);
			return{ (es_raiz_valida ? tree.root() : dr.mult7masCercano), (es_raiz_valida ? nivel : dr.profundidad) };
		}
		else if (tree.right().empty()){
			tSol iz = primos(tree.left(), nivel + 1);
			return{ (es_raiz_valida ? tree.root() : iz.mult7masCercano), (es_raiz_valida ? nivel : iz.profundidad) };
		}
		else{
			tSol iz = primos(tree.left(), nivel + 1);
			tSol dr = primos(tree.right(), nivel + 1);
			if (iz.mult7masCercano != -1 && dr.mult7masCercano != -1)
				return{ (es_raiz_valida ? tree.root() : (iz.profundidad <= dr.profundidad ? iz.mult7masCercano : dr.mult7masCercano)), (es_raiz_valida ? nivel : std::min(iz.profundidad, dr.profundidad)) };
			else if (iz.mult7masCercano != -1)
				return{ (es_raiz_valida ? tree.root() : iz.mult7masCercano), (es_raiz_valida ? nivel : iz.profundidad) };
			else
				return{ (es_raiz_valida ? tree.root() : dr.mult7masCercano), (es_raiz_valida ? nivel : dr.profundidad) };
		}
	}
	return{ -1, 0 };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	auto tree = leerArbol(-1);
	tSol sol = primos(tree, 1);
	// escribir sol
	if (sol.mult7masCercano != -1)
		std::cout << sol.mult7masCercano << " " << sol.profundidad;
	else
		std::cout << "NO HAY";
	std::cout << "\n";
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
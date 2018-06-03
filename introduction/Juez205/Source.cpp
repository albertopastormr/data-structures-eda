// Alberto Pastor Moreno
// E46

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>


#include "conjunto.h"

template <class T>
void read( set<T> & datos, T end){
	T elem;
	std::cin >> elem;
	while (elem != end){
		if (!datos.contains(elem)){
			datos.insert(elem);
		}
		std::cin >> elem;
	}
}

// función que resuelve el problema
template <class T>
void resolver(set<T> const & elementos, set<T> & sol, int k) {

	int i = elementos.size() -1 ;
	while (i >= 0 && sol.size() < k){
		if (!sol.contains(elementos.value(i)))
			sol.insert(elementos.value(i));
		i--;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	char selec;
	int k;
	std::cin >> selec;
	if (!std::cin)
		return false;
	std::cin >> k;

	switch (selec){
	case 'N':{
		set<int> datos;

		read( datos,-1);

		set<int> sol;
		resolver(datos, sol, k);

		sol.print(); }
			break;
	case 'P':{
		set<std::string> datos;

		read( datos,std::string("FIN"));

		set<std::string> sol;

		resolver(datos, sol, k);

		sol.print(); }
			break;
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
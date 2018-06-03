// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include "polinomio.h"




// función que resuelve el problema
long long int resolver(polinomio pol, int valoracion) {
	return pol.valoracion(valoracion);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	polinomio pol;
	monomio mon;
	std::cin >> mon.coef >> mon.exp;
	if (!std::cin)
		return false;
	while (mon.coef != 0 || mon.exp != 0){
		pol.insert(mon);
		std::cin >> mon.coef >> mon.exp;
	}
	
	pol.sort();
	
	int numValoraciones, valoracion;
	std::cin >> numValoraciones;
	for (int i = 0; i < numValoraciones; i++){
		std::cin >> valoracion;
		if (i == 0){
			std::cout << resolver(pol, valoracion);
		}
		else{
			std::cout << " " << resolver(pol, valoracion);
		}
	}
	std::cout << "\n";
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
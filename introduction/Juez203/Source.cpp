// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

#include "complejo.h"

struct tDatos{
	complejo num;
	int numIteraciones;
};


complejo operator*(complejo left, complejo right){
	return left.producto(right);
}
complejo operator+(complejo left, complejo right){
	return left.suma(right);
}


// función que resuelve el problema
bool resolver(tDatos datos) {
	
	complejo sumAnteriores = complejo();

	bool encontrado = false; // Si encontrado = true, la serie de c diverge
	int i = 1;
	while (i < datos.numIteraciones && !encontrado){
		complejo next = ((sumAnteriores * sumAnteriores) + datos.num);
		if ( next.mod() > 2.0)
			encontrado = true; // En este se afirma que datos.num caso diverge
		sumAnteriores = next;
		i++;
	}
	return !encontrado; // Pertenece al conjunto de mandelbrot si no diverge
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	tDatos datos;
	float inReal, inImagin;
	std::cin >> inReal >> inImagin >> datos.numIteraciones;
	datos.num = complejo(inReal, inImagin);
	
	std::cout << (resolver(datos) ? "SI\n" : "NO\n");
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
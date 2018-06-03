// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

// función que resuelve el problema
int alturaArbol(int ramas) {
	int alturaRama = 1;
	for (int i = 0; i < ramas; i++){
		int rama;
		std::cin >> rama;
		if (rama > 0)
			alturaRama = std::max(alturaRama, 1 + alturaArbol(rama));
	}
	return alturaRama;
}

int resolver(int primerNivel){
	return (primerNivel == 0 ?  1 : alturaArbol(primerNivel) + 1); // Se cuenta aqui la copa del arbol
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	int primerNivel;
	std::cin >> primerNivel;
	std::cout << resolver(primerNivel) << "\n";
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
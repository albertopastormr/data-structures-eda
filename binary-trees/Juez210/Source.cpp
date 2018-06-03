// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

// función que resuelve el problema
int precarios(int numRamas, int nivel, int minNivel) {
	int numPrecarios = 0;
	for (int i = 0; i < numRamas; i++){
		int rama;
		std::cin >> rama;
		if (rama != 0)
			numPrecarios += precarios(rama, nivel + 1, minNivel);
		else if (nivel >= minNivel)
			numPrecarios++;
	}
	return numPrecarios;
}

int resolver(int ramasPrimerNivel, int minNivel){
	return (ramasPrimerNivel == 0 ? 0 : precarios(ramasPrimerNivel, 1, minNivel) ); // Se cuenta aqui la copa del arbol
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int minNivel, ramasPrimerNivel;
	std::cin >> minNivel >>  ramasPrimerNivel;
	if (!std::cin)
		return false;
	std::cout << resolver(ramasPrimerNivel, minNivel) << "\n";
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso());


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
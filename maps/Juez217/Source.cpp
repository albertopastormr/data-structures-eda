// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
// función que resuelve el problema
long int capitulos_consecutivos_nuevos(long int num_capitulos) {
	std::unordered_map<int, int> historial; // Clave: numero de capitulo ; Valor: ultimo dia en el cual fue retransmitido el capitulo
	long int elem, init_pos_secuencia_capitulos_nuevos = 1, max_secuencia_capitulos_nuevos = 0, actual_secuencia_capitulos_nuevos = 0;
	for (long int i = 1; i < num_capitulos + 1; i++){
		std::cin >> elem;
		if (historial[elem] >= init_pos_secuencia_capitulos_nuevos){
			init_pos_secuencia_capitulos_nuevos = historial[elem] + 1;
			actual_secuencia_capitulos_nuevos = i - historial[elem];
		}
		else{
			actual_secuencia_capitulos_nuevos++;
			if (actual_secuencia_capitulos_nuevos > max_secuencia_capitulos_nuevos)
				max_secuencia_capitulos_nuevos = actual_secuencia_capitulos_nuevos;
		}
		historial[elem] = i;
	}
	return max_secuencia_capitulos_nuevos;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	long int num_capitulos;
	std::cin >> num_capitulos;
	std::cout << capitulos_consecutivos_nuevos(num_capitulos) << "\n";
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
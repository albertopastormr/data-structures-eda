// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <sstream>

void printDiff(std::map<std::string, std::vector<long int> > const & map){
	for (auto it = map.begin(); it != map.cend(); it++){
		std::cout << it->first;
		for (int i = 0; i < it->second.size(); i++)
			std::cout << " " << it->second[i];
		std::cout << "\n";
	}
	std::cout << "----\n";
}

// función que resuelve el problema
std::map<std::string, std::vector<long int> > create_line_references_map(long int num_lines) {
	std::map<std::string, std::vector<long int> > references_map;
	std::string actual_line, actual_word;
	for (int i = 0; i < num_lines; i++){
		std::getline(std::cin, actual_line);
		std::stringstream ss(actual_line);
		while (ss >> actual_word){
			if (actual_word.length() > 2){
				std::transform(actual_word.begin(), actual_word.end(), actual_word.begin(), ::tolower);
				if (references_map.count(actual_word)){
					std::vector<long int> & v_ref = references_map[actual_word];
					if (v_ref.empty() || v_ref[v_ref.size() - 1] < i + 1)
						references_map[actual_word].push_back(i + 1);
				}
				else
					references_map[actual_word].push_back(i + 1);
			}
		}
	}
	return references_map;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	long int num_lines;
	std::cin >> num_lines;
	if (num_lines == 0)
		return false;
	// escribir sol
	std::cin.get();
	printDiff(create_line_references_map(num_lines));
	return true;
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
// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

std::map<std::string, int> parseDict(std::string const & dict_line){
	std::map<std::string, int> dict;
	std::string iterating_parse_aux = "", last_key="";
	bool parsing_key = true;
	for (int i = 0; i < dict_line.length(); i++){
		if (dict_line[i] == ' '){
			if (parsing_key){
				last_key = iterating_parse_aux;
				parsing_key = false;
			}
			else{
				dict[last_key] = std::stoi(iterating_parse_aux);
				parsing_key = true;
			}
			iterating_parse_aux = "";
		}
		else
			iterating_parse_aux += dict_line[i];
	}
	return dict;
}

void printDiff(std::map<char, std::vector<std::string> > const & diff){
	if (diff.size() != 0){
		if (diff.count('+')){
			std::vector<std::string> const & v = diff.at('+');
			std::cout << '+';
			for (int j = 0; j < v.size(); j++)
				std::cout << " " << v[j];
			std::cout << "\n";
		}
		if (diff.count('-')){
			std::vector<std::string> const & v = diff.at('-');
			std::cout << '-';
			for (int j = 0; j < v.size(); j++)
				std::cout << " " << v[j];
			std::cout << "\n";
		}
		if (diff.count('*')){
			std::vector<std::string> const & v = diff.at('*');
			std::cout << '*';
			for (int j = 0; j < v.size(); j++)
				std::cout << " " << v[j];
			std::cout << "\n";
		}
	}
	else
		std::cout << "Sin cambios\n";
	std::cout << "----\n";
}

// función que resuelve el problema
std::map<char, std::vector<std::string> > dictionary_diff(std::map<std::string, int> const & old_dict, std::map<std::string, int> const & new_dict) {
	std::map<char, std::vector<std::string> > dictionary_diff;
	auto old_it = old_dict.begin();
	auto new_it = new_dict.begin();
	while (old_it != old_dict.cend() || new_it != new_dict.cend()){
		if (old_it != old_dict.cend() && new_it != new_dict.cend()){
			if (old_it->first == new_it->first){
				if (old_it->second != new_it->second)
					dictionary_diff['*'].push_back(old_it->first);
				old_it++;
				new_it++;
			}
			else if (old_it->first < new_it->first){
				dictionary_diff['-'].push_back(old_it->first);
				old_it++;
			}
			else{
				dictionary_diff['+'].push_back(new_it->first);
				new_it++;
			}
		}
		else if (old_it != old_dict.cend()){
			dictionary_diff['-'].push_back(old_it->first);
			old_it++;
		}
		else{
			dictionary_diff['+'].push_back(new_it->first);
			new_it++;
		}
	}
	return dictionary_diff;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	std::string old_dict, new_dict;
	std::getline(std::cin, old_dict);
	std::getline(std::cin, new_dict);
	// escribir sol
	printDiff(dictionary_diff(parseDict(old_dict + " "), parseDict(new_dict + " ")));
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
	std::cin.get();
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
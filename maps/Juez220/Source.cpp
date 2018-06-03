// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

// Estructura que define el par <key,value> del mapa utilizado en el ejercicio
struct sport_ref_t{
	std::string key;
	int value;
	sport_ref_t(std::string k, int v) : key(k), value(v){}
};

// Compara dos instancias de la estructura sport_ref_t
bool cmp_sport_ref(const sport_ref_t &l, const sport_ref_t &r) {
	return l.value > r.value || (l.value == r.value && l.key < r.key);
}

// Traduce un mapa a un vector de pares tipados igual que el mapa
std::vector<sport_ref_t> map_to_vector(std::map<std::string, int> const & map){
	std::vector<sport_ref_t> v;
	for (auto it = map.begin(); it != map.cend(); it++)
		v.push_back({ it->first, it->second });
	return v;
}

// Imprime el mapa traduciendolo a un vector y ordenandolo segun el orden requerido en el ejercicio
void printMap(std::map<std::string, int> const & map){
	std::vector<sport_ref_t> v = map_to_vector(map); 
	std::sort(v.begin(), v.end(), cmp_sport_ref);
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i].key << " " << v[i].value << "\n";
	std::cout << "***\n";
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	std::map<std::string, int> sports_map;
	std::map<std::string, std::string> students_map;
	std::string sport, nickname, elem;

	// leer los datos de la entrada y resolver simultaneamente
	std::cin >> elem;
	if (!std::cin)
		return false;
	while (elem != "_FIN_"){
		if (isupper(elem[0])){
			sport = elem;
			sports_map[sport] = 0;
		}
		else{
			nickname = elem;
			if (students_map.count(nickname)){
				if (students_map[nickname] != sport && students_map[nickname] != "none"){
					--sports_map[students_map[nickname]];
					students_map[nickname] = "none";
				}
			}
			else{
				++sports_map[sport];
				students_map[nickname] = sport;
			}
		}
		std::cin >> elem;
	}
	// escribir sol
	printMap(sports_map);
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
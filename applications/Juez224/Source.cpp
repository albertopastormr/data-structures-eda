// Alberto Pastor Moreno
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <list>
#include <map>

#define TOPBS_LEN 10

using libro = std::string;


struct libro_info_t{
	int num_ejemplares, num_vendidos;
	std::list<libro>::const_iterator bestsellers_it;
	libro_info_t() {}
	libro_info_t(int ne, int nv) : num_ejemplares(ne), num_vendidos(nv) {}
};

struct bs_comp{
	bool operator()(int const & l, int const & r) const {
		return l > r;
	}
};

class libreria {
private:
	std::unordered_map<libro, libro_info_t> libro_map;
	std::map<int, std::list<libro>, bs_comp> bestsellers_map;

public:
	void nuevoLibro(int const & num_ejemplares, libro const & nuevo_lib){ // O(1)
		auto lib_it = libro_map.find(nuevo_lib);
		if (lib_it == libro_map.cend()){
			libro_map.insert({ nuevo_lib, { num_ejemplares, 0 } });
			libro_map[nuevo_lib].bestsellers_it = bestsellers_map[0].cend();
		}
		else
			lib_it->second.num_ejemplares += num_ejemplares;
	}

	void comprar(libro const & lib){
		auto lib_it = libro_map.find(lib);
		if (lib_it != libro_map.cend()){
			if (lib_it->second.num_ejemplares > 0){
				if (lib_it->second.num_vendidos == 0)
					lib_it->second.bestsellers_it = bestsellers_map[1].insert(bestsellers_map[1].cend(), lib);
				else{
					bestsellers_map[lib_it->second.num_vendidos].erase(lib_it->second.bestsellers_it);
					lib_it->second.bestsellers_it = bestsellers_map[lib_it->second.num_vendidos + 1].insert(bestsellers_map[lib_it->second.num_vendidos + 1].cend(), lib);
				}
				--lib_it->second.num_ejemplares;
				++lib_it->second.num_vendidos;
			}
			else
				throw std::out_of_range("No hay ejemplares");
		}
		else
			throw std::invalid_argument("Libro no existente");
	}

	bool estaLibro(libro const & lib){ // O(1)
		return libro_map.count(lib) == 1;
	}

	void elimLibro(libro const & lib){ // O(1)
		if (libro_map.count(lib)){
			if (libro_map[lib].num_vendidos > 0)
				bestsellers_map[libro_map[lib].num_vendidos].erase(libro_map[lib].bestsellers_it);
			libro_map.erase(lib);
		}
	}

	int numEjemplares(libro const & lib){ // O(1)
		auto lib_it = libro_map.find(lib);
		if (lib_it != libro_map.cend()){
			return lib_it->second.num_ejemplares;
		}
		else
			throw std::invalid_argument("Libro no existente");
	}

	std::vector<libro> top10(){ // O(10)
		std::vector<libro> top10_vector;
		int top10_list_len = 0;
		auto bs_map_it = bestsellers_map.begin();
		while (bs_map_it != bestsellers_map.cend() && top10_list_len < TOPBS_LEN){
			auto bs_inner_list_it = bs_map_it->second.rbegin();
			while (bs_inner_list_it != bs_map_it->second.rend() && top10_list_len < TOPBS_LEN){
				top10_vector.push_back(*bs_inner_list_it);
				++top10_list_len;
				++bs_inner_list_it;
			}
			++bs_map_it;
		}
		return top10_vector;
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	libreria librer;
	int num_operaciones;
	std::string operacion_tag;
	// leer los datos de la entrada
	std::cin >> num_operaciones;
	if (!std::cin)
		return false;
	for (int i = 0; i < num_operaciones; ++i){
		std::cin >> operacion_tag;
		if (operacion_tag == "nuevoLibro"){
			int num_ejemplares;
			std::string lib;
			std::cin >> num_ejemplares;
			std::cin.get();
			std::getline(std::cin, lib);
			librer.nuevoLibro(num_ejemplares, lib);
		}
		else if (operacion_tag == "comprar"){
			std::string lib;
			std::cin.get();
			std::getline(std::cin, lib);
			try{
				librer.comprar(lib);
			}
			catch (std::out_of_range err){
				std::cout << err.what() << "\n";
				std::cout << "---\n";
			}
			catch (std::invalid_argument err){
				std::cout << err.what() << "\n";
				std::cout << "---\n";
			}
		}
		else if (operacion_tag == "estaLibro"){
			std::string lib;
			std::cin.get();
			std::getline(std::cin, lib);
			std::cout << (librer.estaLibro(lib) ? "El libro " + lib + " esta en el sistema\n" : "No existe el libro " + lib + " en el sistema\n");
			std::cout << "---\n";
		}
		else if (operacion_tag == "elimLibro"){
			std::string lib;
			std::cin.get();
			std::getline(std::cin, lib);
			librer.elimLibro(lib);
		}
		else if (operacion_tag == "numEjemplares"){
			std::string lib;
			std::cin.get();
			std::getline(std::cin, lib);
			try{
				int num_ejemplares = librer.numEjemplares(lib);
				std::cout << "Existen " << num_ejemplares << " ejemplares del libro " << lib << "\n";
			}
			catch (std::invalid_argument err){
				std::cout << "No existe el libro " << lib << " en el sistema\n";
			}
			std::cout << "---\n";
		}
		else if (operacion_tag == "top10"){
			std::vector<libro> out_list = librer.top10();
			for (libro lib : out_list)
				std::cout << lib << "\n";
			std::cout << "---\n";
		}
	}
	std::cout << "------\n";
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
// Alberto Pastor Moreno
// E46

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>

using alumno = std::string;
using profesor = std::string;

class autoescuela {
private:
	std::unordered_map<alumno, std::pair<int,profesor>> alumnos_map;
	std::unordered_map<profesor, std::unordered_set<alumno>> profesores_map;
public:
	// Leyenda referencias complejidad:
	//
	// N es el numero de alumnos, P es el numero de profesores, PA es el numero de profesores de un alumno, AP es el numero de alumnos de un profesor
	
	autoescuela(){}

	void alta(alumno const & alum, profesor const & new_prof){ // O(1)
		auto it_al = alumnos_map.find(alum);
		if (it_al != alumnos_map.cend()){
			// Baja profesor anterior
			profesor & old_prof = it_al->second.second;
			profesores_map[old_prof].erase(alum);
			if (profesores_map[old_prof].empty())
				profesores_map.erase(old_prof);
			// Alta nuevo profesor
			profesores_map[new_prof].insert(alum);
			// Modificacion alumno
			it_al->second.second = new_prof;
		}
		else{
			alumnos_map.insert({ alum, { 0, new_prof } });
			profesores_map[new_prof].insert(alum);
		}
	}


	bool es_alumno(alumno const & alum, profesor const& prof){ // O(1)
		auto it_al = alumnos_map.find(alum);
		if (it_al != alumnos_map.cend()){
			return it_al->second.second == prof;
		}
		else
			return false;
	}


	int puntuacion(alumno const & alum){
		auto it_al = alumnos_map.find(alum);
		if (it_al != alumnos_map.cend()){
			return it_al->second.first;
		}
		else
			throw std::domain_error("El alumno " + alum + " no esta matriculado");
	}


	void actualizar(alumno const & alum, int incremento_puntuacion){
		auto it_al = alumnos_map.find(alum);
		if (it_al != alumnos_map.cend()){
			it_al->second.first += incremento_puntuacion;
		}
		else
			throw std::domain_error("El alumno " + alum + " no esta matriculado");
	}


	std::vector<alumno> examen(profesor const & prof, int min_puntuacion){ // O( AP * log AP )
		std::unordered_set<alumno> const & alumnos_del_profesor = profesores_map[prof];
		std::vector<alumno> alumnos_examen;
		for (alumno const & it_al : alumnos_del_profesor){
			if (alumnos_map[it_al].first >= min_puntuacion)
				alumnos_examen.push_back(it_al);
		}
		std::sort(alumnos_examen.begin(), alumnos_examen.end());
		return alumnos_examen;
	}


	void aprobar(alumno const & alum){ // O(1)
		auto it_al = alumnos_map.find(alum);
		if (it_al != alumnos_map.cend()){
			profesores_map[it_al->second.second].erase(alum);
			alumnos_map.erase(alum);
		}
		else
			throw std::domain_error("El alumno " + alum + " no esta matriculado");
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	autoescuela autos;
	std::string operacion_tag;
	// leer los datos de la entrada
	std::cin >> operacion_tag;
	if (!std::cin)
		return false;
	while (operacion_tag != "FIN"){
		if (operacion_tag == "alta"){
			alumno alum;
			profesor prof;
			std::cin >> alum >> prof;
			try{
				autos.alta(alum, prof);
			}
			catch (std::domain_error err){
				std::cout << "ERROR\n";
			}
		}
		else if (operacion_tag == "es_alumno"){
			alumno alum;
			profesor prof;
			std::cin >> alum >> prof;
			try{
				std::cout << (autos.es_alumno(alum, prof) ? alum + " es alumno de " + prof : alum + " no es alumno de " + prof) << "\n";
			}
			catch (std::domain_error err){
				std::cout << "ERROR\n";
			}
		}
		else if (operacion_tag == "puntuacion"){
			alumno alum;
			std::cin >> alum;
			try{
				std::cout << "Puntuacion de " << alum << ": " << autos.puntuacion(alum) << "\n";
			}
			catch (std::domain_error err){
				std::cout << "ERROR\n";
			}
		}
		else if (operacion_tag == "actualizar"){
			alumno alum;
			int incremento_puntuacion;
			std::cin >> alum >> incremento_puntuacion;
			try{
				autos.actualizar(alum, incremento_puntuacion);
			}
			catch (std::domain_error err){
				std::cout << "ERROR\n";
			}
		}
		else if (operacion_tag == "examen"){
			profesor prof;
			int min_puntuacion;
			std::cin >> prof >> min_puntuacion;
			try{
				std::vector<alumno> out_alumnos = autos.examen(prof, min_puntuacion);
				std::cout << "Alumnos de " << prof << " a examen:\n";
				for (alumno const & it_al : out_alumnos)
					std::cout << it_al << "\n";
			}
			catch (std::domain_error err){
				std::cout << "ERROR\n";
			}
		}
		else if (operacion_tag == "aprobar"){
			alumno alum;
			std::cin >> alum;
			try{
				autos.aprobar(alum);
			}
			catch (std::domain_error err){
				std::cout << "ERROR\n";
			}
		}
		std::cin >> operacion_tag;
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
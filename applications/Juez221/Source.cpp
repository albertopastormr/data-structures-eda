// Alberto Pastor Moreno
// E46

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>
#include <map>

using medico = std::string;
using paciente = std::string;

struct fecha{
	int dia = 0, hora = 0, minuto = 0;
	fecha() : dia(0), hora(0), minuto(0) {}
	fecha(int d, int h, int m) : dia(d), hora(h), minuto(m) {}
	bool operator()(fecha const & left, fecha const & right){
		return left.dia < right.dia || (left.dia == right.dia && left.hora < right.hora) || (left.dia == right.dia && left.hora == right.hora && left.minuto < right.minuto);
	}
	bool operator<(fecha const & right) const {
		return dia < right.dia || (dia == right.dia && hora < right.hora) || (dia == right.dia && hora == right.hora && minuto < right.minuto);
	}
};

class consultorio : private std::unordered_map<medico, std::map<fecha,paciente> > {
	// N es el numero de medicos mientras F es el numero de fechas de su tabla dado un medico
public:
	void nuevoMedico(medico const & nuevo_med){ // O(1)
		insert({ nuevo_med, std::map<fecha, paciente>()});
	}
	void pideConsulta(paciente const& nuevo_pac, medico const& consult_med, fecha const & consult_fec){ // O(log F)
		auto it_med = find(consult_med);
		if (it_med != end()){
			if (!it_med->second.count(consult_fec)){
				it_med->second.insert({consult_fec, nuevo_pac});
			}
			else
				throw std::domain_error("Fecha ocupada");
		}
		else
			throw std::domain_error("Medico no existente");
	}
	paciente siguientePaciente(medico const & consult_med){ // O(1)
		auto it_med = find(consult_med);
		if (it_med != end()){
			if (!it_med->second.empty()){
				return it_med->second.cbegin()->second;
			}
			else
				throw std::domain_error("No hay pacientes");
		}
		else
			throw std::domain_error("Medico no existente");
	}
	void atiendeConsulta(medico const & consult_med){ // O(1)
		auto it_med = find(consult_med);
		if (it_med != end()){
			if (!it_med->second.empty()){
				it_med->second.erase(it_med->second.cbegin()->first);
			}
			else
				throw std::domain_error("No hay pacientes");
		}
		else
			throw std::domain_error("Medico no existente");
	}
	std::vector<std::pair<paciente,fecha>> listaPacientes(medico const & list_med, int consult_dia){
		std::vector<std::pair<paciente, fecha>> out_lista_pac;
		auto it_med = find(list_med);
		if (it_med != end()){
			auto it_fec = it_med->second.begin();
			while (it_fec != it_med->second.cend() && it_fec->first.dia <= consult_dia){
				if (it_fec->first.dia == consult_dia)
					out_lista_pac.push_back({ it_fec->second, it_fec->first });
				++it_fec;
			}
			return out_lista_pac;
		}
		else
			throw std::domain_error("Medico no existente");
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	consultorio clinica_map;
	int num_operaciones;
	std::string operacion_tag;
	// leer los datos de la entrada
	std::cin >> num_operaciones;
	if (!std::cin)
		return false;
	for (int i = 0; i < num_operaciones; i++){
		std::cin >> operacion_tag;
		if (operacion_tag == "nuevoMedico"){
			medico in_med;
			std::cin >> in_med;
			try{
				clinica_map.nuevoMedico(in_med);
			}
			catch (std::domain_error const& ex){
				std::cout << ex.what() << "\n---\n";
			}
		}
		else if (operacion_tag == "pideConsulta"){
			paciente in_pac;
			medico in_med;
			fecha in_fec;
			std::cin >> in_pac >> in_med >> in_fec.dia >> in_fec.hora >> in_fec.minuto;
			try{
				clinica_map.pideConsulta(in_pac, in_med, in_fec);
			}
			catch (std::domain_error const& ex){
				std::cout << ex.what() << "\n---\n";
			}
		}
		else if (operacion_tag == "siguientePaciente"){
			medico in_med;
			std::cin >> in_med;
			try{
				paciente out_pac = clinica_map.siguientePaciente(in_med);
				std::cout << "Siguiente paciente doctor " << in_med << "\n" << out_pac << "\n---\n";
			}
			catch (std::domain_error const & ex){
				std::cout << ex.what() << "\n---\n";
			}
		}
		else if (operacion_tag == "listaPacientes"){
			medico in_med;
			int in_dia;
			std::cin >> in_med >> in_dia;
			try{
				std::vector< std::pair<paciente, fecha> > consultas = clinica_map.listaPacientes(in_med, in_dia);
				std::cout << "Doctor " << in_med << " dia " << in_dia << "\n";
				for (std::pair<paciente,fecha> consulta : consultas)
					std::cout << consulta.first << " " << (consulta.second.hora < 10 ? "0" : "") << consulta.second.hora << ":" << (consulta.second.minuto < 10 ? "0" : "") << consulta.second.minuto << "\n";
				std::cout << "---\n";
			}
			catch (std::domain_error const& ex){
				std::cout << ex.what() << "\n---\n";
			}
		}
		else if (operacion_tag == "atiendeConsulta"){
			medico in_med;
			std::cin >> in_med;
			try{
				clinica_map.atiendeConsulta(in_med);
			}
			catch (std::domain_error const& ex){
				std::cout << ex.what() << "\n---\n";
			}
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
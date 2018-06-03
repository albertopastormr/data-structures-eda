// Alberto Pastor
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "horas.h"
#include "peliculas.h"

std::istream & operator>>(std::istream & in, horas & hora){
	int auxHora, auxMinuto, auxSegundo;
	char c;
	std::cin >> auxHora >> c >> auxMinuto >> c >> auxSegundo;
	hora = horas(auxHora, auxMinuto, auxSegundo);
	return in;
}

std::ostream & operator<<(std::ostream & out, horas const & hora){
	hora.print(out);
	return out;
}

std::ostream & operator<<(std::ostream & out, peliculas const & pelicula){
	pelicula.print(out);
	return out;
}

void print(std::vector<peliculas> const & v){
	for (peliculas p : v)
		std::cout << p << "\n";
}

// función que resuelve el problema
void resolver(std::vector<peliculas> & v) {
	std::sort(v.begin(), v.end());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int numPeliculas;
	std::cin >> numPeliculas;
	if (numPeliculas == 0)
		return false;
	std::vector<peliculas> v(numPeliculas);
	
	// Inicializacion del vector de peliculas
	for (int i = 0; i < numPeliculas; i++){
		// Cojo por entrada la hora de inicio, duracion y titulo de pelicula
		horas horaInicio, duracion;
		std::cin >> horaInicio >> duracion;
		std::string nombre;
		std::getline(std::cin, nombre);
		v[i] = peliculas(horaInicio, horaInicio + duracion, duracion, nombre); // La hora de fin sera la hora de inicio + duracion
	}

	// Funcion que ordena el vector de menor a mayor
	resolver(v);

	// Imprime el horario de peliculas ordenadas de menor a mayor por la hora de fin
	print(v);
	std::cout << "---\n";
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
// Alberto Pastor
// E46


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "horas.h"

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

horas busquedaHora(std::vector<horas> const & v, horas const & consulta, int ini, int fin){
	if (ini + 1 == fin){
		if (v[ini] < consulta){
			if (fin == v.size())
				throw std::domain_error("NO");
			else
				return v[ini + 1];
		}
		else
			return v[ini];
	}
	else{
		int mitad = (ini + fin) / 2;
		if (v[mitad] < consulta)
			return busquedaHora(v, consulta, mitad, fin);
		else
			return busquedaHora(v, consulta, ini, mitad);
	}
}
// función que resuelve el problema
horas resolver(std::vector<horas> const & v, horas consulta) {
	return busquedaHora(v, consulta, 0, v.size());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int numTrenes, numHoras;
	std::cin >> numTrenes >> numHoras;
	if (numTrenes == 0 && numHoras == 0)
		return false;
	std::vector<horas> v(numTrenes);
		// Inicializacion del vector v que contiene las horas del horario de la linea de tren
	for (int i = 0; i < numTrenes; i++){
		horas horaTren;
		try{
			std::cin >> horaTren;
		}
		catch (std::domain_error const & e){
			std::cout << e.what() << "\n";
		}
		v[i] = horaTren;
	}

	// Consulta de cada palabra de entrada
	for (int j = 0; j < numHoras; j++){
		horas consulta;
		try{
			std::cin >> consulta;
			horas sol = resolver(v, consulta);
			std::cout << sol;
		}
		catch (std::domain_error const & e){
			std::cout << e.what() << "\n";
		}
		// escribir sol
	}
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
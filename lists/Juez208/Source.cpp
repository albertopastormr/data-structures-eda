// Alberto Pastor Moreno
// E46

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include <list>

template <class T>
class modifiedList: public std::list<T> {
public:
	template <class Predicate>
	void remove_if(Predicate pred){
		auto it = this->begin();
		while (it != this->end()){
			if (pred(*it))
				it = this->erase(it);
			else
				it++;
		}
	}
};




class persona {
private:
	std::string nombre;
	int edad;
public:
	persona(){}
	persona(int auxEdad, std::string auxNombre) : edad (auxEdad), nombre (auxNombre){}
	std::string getNombre() const;
	int getEdad() const;
};

class viajero_valido{
private:
	int maxCond;
	int minCond;
public:
	viajero_valido(int minc, int maxc) : maxCond(maxc), minCond(minc){}
	bool operator()(persona const& viajero){
		return !(viajero.getEdad() <= maxCond && viajero.getEdad() >= minCond);
	}
};

std::string persona::getNombre() const {
	return nombre;
}

int persona::getEdad() const{
	return edad;
}

std::ostream& operator<<(std::ostream & out, persona const & right){
	out << right.getNombre();
	return out;
}



template <class T>
void print(modifiedList<T> const & viajeros){
	if (viajeros.size() > 0){
		for (auto it = viajeros.cbegin(); it != viajeros.cend(); it++)
			std::cout << *it << "\n";
	}
	std::cout << "---\n";
}
// función que resuelve el problema
template <class T>
void resolver(modifiedList<T>  & viajeros, int minEdad, int maxEdad) {
	viajeros.remove_if( viajero_valido(minEdad, maxEdad)  );
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int numPersonas, minEdad, maxEdad;
	std::cin >> numPersonas >> minEdad >> maxEdad;
	if (numPersonas == 0 && minEdad == 0 && maxEdad == 0)
		return false;
	modifiedList<persona > viajeros;
	for (int i = 0; i < numPersonas; i++){
		std::string nombre;
		int edad;
		std::cin >> edad;
		std::cin.get();
		getline(std::cin, nombre);
		persona aux(edad, nombre);
		viajeros.push_back(aux);
	}
	resolver(viajeros, minEdad, maxEdad);
	// escribir sol
	print(viajeros);
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
// Alberto Pastor Moreno
// E46

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "horas.h"
#include "queue_eda.h"


template <class T>
class modifiedQueue : public queue<T>{
	using Nodo = typename queue<T>::Nodo;
public:
	void elimina_posiciones_pares(){
		Nodo * actual = this->prim;
		int i = 0;
		while (actual->sig != nullptr){
			if (i % 2 == 0){
				Nodo * borrar = actual->sig;
				actual->sig = actual->sig->sig;
				delete borrar;
				this->nelems--;
			}
			else{
				actual = actual->sig;
			}
			i++;
		}
	}
	void print(){
		if (this->size() > 0){
			std::cout << this->front();
			Nodo * aux = this->prim->sig;
			for (int i = 1; i < this->size(); i++){
				std::cout << " " << aux->elem;
				aux = aux->sig;
			}
		}
		std::cout << "\n";
	}
};


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


// función que resuelve el problema
template <class T>
void resolver(modifiedQueue<T> & horario) {
	horario.elimina_posiciones_pares();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int numElem;
	std::cin >> numElem;
	if (numElem == 0)
		return false;
	modifiedQueue<horas> horario;
	for (int x = 0; x < numElem; x++){
		horas elem;
		std::cin >> elem;
		horario.push(elem);
	}
	resolver(horario);
	// escribir sol
	horario.print();
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
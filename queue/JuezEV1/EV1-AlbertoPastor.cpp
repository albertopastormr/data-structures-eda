// Alberto Pastor Moreno E46

#include <iostream>
#include <fstream>
using namespace std;

#include "queue_eda.h"

template <class T>
class InsertaElementos : public queue<T> {
	using Nodo = typename queue<T>::Nodo;
public:
	// imprime la lista enlazada
	void print(std::ostream & o = std::cout) const {
		if (this->size() > 0){
			Nodo * aux = this->prim;
			o << aux->elem; // Imprimo el primer elemento de forma especial para evitar insertar espacio al final de linea
			aux = aux->sig;
			while (aux != nullptr){
				o << " " << aux->elem;
				aux = aux->sig;
			}
		}
	}

	// inserta los elementos de elems (que se vacía) a partir de la posición P
	// 0 <= P <= nelems
	// La solucion implementada tiene coste O(n), siendo n el numero de elementos de this, ya si P == this->elems, iterare por todos los nodos de this
	void inserta(size_t P, InsertaElementos<T> & elems) {
		if (P == 0){ // En este caso apunto prim a la cola recibida y el ultimo elemento de la cola recibida al primer elemento de this
			Nodo * corte = this->prim;
			this->prim = elems.prim;
			elems.ult->sig = corte;
		}
		else{
			Nodo * antesCorte = this->prim; // Nodo auxiliar que, tras iterar, almacenara el nodo previo al corte, donde se inserta la lista elems
			long int end = P - 1;
			for (long int i = 0; i < end; i++)
				antesCorte = antesCorte->sig; // Itero hasta llegar a la posicion demandada por P
			Nodo * despuesCorte = antesCorte->sig; // Diferencio por los nodos de this antes de insertar la lista y despues de insertarla
			antesCorte->sig = elems.prim;
			elems.ult->sig = despuesCorte;
		}
		this->nelems += elems.nelems; // Aumento el numero de elementos con los nuevos introducidos proporcionados por elems
		elems.nelems = 0;
		elems.prim = elems.ult = nullptr; // Vacio la lista recibida por parametro
	}
};

template <class T>
inline std::ostream& operator<<(std::ostream & o, InsertaElementos<T> const& lista) {
	lista.print(o);
	return o;
}

bool resuelveCaso() {
	int N;
	cin >> N;
	if (!cin)
		return false;

	InsertaElementos<int> lista;
	for (size_t i = 0; i < N; ++i) {
		int num;
		cin >> num;
		lista.push(num);
	}

	int M, P;
	cin >> M >> P;

	InsertaElementos<int> nuevos;
	for (size_t i = 0; i < M; ++i) {
		int num;
		cin >> num;
		nuevos.push(num);
	}

	lista.inserta(P, nuevos);

	cout << lista << '\n';

	return true;
}

int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif

	return 0;
}

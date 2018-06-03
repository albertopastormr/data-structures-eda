#include "queue.h"

template <class T>
class ListaDuplica : public queue<T> {
	using Nodo = typename queue<T>::Nodo; // para poder usar Nodo aquí
public:
	void print(std::ostream & o = std::cout) const {
		Nodo * nodeAux = this->prim;
		o << nodeAux->elem;
		nodeAux = this->prim->sig;

		for (int i = 1; i < this->nelems; i++){
			o << ' ' << nodeAux->elem;
			nodeAux = nodeAux->sig;
		}
		o << '\n';
	}

	// Duplicar los nodos de una lista enlazada simple
	void duplica() {
		Nodo * nodeAux = this->prim;

		for (int i = 0; i < this->nelems; i++){
			Nodo * nextNode = nodeAux->sig;
			nodeAux->sig = new Nodo(nodeAux->elem, nextNode);
			nodeAux = nextNode;
		}

		this->nelems *= 2;
	}
};

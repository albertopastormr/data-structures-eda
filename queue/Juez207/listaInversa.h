#include "queue_eda.h"

template <class T>
class listaInversa : public queue<T> {
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
	void invierte() {
		if (this->nelems > 1){
			Nodo * nextNode = this->prim->sig;
			Nodo * auxNode = this->prim;

			this->prim->sig = nullptr;
			for (int i = 0; i < this->nelems - 1; i++){
				//Nodo * aux = new Nodo( nextNode->sig->elem , nextNode->sig );
				Nodo * aux = nextNode->sig;
				nextNode->sig = auxNode;
				auxNode = nextNode;
				nextNode = aux;
			}
			auxNode = this->prim;
			this->prim = this->ult;
			this->ult = auxNode;

		}
	}
};

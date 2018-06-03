
#include "polinomio.h"


void polinomio::insert(monomio elem){
	poli.push_back(elem);
}

bool operator<(monomio left, monomio right){
	return ((left.exp < right.exp) || (left.exp == right.exp && left.coef < right.exp));
}
void polinomio::sort(){
	std::sort(poli.begin(), poli.end());
}

long long int polinomio::valoracion(int valor){
	long long int sol = 0;
	for (int i = 0; i < poli.size(); i++)
		sol += poli[i].coef * (std::pow(valor, poli[i].exp));
	return sol;
}

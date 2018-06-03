

#ifndef polinomio_h
#define polinomio_h

#include <iostream>
#include <vector>
#include <algorithm>

struct monomio{
	int exp = 0, coef = 0;
};

class polinomio{
private:
	std::vector<monomio> poli;
public:
	polinomio(){}
	void insert(monomio elem);
	void sort();
	long long int valoracion(int valor);
};

#endif


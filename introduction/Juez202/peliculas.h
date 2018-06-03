#ifndef peliculas_h
#define peliculas_h

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept> 
#include "horas.h"

class peliculas{
public:
	peliculas();
	peliculas(horas auxInicio, horas auxFin, horas auxDuracion, std::string auxTitulo);
	void print(std::ostream & out = std::cout) const;
	bool operator<(peliculas const& right) const;
private:
	horas inicio, fin, duracion;
	std::string titulo;
};

#endif
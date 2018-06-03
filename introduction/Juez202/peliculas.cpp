#include "peliculas.h"
#include <string>

void peliculas::print(std::ostream & out) const {
	fin.print(out);
	out << " " << titulo;
}

peliculas::peliculas() : inicio(), fin(), duracion(), titulo() {}
peliculas::peliculas(horas auxInicio, horas auxFin, horas auxDuracion, std::string auxTitulo){
	inicio = auxInicio;
	fin = auxFin;
	duracion = auxDuracion;
	titulo = auxTitulo;
}

bool peliculas::operator<(peliculas const& right) const{
	return  ((fin < right.fin) || (fin == right.fin && titulo < right.titulo));
}
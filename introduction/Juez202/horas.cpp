#include "horas.h"
#include <string>

void horas::print(std::ostream & out) const {
	out << (hora<10 ? "0" + std::to_string(hora) : std::to_string(hora)) << ":" << (minuto<10 ? "0" + std::to_string(minuto) : std::to_string(minuto)) << ":" << (segundo<10 ? "0" + std::to_string(segundo) : std::to_string(segundo));
}

horas::horas() : hora(0), minuto(0), segundo(0) {}
horas::horas(int auxHora, int auxMinuto, int auxSegundo) : hora(0), minuto(0), segundo(0) {
	if (auxHora <= 23 && auxHora >= 0 && auxMinuto <= 59 && auxMinuto >= 0 && auxSegundo <= 59 && auxSegundo >= 0){
		hora = auxHora;
		minuto = auxMinuto;
		segundo = auxSegundo;
	}
	else
		throw std::domain_error("ERROR");
}

bool horas::operator<(horas const& right) const{
	return (hora < right.hora) || ((hora == right.hora) && (minuto < right.minuto)) || ((hora == right.hora) && (minuto == right.minuto) && (segundo < right.segundo));
}


bool horas::operator==(horas const& right) const{
	return (hora == right.hora && minuto == right.minuto && segundo == right.segundo);
}

horas horas::operator+(horas const & right) const {
	long int totalSegundos = hora * 3600 + minuto * 60 + segundo + right.hora * 3600 + right.minuto * 60 + right.segundo;
	return horas(totalSegundos / 3600, (totalSegundos % 3600) / 60, totalSegundos % 60);
}

#ifndef horas_h
#define horas_h

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept> 


class horas{
public:
	horas();
	horas(int auxHora, int auxMinuto, int auxSegundo);
	void print(std::ostream & out = std::cout) const;
	bool operator<(horas const& right) const;
	bool operator==(horas const& right) const;
	horas operator+(horas const & right) const;
private:
	int hora, minuto, segundo;
};

#endif
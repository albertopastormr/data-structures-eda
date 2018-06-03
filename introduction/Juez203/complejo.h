#ifndef complejo_h
#define complejo_h

#include <iostream>
#include <algorithm>
#include <math.h>

class complejo{
private:
	float real;
	float imagin;
public:
	complejo() : real(0), imagin(0) {}
	complejo(float auxReal, float auxImagin) : real(auxReal), imagin(auxImagin) {}
	complejo suma(complejo right);
	complejo producto(complejo right);
	float mod();
};

#endif
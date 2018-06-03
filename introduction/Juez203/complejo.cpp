

#include "complejo.h"



complejo  complejo::suma(complejo right){
	return complejo(real + right.real, imagin + right.imagin);
}
complejo complejo::producto(complejo right){
	return complejo(real*right.real - imagin*right.imagin, real*right.imagin + imagin*right.real);
}
float complejo::mod(){
	return std::sqrt( std::pow(real, 2) + std::pow(imagin, 2) );
}
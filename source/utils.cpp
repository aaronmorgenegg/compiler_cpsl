#include "utils.hpp"

void Error(std::string msg){
	// Output error and terminate, aka 'Whine Bitterly'
	std::cerr << msg << std::endl;
	exit(1);
}


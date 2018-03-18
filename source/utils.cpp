#include "utils.hpp"

void Error(std::string msg){
	// Output error and terminate, aka 'Whine Bitterly'
	std::cerr << msg << std::endl;
	exit(1);
}

std::string RemoveSeq(std::string str, char seq){
	// Returns a copy of str with all instances of given seq removed
	std::string str_copy(str);
	str_copy.erase(std::remove(str_copy.begin(), str_copy.end(), seq), str_copy.end());
	return str_copy;
}


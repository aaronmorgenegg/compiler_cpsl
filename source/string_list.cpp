#include "string_list.hpp"

int StringList::Store(std::string str){
	strings.push_back(str);
	return GetSize();
}

std::string StringList::Lookup(int index){
	return strings[index];
}

int StringList::GetSize(){
	return strings.size();
}


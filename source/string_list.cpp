#include "string_list.hpp"

int StringList::Store(std::string str){
	strings.push_back(str);
	return GetSize() - 1;
}

std::string StringList::Lookup(int index){
	return strings[index];
}

int StringList::GetSize(){
	return strings.size();
}


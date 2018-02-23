#include "string_list.hpp"

void StringList::Store(std::string str){
	strings.push_back(str);
}

std::string StringList::Lookup(int index){
	return strings[index];
}

int StringList::GetSize(){
	return strings.size();
}


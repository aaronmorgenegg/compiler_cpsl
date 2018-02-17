#pragma once

//Type.size -> (virtual) how much space the type needs
//inherited by simple type(int, char, string, bool), array, and record
class Type{
protected:
	int size;
};

class SimpleType: public Type {
public:
	SimpleType(){
		this->size = 4;
	}
};


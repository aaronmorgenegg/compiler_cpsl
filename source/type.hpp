#pragma once

//Type.size -> (virtual) how much space the type needs
//inherited by simple type(int, char, string, bool), array, and record
class Type{
public:
	int GetSize();
protected:
	int size;
};

class SimpleType: public Type {
public:
	SimpleType();
};


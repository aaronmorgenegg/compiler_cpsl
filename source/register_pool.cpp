#include "register_pool.hpp"

RegisterPool::RegisterPool(){
	std::string registers[18] = {"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
	            		     "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};
	for(int i = 0; i < 18; i++){
		this->available_registers.push_back(registers[i]);
	}
	
}

std::string RegisterPool::GetRegister(){
	std::string reg = available_registers.back();
	available_registers.pop_back();
	return reg;
}

void RegisterPool::ReleaseRegister(std::string reg){
        available_registers.push_back(reg);
}



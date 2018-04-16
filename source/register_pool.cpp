#include "register_pool.hpp"

RegisterPool::RegisterPool(){
	Initialize();
}

void RegisterPool::Initialize(){
	std::string registers[18] = {"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
                                     "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8"};
        for(int i = 0; i < 17; i++){
                this->available_registers.push_back(registers[i]);
        }
}

std::string RegisterPool::GetRegister(){
	if(available_registers.size() <=0) {
		std::cerr << "Error: Out of registers!" << std::endl;
		Initialize();
	}
	std::string reg = available_registers.back();
	available_registers.pop_back();
	return reg;
}

void RegisterPool::ReleaseRegister(std::string reg){
        available_registers.push_back(reg);
}



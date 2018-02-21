#pragma once
#include <string>
#include <vector>
#include <iostream>


class RegisterPool {
public:
	RegisterPool();
        std::string GetRegister();
        void ReleaseRegister(std::string reg);
private:
	std::vector<std::string> available_registers;
};

extern RegisterPool REGISTER_POOL;


#include <string>
#include <vector>
#include <iostream>

// const std::string AVAILABLE_REGISTERS[] = {"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
//       					   "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};

class RegisterPool {
public:
        static std::string GetRegister();
        static std::string ReleaseRegister(std::string reg);
};


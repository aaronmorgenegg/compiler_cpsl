#include <iostream>
#include <string>
#include "../../source/expressions.hpp"

bool TestAddConstants(){
	// test adding constants
	Expression * a = new Expression(5);
	Expression * b = new Expression(7);
	Expression * result = Add(a, b);
	return result->value==12;
}

bool TestAddRegs(){
	// test adding registers
	Expression * a = new Expression("$t0");
	Expression * b = new Expression("$t1");
	Expression * result = Add(a, b);
	return result->reg=="$t0";
}

bool TestAddMixed(){
	// test adding registers and constants
        Expression * a = new Expression("$t0");
        Expression * b = new Expression(5);
        Expression * result = Add(a, b);
        return result->reg=="$t0";
}

std::string RunExpressionsTests(){
	std::string results = "";
	int tests_passed = 0;
	int tests_failed = 0;
	
	if(TestAddConstants()){
		tests_passed++;
		results += "Test Passed : TestAddConstants\n";
	} else {
		tests_failed++;
		results += "Test Failed : TestAddConstants\n";
	}
	if(TestAddRegs()){
                tests_passed++;
                results += "Test Passed : TestAddRegs\n";
        } else {
                tests_failed++;
                results += "Test Failed : TestAddRegs\n";
        }
	if(TestAddMixed()){
                tests_passed++;
                results += "Test Passed : TestAddMixed\n";
        } else {
                tests_failed++;
                results += "Test Failed : TestAddMixed\n";
	}


	results += "\nExpression Tests Passed : " + std::to_string(tests_passed) + "\nExpression Tests Failed : " + std::to_string(tests_failed) + "\n\n";
	return results;
}


#include <iostream>
#include "DArray.hpp"

int main() {
	DArray ar1, ar2;
	
	ar1[10] = 10;
	ar1[3] = 5;
	
	int v1 = ar1[3]--;
	int v2 = --ar1[10];
	
	std::cout << v1 << ' ' << v2 << std::endl;
	
	for (int i = 0; i < ar1.size(); i++) std::cout << ar1.get_data()[i] << ' ';
	std::cout << std::endl;
	return 0;
}
#include <iostream>
#include "DArray.hpp"

int main() {
	DArray ar1, ar2;
	
	for (int i = 0; i < 10; i++) ar1.push_back(i+1);
	for (int i = 0; i < 5; i++) ar2.push_back(i+15);
	
	DArray ar3 = ar1 + ar2;
	
	std::cout << ar3.size() << " " << ar3.get_capacity() << std::endl;
	
	for (int i = 0; i < ar3.size(); i++) {
		std::cout << ar3.get_data()[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < ar2.size(); i++) {
		std::cout << ar2.get_data()[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < ar1.size(); i++) {
		std::cout << ar1.get_data()[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
#include <iostream>
#include "Map.h"

int main()
{
	Map<std::string, int> map;
	std::cout << "** add 10 elements **" << std::endl;
	for (auto i = 0; i < 10; ++i) {
		std::string key = "hey" + std::to_string(i);
		map.insert(key, i);
	}
	map.print();
	std::cout << "** remove 5 elements **" << std::endl;
	for (auto i = 0; i < 10; i += 2) {
		std::string key = "hey" + std::to_string(i);
		map.remove(key);
	}
	map.print();
	std::cout << "** clear map **" << std::endl;
	map.clear();
	map.print();
}

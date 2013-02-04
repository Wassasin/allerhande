#include <iostream>

#include "interface.hpp"

int main(int argc, char **argv)
{
	using namespace allerhande;

	interface iface;

	for(size_t i = 0; i < 10000; i += 60)
		for(auto id : iface.fetch_index(i))
			std::cout << id << std::endl;
}

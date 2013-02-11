#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "interface.hpp"
#include "parsers/recipe_parser.hpp"

int main(int argc, char **argv)
{
	using namespace allerhande;

	/*interface iface;

	for(size_t i = 0; i < 12500; i += 60)
		for(auto id : iface.fetch_index(i))
		{
			std::cout << id << std::endl;
			iface.fetch_recipe(id);
		}*/
	
	typedef boost::filesystem::directory_iterator dir_itr_t;
	
	dir_itr_t end_itr;
	for(dir_itr_t itr("recipes"); itr != end_itr; ++itr)
	{
		boost::filesystem::ifstream fh(itr->path());
		std::string src;
		recipe_parser p;
		
		auto recipe = p.parse<std::istream&>(fh);
		std::cout << recipe.name << std::endl;
		
		fh.close();
	}
}

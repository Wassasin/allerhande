#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "interface.hpp"
#include "parsers/ah_recipe_parser.hpp"
#include "parsers/ww_category_parser.hpp"

#include "serialization/json_serializer.hpp"
#include "serialization/serialize_fusion.hpp"

int main(int argc, char **argv)
{
	using namespace allerhande;

	/*interface iface;
	
	iface.ww_fetch_index();*/
	
	/*
	for(size_t i = 0; i < 12500; i += 60)
		for(auto id : iface.fetch_index(i))
		{
			std::cout << id << std::endl;
			iface.fetch_recipe(id);
		}*/
	
	/*typedef boost::filesystem::directory_iterator dir_itr_t;
	
	dir_itr_t end_itr;
	for(dir_itr_t itr("recipes"); itr != end_itr; ++itr)
	{
		std::unique_ptr<serializer> s(new json_serializer());
		boost::filesystem::ifstream fh(itr->path());
		std::string src;
		ah_recipe_parser p;
		
		auto recipe = p.parse<std::istream&>(fh);
		serialize(s, "recipe", recipe);
		std::cout << s->str() << std::endl;
		
		fh.close();
	}*/
	
	typedef boost::filesystem::directory_iterator dir_itr_t;
	
	dir_itr_t end_itr;
	for(dir_itr_t itr("products"); itr != end_itr; ++itr)
	{
		boost::filesystem::ifstream fh(itr->path());
		ww_category_parser p([&](ww_category_parser::product p) { std::cout << p.name << ", " << p.yield << " [" << p.price << "]" << std::endl; });
		
		p.parse<std::istream&>(fh);
		
		fh.close();
	}
}

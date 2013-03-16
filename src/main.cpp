/*#include <iostream>

#include "parsers/ah_recipe_parser.hpp"
#include "parsers/ww_category_parser.hpp"

#include "serialization/json_serializer.hpp"
#include "serialization/serialize_fusion.hpp"
*/

#include "cli.hpp"

int main(int argc, char **argv)
{
	return allerhande::cli::main(argc, argv);
	
	/*interface iface;
	
	iface.ww_fetch_index();*/
	
	/*typedef boost::filesystem::directory_iterator dir_itr_t;
	
	dir_itr_t end_itr;
	for(dir_itr_t itr("products"); itr != end_itr; ++itr)
	{
		boost::filesystem::ifstream fh(itr->path());
		ww_category_parser p([&](ww_category_parser::product p) { std::cout << p.name << ", " << p.yield << " [" << p.price << "]" << std::endl; });
		
		p.parse<std::istream&>(fh);
		
		fh.close();
	}*/
}

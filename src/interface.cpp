#include "interface.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

#include "parsers/ah_index_parser.hpp"
#include "parsers/ah_recipe_parser.hpp"
#include "parsers/ww_main_parser.hpp"

namespace allerhande
{
	interface::interface()
	: dl("allerhande-scraper/1.0")
	{}
	
	std::vector<uint64_t> interface::ah_fetch_index(size_t i) const
	{
		std::vector<uint64_t> result;
	
		std::stringstream url;
		url << "http://www.ah.nl/allerhande/recepten/vinden/?lp_fromIndex=" << i;
		
		ah_index_parser p([&](uint64_t id) { result.emplace_back(id); });
		p.parse(dl.fetch(url.str()));
		
		return result;
	}
	
	void interface::ah_fetch_recipe(uint64_t id) const
	{
		std::stringstream url;
		url << "http://www.ah.nl/allerhande/recepten/" << id;
		
		//ah_recipe_parser p;
		//p.parse(dl.fetch(url.str()));
		
		std::ofstream fh;
		fh.open(std::string("recipes/") + boost::lexical_cast<std::string>(id));
		fh << dl.fetch(url.str());
		fh.close();
	}
	
	void interface::ww_fetch_index() const
	{
		ww_main_parser p([&](ww_main_parser::shelf r) { std::cout << r.title << std::endl; });
		p.parse(dl.fetch("http://webwinkel.ah.nl/"));
	}
}

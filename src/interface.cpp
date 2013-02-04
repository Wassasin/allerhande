#include "interface.hpp"

#include <sstream>
#include <iostream>

#include "parsers/index_parser.hpp"
#include "parsers/recipe_parser.hpp"

namespace allerhande
{
	interface::interface()
	: dl("allerhande-scraper/1.0")
	{}
	
	std::vector<uint64_t> interface::fetch_index(size_t i) const
	{
		std::vector<uint64_t> result;
	
		std::stringstream url;
		url << "http://www.ah.nl/allerhande/recepten/vinden/?lp_fromIndex=" << i;
		
		index_parser p([&](uint64_t id) { result.emplace_back(id); });
		p.parse(dl.fetch(url.str()));
		
		return result;
	}
	
	void interface::fetch_recipe(size_t id) const
	{
		std::stringstream url;
		url << "http://www.ah.nl/allerhande/recepten/" << id;
		
		recipe_parser p;
		p.parse(dl.fetch(url.str()));
	}
}

#include "interface.hpp"

#include <sstream>
#include <iostream>

namespace allerhande
{
	interface::interface()
	: dl("allerhande-scraper/1.0")
	{}
	
	void interface::fetch_index(size_t i) const
	{
		std::stringstream url;
		url << "http://www.ah.nl/allerhande/recepten/vinden/?lp_fromIndex=" << i;
		
		std::cout << dl.fetch(url.str()) << std::endl;
	}
	
	void interface::fetch_recipe(size_t id) const
	{
		//
	}
}

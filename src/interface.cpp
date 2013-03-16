#include "interface.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

#include "parsers/ah_index_parser.hpp"
#include "parsers/ah_recipe_parser.hpp"
#include "parsers/ww_main_parser.hpp"
#include "parsers/ww_shelf_parser.hpp"

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
	
	std::string interface::ah_fetch_recipe(uint64_t id) const
	{
		std::stringstream url;
		url << "http://www.ah.nl/allerhande/recepten/" << id;
		return dl.fetch(url.str());
	}
	
	void interface::ww_fetch_index() const
	{
		const static size_t scrape_size = 120;
		std::vector<ww_shelf_parser::category> categories;
		
		{
			std::vector<ww_main_parser::shelf> shelves;
		
			{
				ww_main_parser p([&](ww_main_parser::shelf s) { shelves.emplace_back(s); });
				p.parse(dl.fetch("http://webwinkel.ah.nl/"));
			}
		
			for(auto s : shelves)
			{
				std::cout << s.title << std::endl;
				
				std::stringstream url;
				url << "http://webwinkel.ah.nl";
				url << s.uri;
			
				ww_shelf_parser p([&](ww_shelf_parser::category c) { categories.emplace_back(c); });
				p.parse(dl.fetch(url.str()));
			}
		}
		
		for(auto c : categories)
		{
			for(size_t i = 0; i < c.item_count; i += scrape_size)
			{
				std::cout << c.title << " (" << c.item_count << " items, from " << i << ")" << std::endl;
			
				std::stringstream url;
				url << "http://webwinkel.ah.nl";
				url << c.uri;
				url << "&fh_view_size=" << scrape_size;
				url << "&fh_start_index=" << i;
				
				std::stringstream file;
				file << "products/" << c.title << " " << i;
				
				std::ofstream fh;
				fh.open(file.str());
				fh << dl.fetch(url.str());
				fh.close();
			}
		}
	}
}

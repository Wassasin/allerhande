#pragma once

#include <limits>
#include <sstream>
#include <boost/filesystem.hpp>

#include "interface.hpp"

namespace allerhande
{
	class scraper
	{
		scraper(scraper&) = delete;
		void operator=(scraper&) = delete;
		
	public:
		static std::string allerhande_path(uint64_t recipe_id)
		{
			std::stringstream s;
			s << "cache/allerhande/" << recipe_id;
			return s.str();
		}
		
		static void scrape_allerhande()
		{
			size_t additions = 0;
			interface iface;
		
			for(size_t i = 0; i < std::numeric_limits<size_t>().max(); i += 60)
			{
				bool encountered_old = false;
			
				for(auto id : iface.ah_fetch_index(i))
				{
					std::string path = allerhande_path(id);
				
					if(boost::filesystem::exists(path))
					{
						encountered_old = true;
						break;
					}
					
					std::ofstream fh;
					fh.open(path);
					fh << iface.ah_fetch_recipe(id);
					fh.close();
					
					++additions;
					
					std::cout << "Fetched recipe #" << id << std::endl;
				}
				
				if(encountered_old)
					break;
			}
			
			std::cout << "Added " << additions << " new recipes" << std::endl;
		}
	};
}

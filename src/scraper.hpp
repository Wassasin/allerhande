#pragma once

#include <limits>

#include "cache.hpp"
#include "interface.hpp"

namespace allerhande
{
	class scraper
	{
		scraper(scraper&) = delete;
		void operator=(scraper&) = delete;
		
	public:
		static void scrape_allerhande()
		{
			size_t additions = 0;
			interface iface;
		
			for(size_t i = 0; i < std::numeric_limits<size_t>().max(); i += interface::ah_page_size)
			{
				bool encountered_old = false;
			
				for(auto id : iface.ah_fetch_index(i))
				{
					if(cache::allerhande_exists(id))
					{
						encountered_old = true;
						break;
					}
					
					cache::allerhande_put(id, iface.ah_fetch_recipe(id));					
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

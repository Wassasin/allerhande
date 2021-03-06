#pragma once

#include <vector>

#include "util/downloader.hpp"

namespace allerhande
{
	class interface
	{
	private:
		downloader dl;
	
	public:
		interface();
	
		static const size_t ah_page_size = 60;
		std::vector<uint64_t> ah_fetch_index(size_t i) const;
		std::string ah_fetch_recipe(uint64_t id) const;
		
		void ww_fetch_index() const;
	};
}

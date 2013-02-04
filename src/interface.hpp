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
	
		std::vector<uint64_t> fetch_index(size_t i) const;
		void fetch_recipe(size_t id) const;
	};
}

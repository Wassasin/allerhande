#pragma once

#include "util/downloader.hpp"

namespace allerhande
{
	class interface
	{
	private:
		downloader dl;
	
	public:
		interface();
	
		void fetch_index(size_t i) const;
		void fetch_recipe(size_t id) const;
	};
}

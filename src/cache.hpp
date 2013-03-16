#pragma once

#include <sstream>
#include <boost/filesystem.hpp>

namespace allerhande
{
	class cache
	{
		cache(cache&) = delete;
		void operator=(cache&) = delete;
	
		static void put(const std::string path, const std::string str)
		{
			std::ofstream fh;
			fh.open(path);
			fh << str;
			fh.close();
		}
	
		static bool exists(const std::string path)
		{
			return boost::filesystem::exists(path);
		}
	
	public:
		static std::string allerhande_basepath()
		{
			return "cache/allerhande/";
		}
		
		static std::string allerhande_path(uint64_t recipe_id)
		{
			std::stringstream s;
			s << allerhande_basepath() << recipe_id;
			return s.str();
		}
		
		static void allerhande_put(uint64_t recipe_id, const std::string str)
		{
			put(allerhande_path(recipe_id), str);
		}
		
		static bool allerhande_exists(uint64_t recipe_id)
		{
			return exists(allerhande_path(recipe_id));
		}
	};
}

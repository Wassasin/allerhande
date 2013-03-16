#pragma once

#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "parsers/ah_recipe_parser.hpp"
#include "parsers/ww_category_parser.hpp"

#include "serialization/json_serializer.hpp"
#include "serialization/serialize_fusion.hpp"

namespace allerhande
{
	class updater
	{
		updater(updater&) = delete;
		void operator=(updater&) = delete;
		
	public:
		updater()
		{}
	
		void from_allerhande()
		{
			typedef boost::filesystem::directory_iterator dir_itr_t;
			size_t i = 0;
	
			dir_itr_t end_itr;
			for(dir_itr_t itr("recipes"); itr != end_itr; ++itr)
			{
				std::unique_ptr<serializer> s(new json_serializer());
				boost::filesystem::ifstream fh(itr->path());
				ah_recipe_parser p;
		
//				auto recipe = p.parse<std::istream&>(fh);
//				serialize(s, "recipe", recipe);
//				std::cout << s->str() << std::endl;
		
				fh.close();
				++i;
			}
			
			std::cout << i << std::endl;
		}
		
		void from_albert()
		{
			//
		}
	};
}

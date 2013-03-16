#pragma once

#include <fstream>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/regex.hpp>

#include "parsers/ah_recipe_parser.hpp"

#include "cache.hpp"
#include "database.hpp"

namespace allerhande
{
	class updater
	{
		updater(updater&) = delete;
		void operator=(updater&) = delete;
		
	public:
		updater()
		{}
	
		database::unit parse_unit(const std::string str)
		{
			if(str == "gram")
				return database::unit::gram;
			else if(str == "liter")
				return database::unit::liter;
			else if(str == "persoon" || str == "personen")
				return database::unit::person;
			else if(str == "stuk" || str == "stuks")
				return database::unit::quantity;
			else
				throw std::runtime_error(std::string("Unknown unit ")+str);
		}
	
		database::amount parse_amount(const std::string str)
		{
			const static boost::regex regex("([0-9]+) ([a-z]+)");
			
			boost::smatch match;
			if(!boost::regex_match(str, match, regex))
				throw std::runtime_error(std::string("Could not match ")+str);
			
			return database::amount(boost::lexical_cast<double>(match[1]), parse_unit(match[2]));
		}
	
		database::recipe handle(const ah_recipe_parser::recipe origin)
		{
			database::recipe result(origin.name, parse_amount(origin.yield));
			
			return result;
		}
	
		void from_allerhande()
		{
			typedef boost::filesystem::directory_iterator dir_itr_t;

			dir_itr_t itr(cache::allerhande_basepath()), end_itr;
			const auto f = [&](decltype(*itr) x)
			{
				const std::string identifier = x.path().filename().string();
				
				boost::filesystem::ifstream fh(x.path());
				ah_recipe_parser p;
		
				auto origin = p.parse<std::istream&>(fh);
		
				fh.close();
				
				database::recipe r = handle(origin);
				std::cout << r.name << std::endl;
			};
			std::for_each(itr, end_itr, f);
		}
		
		void from_albert()
		{
			//
		}
	};
}

#pragma once

#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#include "updater.hpp"
#include "scraper.hpp"

namespace allerhande
{
	class cli
	{
		cli() = delete;
		cli(cli&) = delete;
		void operator=(cli&) = delete;
		
		enum class source_e
		{
			allerhande,
			albert
		};
		
		enum class command_e
		{
			scrape,
			update
		};
	
	public:
	
		static boost::optional<source_e> to_source(const std::string& s)
		{
			if(s == "allerhande")
				return source_e::allerhande;
			else if(s == "albert")
				return source_e::albert;
			else
				return boost::optional<source_e>();
		}
		
		static boost::optional<command_e> to_command(const std::string& s)
		{
			if(s == "scrape")
				return command_e::scrape;
			else if(s == "update")
				return command_e::update;
			else
				return boost::optional<command_e>();
		}
		
		static void update_db(source_e source)
		{
			updater u;
			
			switch(source)
			{
				case source_e::allerhande:
					u.from_allerhande();
					break;
				case source_e::albert:
					u.from_albert();
					break;
			}
		}
		
		static void scrape(source_e source)
		{
			switch(source)
			{
				case source_e::allerhande:
					scraper::scrape_allerhande();
					break;
				case source_e::albert:
					break;
			}
		}
		
		static int main(int argc, char** argv)
		{
			std::string source_str = "allerhande";
			std::string command_str = "";

			boost::program_options::options_description o_general("General options");
			o_general.add_options()
			("help,h", "display this message");
	
			boost::program_options::options_description o_scrape("Scraping options");
			o_scrape.add_options()
			("source", boost::program_options::value<decltype(source_str)>(&source_str), "the source to be processed");
			
			boost::program_options::options_description o_hidden("Hidden options");
			o_hidden.add_options()
			("command", boost::program_options::value<decltype(command_str)>(&command_str), "command to execute");

			boost::program_options::variables_map vm;
			boost::program_options::positional_options_description pos;
			pos.add("command", -1);
			
			boost::program_options::options_description options("Allowed options");
			options.add(o_general).add(o_scrape).add(o_hidden);
	
			try
			{
				boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options).positional(pos).run(), vm);
			} catch(boost::program_options::unknown_option &e)
			{
				std::cerr << "Unknown option --" << e.get_option_name() << ", see --help" << std::endl;
				return -1;
			}
			
			if(vm.count("help"))
			{
				std::cout
					<< "Scraper for the Albert Heijn recipe page Allerhande and webshop Albert. [https://github.com/Wassasin/allerhande]" << std::endl
					<< "Usage: ./allerhande [options] <command>" << std::endl
					<< std::endl
					<< o_general << std::endl
					<< o_scrape << std::endl
					<< "Sources:" << std::endl
					<< "  allerhande  - recipe collection on http://www.ah.nl/allerhande/recepten/ (default)" << std::endl
					<< "  albert      - product shop on http://webwinkel.ah.nl" << std::endl
					<< std::endl
					<< "Commands:" << std::endl
					<< "  scrape      - updates the local cache by scraping the source" << std::endl
					<< "  update      - interactively update the recipe database" << std::endl;
				
				return 0;
			}
			
			try
			{
				boost::program_options::notify(vm);
			} catch(const boost::program_options::required_option &e)
			{
				std::cerr << "You forgot this: " << e.what() << std::endl;
				return -1;
			}
			
			auto const source = to_source(source_str);
			if(!source)
			{
				std::cerr << "Unknown source \"" << source_str << "\", see --help" << std::endl;
				return -1;
			}
			
			auto const command = to_command(command_str);
			if(!command)
			{
				if(command_str == "")
					std::cerr << "Please specify a command, see --help" << std::endl;
				else
					std::cerr << "Unknown command \"" << command_str << "\", see --help" << std::endl;
					
				return -1;
			}
			
			switch(command.get())
			{
				case command_e::update:
					update_db(source.get());
					return 0;
				case command_e::scrape:
					scrape(source.get());
					return 0;
			}
		}
	};
}

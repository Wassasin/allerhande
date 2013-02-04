#pragma once

#include <SAX/helpers/DefaultHandler.hpp>

namespace allerhande
{
	class html_parser
	{
	public:
		typedef Arabica::SAX::DefaultHandler<std::string> default_handler;
	
		html_parser() = delete;
		
		static void parse(const std::string src, default_handler& p);
	};
}

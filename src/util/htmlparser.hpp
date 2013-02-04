#pragma once

#include <SAX/helpers/DefaultHandler.hpp>

namespace allerhande
{
	class htmlparser
	{
	public:
		typedef Arabica::SAX::DefaultHandler<std::string> defaulthandler;
	
		htmlparser() = delete;
		
		static void parse(const std::string src, defaulthandler& p);
	};
}

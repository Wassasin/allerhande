#include "htmlparser.hpp"

#include <Taggle/Taggle.hpp>

namespace allerhande
{
	void htmlparser::parse(const std::string src, defaulthandler& p)
	{
		Arabica::SAX::Taggle<std::string> parser;

		parser.setContentHandler(p);
		parser.setErrorHandler(p);

		std::istringstream ss(src);
		Arabica::SAX::InputSource<std::string> is(ss);

		parser.parse(is);
	}
}

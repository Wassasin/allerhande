#include "html_parser.hpp"

#include <Taggle/Taggle.hpp>

namespace allerhande
{
	void html_parser::parse(const std::string src, default_handler& p)
	{
		Arabica::SAX::Taggle<std::string> parser;

		parser.setContentHandler(p);
		parser.setErrorHandler(p);

		std::istringstream ss(src);
		Arabica::SAX::InputSource<std::string> is(ss);

		parser.parse(is);
	}
}

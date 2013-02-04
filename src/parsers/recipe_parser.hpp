#pragma once

#include <boost/lexical_cast.hpp>

#include "../util/html_parser.hpp"

namespace allerhande
{
	class recipe_parser : public html_parser::default_handler
	{
	public:
		//typedef std::function<void(uint64_t)> callback_t;
	
	private:
		//callback_t f;
	
	public:
		recipe_parser()
		{}
	
		void parse(const std::string& source)
		{
			html_parser::parse(source, *this);
		}
	
		virtual void startElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& qName, const AttributesT& atts)
		{
			//
		}
		
		virtual void characters(const std::string& ch)
		{
			//
		}
		
		virtual void endElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& qName)
		{
			//
		}
	};
}

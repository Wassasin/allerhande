#pragma once

#include <boost/lexical_cast.hpp>

#include "../util/html_parser.hpp"

namespace allerhande
{
	class ww_main_parser : public html_parser::default_handler
	{
	public:
		struct shelf
		{
			std::string title, uri;
		};
		
		typedef std::function<void(shelf)> callback_t;
		
	private:
		enum state_e {
			S_INIT,
			S_SHELVES,
			S_DONE
		};
	
		state_e s;
		callback_t f;
	
	public:
		ww_main_parser(callback_t f)
		: s(S_INIT)
		, f(f)
		{}
	
		template<typename T>
		void parse(T source)
		{
			html_parser::parse(source, *this);
		}
	
		virtual void startElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& qName, const AttributesT& atts)
		{
			switch(s)
			{
			case S_INIT:
				if(qName == "div" && atts.getValue("id") == "shelves")
					s = S_SHELVES;
			break;
			case S_SHELVES:
				if(qName == "a")
					f({atts.getValue("title"), atts.getValue("href")});
			break;
			case S_DONE:
				//Do nothing
			break;
			}
		}
		
		virtual void endElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& qName)
		{
			switch(s)
			{
			case S_SHELVES:
				if(qName == "div")
					s = S_DONE;
			break;
			case S_INIT:
			case S_DONE:
				//Do nothing
			break;
			}
		}
	};
}

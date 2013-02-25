#pragma once

#include <memory>
#include <boost/lexical_cast.hpp>

#include "../util/html_parser.hpp"
#include "../util/html_recorder.hpp"
#include "../util/util.hpp"

namespace allerhande
{
	class ww_shelf_parser : public html_parser::default_handler
	{
	public:
		struct category
		{
			std::string title, uri;
		};
		
		typedef std::function<void(category)> callback_t;
		
	private:
		enum state_e {
			S_INIT,
			S_CATEGORIES,
			S_DONE
		};
	
		state_e s;
		callback_t f;
		boost::optional<html_recorder> rec;
	
	public:
		ww_shelf_parser(callback_t f)
		: s(S_INIT)
		, f(f)
		, rec()
		{}
	
		template<typename T>
		void parse(T source)
		{
			html_parser::parse(source, *this);
		}
	
		virtual void startElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& qName, const AttributesT& atts)
		{
			if(rec)
				rec.get().startElement();
			
			switch(s)
			{
			case S_INIT:
				if(qName == "div" && atts.getValue("class") == "category_links")
					s = S_CATEGORIES;
			break;
			case S_CATEGORIES:
				if(qName == "a")
				{
					std::string uri = atts.getValue("href");
					rec = html_recorder([uri,this](std::string ch) { f({util::sanitize(ch), uri}); });
				}
			break;
			case S_DONE:
				//Do nothing
			break;
			}
		}
		
		virtual void characters(const std::string& ch)
		{
			if(rec)
				rec.get().characters(ch);
		}
		
		virtual void endElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& qName)
		{
			if(rec && rec.get().endElement())
				rec = boost::none;
			
			switch(s)
			{
			case S_CATEGORIES:
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

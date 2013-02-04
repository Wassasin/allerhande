#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

#include "../util/html_parser.hpp"
#include "../util/html_recorder.hpp"

namespace allerhande
{
	class recipe_parser : public html_parser::default_handler
	{
	public:
		//typedef std::function<void(uint64_t)> callback_t;
	
	private:
		boost::optional<html_recorder> rec;
		
		//callback_t f;
	
	public:
		recipe_parser()
		: rec()
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
		
			if(atts.getValue("data-title") != "")
				rec = html_recorder([&](std::string ch) { std::cout << ch << std::endl; });
			//else if(atts.getValue("class") == "course")
			//	rec = html_recorder([&](std::string& ch) { recipe.course });
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
		}
	};
}

#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>

#include "../util/html_parser.hpp"
#include "../util/html_recorder.hpp"

namespace allerhande
{
	class recipe_parser : public html_parser::default_handler
	{
	public:
		struct recipe
		{
			std::string name, type, yield;
			std::vector<std::string> ingredients;
		};
	
	private:
		boost::optional<html_recorder> rec;
		recipe current_r;
		
		static inline std::string sanitize(const std::string& str)
		{
			std::stringstream is(str);
			std::string result;
			
			while(is.peek() != std::char_traits<char>::eof())
			{
				std::string tmp;
				is >> tmp;
				
				if(!result.empty())
					result.append(" ");
				
				result.append(tmp);
			}
			
			return result;
		}
	
	public:
		recipe_parser()
		: rec()
		, current_r()
		{}
	
		template<typename T>
		recipe parse(T source)
		{
			html_parser::parse(source, *this);
			return current_r;
		}
	
		virtual void startElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& qName, const AttributesT& atts)
		{
			if(rec)
				rec.get().startElement();
		
			if(atts.getValue("data-title") != "" && atts.getValue("class") == "fn")
			{
				current_r = recipe();
				rec = html_recorder([&](std::string ch) { current_r.name = sanitize(ch); });
			}
			else if(atts.getValue("class") == "course")
				rec = html_recorder([&](std::string ch) { current_r.type = sanitize(ch); });
			else if(atts.getValue("class") == "yield")
				rec = html_recorder([&](std::string ch) { current_r.yield = sanitize(ch); });
			else if(atts.getValue("class") == "ingredient")
				rec = html_recorder([&](std::string ch) { current_r.ingredients.emplace_back(sanitize(ch)); });
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

#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../util/html_parser.hpp"
#include "../util/html_recorder.hpp"
#include "../util/html_watcher.hpp"
#include "../util/util.hpp"

namespace allerhande
{
	class ww_category_parser : public html_parser::default_handler
	{
	public:
		struct product
		{
			std::string name, yield, price;
		};
		
		typedef std::function<void(product)> callback_t;
	
	private:
		enum state_e {
			S_INIT,
			S_PRODUCT,
			S_PRODUCT_INFO
		};
	
		boost::optional<html_recorder> rec;
		html_watcher_collection wc;
		
		product current_p;
		state_e s;
		
		callback_t f;
	
	public:
		ww_category_parser(callback_t f)
		: rec()
		, wc()
		, current_p()
		, s(S_INIT)
		, f(f)
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
			
			wc.startElement();
		
			switch(s)
			{
			case S_INIT:
				if(qName == "div" && atts.getValue("class") == "product")
				{
					s = S_PRODUCT;
					wc.add([&]() {
						s = S_INIT;
						f(current_p);
						current_p = product();
					});
				}
			break;
			case S_PRODUCT:
				if(qName == "div" && atts.getValue("class") == "product_info")
				{
					s = S_PRODUCT_INFO;
					wc.add([&]() { s = S_PRODUCT; });
				}
				else if(atts.getValue("class") == "p_promo" || atts.getValue("class") == "p_price")
					rec = html_recorder([&](std::string ch) { current_p.price = util::sanitize(ch); });  
			break;
			case S_PRODUCT_INFO:
				if(qName == "h4")
					rec = html_recorder([&](std::string ch) { current_p.name = util::sanitize(ch); });
				else if(qName == "p" && atts.getValue("class") == "")
					rec = html_recorder([&](std::string ch) { current_p.yield = util::sanitize(ch); });
			break;
			}
		}
		
		virtual void characters(const std::string& ch)
		{
			if(rec)
				rec.get().characters(ch);
		}
		
		virtual void endElement(const std::string& /* namespaceURI */, const std::string& /* localName */, const std::string& /* qName */)
		{
			if(rec && rec.get().endElement())
				rec = boost::none;
			
			wc.endElement();
		}
	};
}

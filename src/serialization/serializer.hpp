#pragma once

#include <string>

namespace allerhande
{
	class serializer
	{
	protected:
		serializer() {};
	
	public:
		virtual ~serializer() {};

		virtual void write_array(const std::string& name, const size_t n) = 0;
		virtual void write_object(const std::string& name, const size_t n) = 0;
		
		virtual void write(const std::string& key, const double x) = 0;
		virtual void write(const std::string& key, const uint64_t x) = 0;
		virtual void write(const std::string& key, const std::string& x) = 0;
		
		void write(const std::string& key, const bool x);

		virtual std::string str() = 0;
	};
}

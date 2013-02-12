#include "serializer.hpp"

#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <sstream>

namespace allerhande
{
	void serializer::write(const std::string& key, const bool x)
	{
		write(key, std::string(x ? "yes" : "no"));
	}
}

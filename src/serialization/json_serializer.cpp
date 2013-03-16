#include "json_serializer.hpp"

#include <stdexcept>

namespace allerhande
{
	json_serializer::json_serializer()
	: stack()
	{}

	json_serializer::stack_e::stack_e(Json::Value& node, size_t n)
	: node(node)
	, n(n)
	, i(0)
	{}

	void json_serializer::add_node(const std::string& name, size_t n, const Json::Value&& node)
	{
		while(!stack.empty())
		{
			stack_e& s = stack.top();

			if(s.i < s.n)
				break;

			stack.pop();
		}

		if(stack.empty())
		{
			if(root)
				throw std::logic_error("Setting root twice");
			
			root = node;
			stack.emplace(root.get(), n);
		}
		else
		{
			stack_e& s = stack.top();
			s.i++;

			if(s.node.isArray())
				stack.emplace(s.node.append(node), n);
			else if(s.node.isObject())
				stack.emplace(s.node[name] = node, n);
		}
	}

	void json_serializer::write_array(const std::string& name, const size_t n)
	{
		add_node(name, n, Json::Value(Json::arrayValue));
	}

	void json_serializer::write_object(const std::string& name, const size_t n)
	{
		add_node(name, n, Json::Value(Json::objectValue));
	}
	
	void json_serializer::write(const std::string& key, const double x)
	{
		add_node(key, 0, Json::Value(x));
	}
	
	void json_serializer::write(const std::string& key, const uint64_t x)
	{
		add_node(key, 0, Json::Value((Json::UInt64) x));
	}

	void json_serializer::write(const std::string& key, const std::string& x)
	{
		add_node(key, 0, Json::Value(x));
	}

	std::string json_serializer::str()
	{
		Json::StyledWriter w;

		if(!root)
			return "";
		else
			return w.write(root.get());
	}
}

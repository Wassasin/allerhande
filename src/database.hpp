#pragma once

#include "serialization/json_serializer.hpp"
#include "serialization/serialize_fusion.hpp"

namespace allerhande
{
	class database
	{
	public:
		enum class unit
		{
			quantity,
			gram,
			liter,
			person,
			craving
		};
		
		struct amount
		{
			double x;
			unit u;
			
			amount(double x_)
			: x(x_)
			, u(unit::quantity)
			{}

			amount(double x_, unit unit_)
			: x(x_)
			, u(unit_)
			{}
		};
	
		struct ingredient
		{
			amount a;
			std::string name, properties;
			
			ingredient(amount a_, std::string name_, std::string properties_)
			: a(a_)
			, name(name_)
			, properties(properties_)
			{}
		};
	
		struct recipe
		{
			std::string name;
			amount yield;
			
			std::vector<ingredient> ingredients;
			
			recipe(std::string name_, amount yield_)
			: name(name_)
			, yield(yield_)
			, ingredients()
			{}
			
			void emplace(ingredient i)
			{
				ingredients.emplace_back(i);
			}
		};
		
		static std::string basepath()
		{
			return "database/";
		}
		
		static std::string path(std::string handle)
		{
			std::stringstream s;
			s << basepath() << handle;
			return s.str();
		}
		
		bool exists(std::string handle)
		{
			return boost::filesystem::exists(path(handle));
		}
		
		void save(const std::string handle, const recipe r)
		{
			std::unique_ptr<serializer> s(new json_serializer());
			serialize(s, "recipe", r);
			
			std::ofstream fh;
			fh.open(path(handle));
			fh << s->str();
			fh.close();
		}
	};
}

BOOST_FUSION_ADAPT_STRUCT(
	allerhande::database::amount,
	(double, x)
	(allerhande::database::unit, u)
)

BOOST_FUSION_ADAPT_STRUCT(
	allerhande::database::ingredient,
	(allerhande::database::amount, a)
	(std::string, name)
	(std::string, properties)
)

BOOST_FUSION_ADAPT_STRUCT(
	allerhande::database::recipe,
	(std::string, name)
	(allerhande::database::amount, yield)
	(std::vector<allerhande::database::ingredient>, ingredients)
)

namespace std
{
	inline std::string to_string(const allerhande::database::unit u)
	{
		typedef allerhande::database::unit unit;
		
		switch(u)
		{
		case unit::quantity:
			return "quantity";
		case unit::gram:
			return "gram";
		case unit::liter:
			return "liter";
		case unit::person:
			return "person";
		case unit::craving:
			return "craving";
		}
	}
}

namespace allerhande
{
	inline std::ostream& operator<<(std::ostream& os, const database::unit rhs)
	{
		return os << std::to_string(rhs);
	}
	
	inline std::ostream& operator<<(std::ostream& os, const database::amount rhs)
	{
		return os << rhs.x << ' ' << rhs.u;
	}
	
	inline std::ostream& operator<<(std::ostream& os, const database::ingredient rhs)
	{
		os << '[' << rhs.a << "] " << rhs.name;
		
		if(!rhs.properties.empty())
			os << " (" << rhs.properties << ')';
		
		return os;
	}
	
	inline std::ostream& operator<<(std::ostream& os, const database::recipe rhs)
	{
		os << rhs.name << " (" << rhs.yield << ")";
		
		for(auto const i : rhs.ingredients)
			os << '\t' << i << std::endl;
		
		return os;
	}

	template<>
	struct serialize_value<database::unit>
	{
		static inline void exec(const std::unique_ptr<serializer>& s, const std::string& name, const database::unit x)
		{
			s->write(name, std::to_string(x));
		}
	};
}

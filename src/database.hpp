#pragma once

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
	};
}

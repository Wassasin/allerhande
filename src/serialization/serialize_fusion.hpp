#pragma once

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>

#include "serializer.hpp"

namespace allerhande
{
	template<typename T, typename N>
	struct serialize_itr;

	template<typename T>
	void inline serialize(const std::unique_ptr<serializer>& s, const std::string name, const T& x)
	{
		s->write_object(name, boost::fusion::result_of::size<T>::value);
		serialize_itr<T, boost::mpl::int_<0>>::exec(s, x);
	}

	template<typename T>
	struct serialize_value
	{
		static inline void exec(const std::unique_ptr<serializer>& s, const std::string& name, const T& x)
		{
			s->write(name, x);
		}
	};
	
	template<typename T>
	struct serialize_value<std::vector<T>>
	{
		static inline void exec(const std::unique_ptr<serializer>& s, const std::string& name, const std::vector<T>& xs)
		{
			const std::string element_name = name.substr(0, name.size()-1);
			s->write_array(name, xs.size());
			for(const T& x : xs)
				serialize(s, element_name, x);
		}
	};

	template<typename T>
	struct serialize_itr<T, typename boost::fusion::result_of::size<T>::type>
	{
		static inline void exec(const std::unique_ptr<serializer>&, const T&) {}
	};

	template<typename T, typename N>
	struct serialize_itr
	{
		typedef typename boost::fusion::result_of::value_at<T, N>::type current_t;
		typedef typename boost::mpl::next<N>::type next_t;
		typedef boost::fusion::extension::struct_member_name<T, N::value> name_t;
	
		static inline void exec(const std::unique_ptr<serializer>& s, const T& x)
		{
			serialize_value<current_t>::exec(s, name_t::call(), boost::fusion::at<N>(x));
			serialize_itr<T, next_t>::exec(s, x);
		}
	};
}

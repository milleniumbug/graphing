#pragma once
#include <boost/optional.hpp>

template<typename Map, typename Key>
boost::optional<typename Map::mapped_type&> at(Map& map, const Key& key)
{
	auto it = map.find(key);
	if(it != map.end())
		return it->second;
	else
		return boost::none;
}

template<typename Map, typename Key>
boost::optional<const typename Map::mapped_type&> at(const Map& map, const Key& key)
{
	auto it = map.find(key);
	if(it != map.end())
		return it->second;
	else
		return boost::none;
}
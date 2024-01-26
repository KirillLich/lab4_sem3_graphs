#pragma once
#include <utility>

template <typename Key>
struct std::hash<std::pair<Key, Key>>
{
	template<typename T1, typename T2>
	std::size_t operator()(std::pair<T1, T2>& pair)
	{
		std::size_t first = std::hash<T1>()(pair.first);
		std::size_t second = std::hash<T2>()(pair.second);
		return first ^ second;
	}
};
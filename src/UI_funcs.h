#pragma once

template<typename T>
inline T TakeItem(std::string errorMessage)
{
	T out = 0;
	std::cin >> out;
	if (!std::cin.good() || (std::cin.peek() != '\n'))
	{
		std::cin.clear();

		std::cout << errorMessage << '\n';
		while (std::cin.get() != '\n') {}
		out = TakeItem<T>(errorMessage);
	}
	return out;
}
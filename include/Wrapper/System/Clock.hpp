#pragma once
#include <Wrapper/Export/Export.hpp>
#include <chrono>

template class GDIWRAPPER_API std::chrono::duration<__int64, std::nano>;
template class GDIWRAPPER_API std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>;

class GDIWRAPPER_API Clock
{
public:
	Clock();
	~Clock();

	double restart();
	double getElapsedTime();

private:
	std::chrono::steady_clock::time_point m_last;
	std::chrono::steady_clock::time_point m_old;
};
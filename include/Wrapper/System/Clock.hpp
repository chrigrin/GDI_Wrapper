#pragma once
#include <Wrapper/Export/Export.hpp>
#include <chrono>

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
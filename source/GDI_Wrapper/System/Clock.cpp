#include <GDI_Wrapper/System/Clock.hpp>

Clock::Clock()
{
	m_last = std::chrono::steady_clock::now();
	m_old = m_last;
}

Clock::~Clock()
{
}

std::chrono::duration<__int64, std::nano> Clock::restart()
{
	m_old = m_last;
	m_last = std::chrono::steady_clock::now();
	std::chrono::duration<__int64, std::nano> duration = m_last - m_old;
	return duration;
}

std::chrono::duration<__int64, std::nano> Clock::getElapsedTime()
{
	m_last = std::chrono::steady_clock::now();
	std::chrono::duration<__int64, std::nano> duration = m_last - m_old;
	return duration;
}

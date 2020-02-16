#include "stdafx.h"
#include "Clock.hpp"

Clock::Clock()
{
	m_last = std::chrono::steady_clock::now();
	m_old = m_last;
}

Clock::~Clock()
{
}

double Clock::restart()
{
	m_old = m_last;
	m_last = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = m_last - m_old;
	return duration.count();
}

double Clock::getElapsedTime()
{
	m_last = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = m_last - m_old;
	return duration.count();
}

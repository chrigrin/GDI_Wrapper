#include <GDI_Wrapper/System/Time.hpp>

namespace gw
{
	Time::Time()
		:
		m_nanoseconds(0)
	{
	}

	Time::Time(int milli)
		:
		m_nanoseconds(milli * 1'000'000)
	{
	}

	Time::~Time()
	{
	}

	const Time &Time::operator=(const std::chrono::duration<__int64, std::nano> &time)
	{
		m_nanoseconds = time.count();
		return *this;
	}

	bool Time::operator<(const Time &other) const
	{
		return m_nanoseconds < other.m_nanoseconds;
	}

	bool Time::operator>(const Time &other) const
	{
		return m_nanoseconds > other.m_nanoseconds;
	}

	__int64 Time::operator+(const Time &other) const
	{
		return m_nanoseconds + other.m_nanoseconds;
	}

	__int64 Time::operator-(const Time &other) const
	{
		return m_nanoseconds - other.m_nanoseconds;
	}

	__int64 &Time::operator+=(const Time& other)
	{
		return m_nanoseconds += other.m_nanoseconds;
	}

	__int64 &Time::operator-=(const Time& other)
	{
		return m_nanoseconds -= other.m_nanoseconds;
	}

	double Time::asSeconds()
	{
		return static_cast<double>(m_nanoseconds / 1'000'000'000);
	}

	__int64 Time::asMilliseconds()
	{
		return static_cast<__int64>(m_nanoseconds / 1'000'000);
	}

	__int64 Time::asMicroseconds()
	{
		return static_cast<__int64>(m_nanoseconds / 1'000);
	}

	__int64 Time::asNanoseconds()
	{
		return m_nanoseconds;
	}
}
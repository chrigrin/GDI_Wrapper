#pragma once
#include <GDI_Wrapper/Export/Export.hpp>
#include <chrono>

namespace gw
{
	class GDIWRAPPER_API Time
	{
	public:
		Time();
		Time(int milli);
		~Time();

		const Time &operator=(const std::chrono::duration<__int64, std::nano> &time);
		bool operator<(const Time &other) const;
		bool operator>(const Time &other) const;
		__int64 operator+(const Time &other) const;
		__int64 operator-(const Time &other) const;
		__int64 &operator+=(const Time &other);
		__int64 &operator-=(const Time &other);

		double asSeconds();
		__int64 asMilliseconds();
		__int64 asMicroseconds();
		__int64 asNanoseconds();

	private:
		__int64 m_nanoseconds;
	};
}
#pragma once
#include <GDI_Wrapper/Export/Export.hpp>
#include <chrono>

namespace gw
{
	class GDIWRAPPER_API Time
	{
	public:
		Time();
		~Time();

		const Time &operator=(const std::chrono::duration<__int64, std::nano> &time);

		double asSeconds();
		double asMilliseconds();
		__int64 asMicroseconds();
		__int64 asNanoseconds();

	private:
		__int64 m_nanoseconds;
	};
}
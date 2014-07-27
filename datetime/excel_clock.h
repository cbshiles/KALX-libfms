// excel_clock - high frequency clock
#pragma once
#include <ctime>
#include <chrono>
#include <Windows.h>
#include <WinBase.h>

#if defined(_WIN32) && _MSC_VER <= 1700
#define constexpr const
#endif

namespace datetime {

	struct high_perfomance_clock {
	    typedef long long                            rep;
	    typedef std::nano                            period;
	    typedef std::chrono::duration<rep,period>    duration;
	    typedef std::chrono::time_point<high_perfomance_clock>
			time_point;
	    static const bool is_steady =                true;

		static time_point now()
		{
			LARGE_INTEGER count;
			QueryPerformanceCounter(&count);

			return time_point(duration(count.QuadPart
				* static_cast<rep>(period::den) / frequency()));
		}
	private:
		static long long frequency()
		{
			static LARGE_INTEGER frequency = {0};

			if (!frequency.u.LowPart)
				QueryPerformanceFrequency(&frequency);

	        return frequency.QuadPart;
		}
	};

} // namespace datetime

#if _MSC_VER <= 1700
#undef constexpr
#endif

#ifdef _DEBUG

using namespace std::chrono;
using datetime::high_perfomance_clock;

static_assert(high_perfomance_clock::is_steady, "datetime::high_performance_clock is not steady");

void check_high_performance_clock(void)
{
	auto t0 = high_perfomance_clock::now();
	Sleep(1000);
	auto t1 = high_perfomance_clock::now();

	ensure (std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() >= 1000);

	duration<double,std::ratio<86400>> d;
	d = minutes(5);
	auto c = d.count();
	++c;

}

#endif // _DEBUG

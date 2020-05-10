#ifndef TIMER_HPP
#define TIMER_HPP
#include <chrono>
#include <iostream>

#ifdef BENCHMARK
#define BENCHMARK_THIS cbf::timer timer
#else
#define BENCHMARK_THIS
#endif


namespace cbf
{
	class timer
	{
	public:
		timer()
		{
			start_timepoint = std::chrono::high_resolution_clock::now();
		}

		~timer()
		{
			const auto end_timepoint = std::chrono::high_resolution_clock::now();

			const auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint)
			                   .time_since_epoch().count();
			const auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint)
			                 .time_since_epoch().count();

			const auto duration = end - start;
			double ms = duration * 0.001;

			std::cout << duration << "us (" << ms << "ms)\n";
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;
	};
}
#endif // TIMER_HPP

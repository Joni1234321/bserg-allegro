#pragma once
#include <chrono>

#define TIMER(T) Timer ______timer(T);

class Timer {
public:
	Timer(const char* text = "____");
	~Timer();

	const char* text;
	const std::chrono::time_point<std::chrono::steady_clock> time;
};
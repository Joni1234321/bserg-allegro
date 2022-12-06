#include "timer.h"

#include <iostream>

Timer::Timer(const char* text) : text(text), time(std::chrono::high_resolution_clock::now()) {
}

Timer::~Timer() {
	std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - time;
	float ms = duration.count() * 1000.0f;
	std::cout << "Timer \"" << text << "\" took " << ms << " ms." << std::endl;
}
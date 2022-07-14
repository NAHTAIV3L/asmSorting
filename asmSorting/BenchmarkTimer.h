#include <stdio.h>
#include <chrono>

#pragma once
class BenchmarkTimer
{
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_End;
	std::chrono::duration<float> duration = (std::chrono::duration<float, std::ratio<1i64, 1i64>>)NULL;
public:
	BenchmarkTimer() {}

	void Start()
	{ m_Start = std::chrono::high_resolution_clock::now(); }

	void End()
	{ m_End = std::chrono::high_resolution_clock::now(); }

	float GetTime()
	{
		duration = m_End - m_Start;
		float ms = duration.count() * 1000;
		return ms;
	}

	void Print()
	{
		duration = m_End - m_Start;
		float ms = duration.count() * 1000;
		printf("%f\n", ms);
	}

	~BenchmarkTimer() {}

};


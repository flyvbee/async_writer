#pragma once
#include "AsyncWriter.h"
#include <chrono>         // std::chrono::seconds
 

#define STEP_OUTPUT_SIZE 50

class Compute
{
public:
	Compute(AsyncWriter* theWriter);
	// ~Compute();

	int new_step();
	int set_total_steps(int step);
	int output_step();
private:
	AsyncWriter* _theWriter;
	std::mutex* _mtx;
	int _current_step;
	int _total_step;
};
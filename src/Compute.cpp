#include "Compute.h"



Compute
::Compute(AsyncWriter* theWriter)
: _theWriter(theWriter), _current_step(0)
{
    _mtx = _theWriter->get_mutex();
	_theWriter->set_step_output_size(STEP_OUTPUT_SIZE);
}

int Compute
::new_step(){
	std::this_thread::sleep_for (std::chrono::microseconds(1));
	_current_step++;

	this->output_step();
	return 1;
}

int Compute
::set_total_steps(int step){
	_theWriter->set_total_steps(step);
	_total_step = step;
	return 1;
}

int Compute
::output_step(){
	std::vector<int> id(STEP_OUTPUT_SIZE, _current_step);
	std::vector<float> results(STEP_OUTPUT_SIZE, (float) (_current_step+0.5));

	_theWriter->output_ID(id);
	_theWriter->output_results(results);

	static bool first_step = true;
	if(first_step){
		std::unique_lock<std::mutex> lk(*_mtx);
		_theWriter->notify();
		first_step = false;
	}

	return 1;
}
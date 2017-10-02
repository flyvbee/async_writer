#pragma once
#include <fstream>           // std::cout
#include <iostream>           // std::cout
#include <vector>             // std::vector
#include <string>             // std::string
#include <atomic>             // std::atomic

#include <tbb/tbb.h>
#include <thread>             // std::thread
#include <condition_variable> // std::condition_variable
#include <mutex>              // std::mutex, std::unique_lock

#define CONCURRENT_BOUNDED_QUEUE_CAPACITY 100

class AsyncWriter
{
public:
	AsyncWriter(std::mutex* mtx, std::string const& filename);
	~AsyncWriter();

	int output_ID(std::vector<int> const& id);
	int output_results(std::vector<float> const& results);

	int write_ID_to_disk(int step);
	int write_results_to_disk(int step);


	int start_writing();
	int notify();
	void async_writer_thread();
	int switch_async_output(bool b);
	int set_step_output_size(int step);
	int set_total_steps(int step);

	std::mutex* get_mutex();

private:
	bool _async_output_is_enabled;
	std::mutex* _mtx;
	std::string _filename;
	std::condition_variable* _cv;
	std::ofstream ofsID;
	std::ofstream ofsResult;
	int _step_output_size;
	

	tbb::concurrent_bounded_queue<int>   _output_ID_buffer;
	tbb::concurrent_bounded_queue<float> _output_results_buffer;
	std::thread                          _async_writer;
    int _current_output_step;
	int _total_output_step;
};
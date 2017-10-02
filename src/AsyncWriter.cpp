#include "AsyncWriter.h"



AsyncWriter
::AsyncWriter(std::mutex* mtx, std::string const& filename)
:_async_output_is_enabled(false), _mtx(mtx), _filename(filename)
,_current_output_step(0)
{
	_output_ID_buffer.set_capacity(sizeof(int)*CONCURRENT_BOUNDED_QUEUE_CAPACITY);
	_output_results_buffer.set_capacity(sizeof(float)*CONCURRENT_BOUNDED_QUEUE_CAPACITY);
	ofsID.open(_filename+"_ID.txt" , std::ofstream::out | std::ofstream::app);
	ofsResult.open(_filename+"_result.txt" , std::ofstream::out | std::ofstream::app);
	_cv = new std::condition_variable() ;
}

AsyncWriter
::~AsyncWriter(){

	ofsID.flush();
	ofsResult.flush();

	if (_async_output_is_enabled && _async_writer.joinable()){
		_async_writer.join();
	}
	std::cout<<"\n";
	std::cout<<"*********************\n";	
	std::cout<<"****Output  Done!****\n";	
	std::cout<<"*********************\n";	
}


int AsyncWriter
::notify(){
	_cv->notify_one();
	return 1;
}

int AsyncWriter
::start_writing(){
	if(_async_output_is_enabled){
	    if(_async_writer.joinable()){
	        _async_writer.join();
	    }
	    _async_writer = std::thread ([=]{
	    	std::unique_lock<std::mutex> lk(*_mtx);
	    	_cv->wait(lk);
	    	async_writer_thread();
	    });
	}
	return 1;
}

void AsyncWriter
::async_writer_thread(){
	while(_current_output_step < _total_output_step){
		this->write_ID_to_disk(_current_output_step);
		this->write_results_to_disk(_current_output_step);
		_current_output_step++;
	}
}

int AsyncWriter
::switch_async_output(bool b){
	_async_output_is_enabled = b;
	return 1;
}

std::mutex* AsyncWriter
::get_mutex(){
	return this->_mtx;
}


int AsyncWriter
::set_step_output_size(int stepsize){
	_step_output_size = stepsize ;
	return 1;
}
int AsyncWriter
::set_total_steps(int step){
	_total_output_step = step;
	return 1;
}

int AsyncWriter
::output_ID(std::vector<int> const& id){
	for (int i = 0; i < _step_output_size; ++i){
		_output_ID_buffer.push(id[i]);
	}
	return 1;
}

int AsyncWriter
::output_results(std::vector<float> const& results){
	for (int i = 0; i < _step_output_size; ++i){
		_output_results_buffer.push(results[i]);
	}
	return 1;
}



int AsyncWriter
::write_ID_to_disk(int step){
	for (int i = 0; i < _step_output_size; ++i){
		int item = -1;
		_output_ID_buffer.pop(item);
		std::cout<< item << " " ;
		ofsID<< item << " " ;
	}
	std::cout<<std::endl;
	ofsID<<std::endl;
	return 1;
}


int AsyncWriter
::write_results_to_disk(int step){
	for (int i = 0; i < _step_output_size; ++i){
		float item = -1;
		_output_results_buffer.pop(item);
		std::cout<< item << " " ;
		ofsResult<< item << " " ;
	}
	std::cout<<std::endl;
	ofsResult<<std::endl;
	return 1;
}


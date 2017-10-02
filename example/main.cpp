#include <AsyncWriter.h>
#include <Compute.h>




int main(int argc, char const *argv[])
{
	std::mutex mtx;
	std::string filename = "test_async";
	int total_steps = 10;
	bool async_output_is_enabled = true;


	std::cout<<"start theWriter " <<std::endl;
	AsyncWriter theWriter(&mtx, filename) ;
	theWriter.switch_async_output(async_output_is_enabled);

	std::cout<<"start theComputeA" <<std::endl;
	Compute theComputeA(&theWriter) ;
	theComputeA.set_total_steps(total_steps);

	std::cout<<"start theWriter.start_writing " <<std::endl;
	theWriter.start_writing();

	std::cout<<"start theComputeA new step" <<std::endl;	
	for (int i = 0; i < total_steps; ++i){
		theComputeA.new_step();
	}


	std::cout<<"\n";
	std::cout<<"*********************\n";	
	std::cout<<"**Computation Done!**\n";	
	std::cout<<"*********************\n";	
	return 0;
}
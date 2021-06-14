#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<sys/types.h>

int main (int argc, char *argv[]) {
	size_t array_sz = 1 * 1000 * 1000;	// 1 MB default size of array
	int iter_time = -1;			// Iterate infinitely

	switch (argc) {
		case 3:
			// expect time in third argumnet
			iter_time = atoi(argv[2]);
		case 2:
			// expect size in second argument
			array_sz = atol(argv[1]);
	}

	std::cout << "PID : " << getpid() << std::endl;
	std::cout << "Sz = " << array_sz << ", time = " << iter_time << std::endl;
	char* block = new char[array_sz];
	if (!block) {
		std::cout << "Failed to allocate memory!\n";
		return 1;
	}

	size_t i = 0;
	time_t start_time = time(0);
	time_t cur_time = start_time;
	time_t end_time = cur_time + iter_time;
	
	char progress[4] = { '|', '/', '-', '\\' };
	int pi = 0;
	time_t last_update_time = 0;
	//std::cerr << ".";
	while (iter_time == -1 ||
	 	cur_time < end_time) {
		// access array
		++block[i];
		i = (i + 1) % array_sz;
		// get new current time
		cur_time = time(0);
		// if we are 10 seconds since last update, move the progress bar
		if (last_update_time == 0 ||
			(cur_time == last_update_time + 1)) {
			//std::cerr << '\b' << progress[pi];
			std::cerr << i << std::endl;
			pi = (pi + 1) % 4;
			last_update_time = cur_time;
		}
	}
	std::cerr << std::endl;
	delete[] block;
	return 0;
}

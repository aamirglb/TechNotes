#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main()
{
	std::vector<int32_t *> ptr;
	uint64_t   total_allocation{};
	uint32_t   block_size {10*1024*1024};  // 10 MB
	uint32_t   block{};
	
	while(true)
	{
		auto *p = new int[block_size];
		ptr.push_back(p);
		total_allocation += block_size;
		++block;
		std::cout << "Block-" << block << " : " << (block * 10) << " MB allocated." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
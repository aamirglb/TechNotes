#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

int main()
{
	std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int>::const_iterator pos;
	pos = std::find(v.cbegin(), v.cend(), 5);
	std::cout << "pos: " << *pos <<  std::endl;

	std::vector<int>::const_reverse_iterator rpos(pos);
	std::cout << "rpos: " << *rpos << std::endl;

	std::deque<int> q {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::deque<int>::const_iterator pos1;
	pos1 = std::find(q.cbegin(), q.cend(), 2);

	std::deque<int>::const_iterator pos2;
	pos2 = std::find(q.cbegin(), q.cend(), 7);

	auto print = [](int e) { std::cout << e << ' '; };
	std::for_each(pos1, pos2, print);
	std::cout << std::endl;

	std::deque<int>::const_reverse_iterator rpos1{pos1};
	std::deque<int>::const_reverse_iterator rpos2{pos2};

	std::for_each(rpos2, rpos1, print);
	std::cout << std::endl;
}

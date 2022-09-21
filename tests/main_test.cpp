#include "test.hpp"

int main(void)
{
	std::cout << "USED NAMESPACE => " << NAMESPACE_STR << std::endl; 
	vector_test();
	stack_test();
	map_test();
	pair_test();
	set_test();
	
	return 0;
}
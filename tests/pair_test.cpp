#include "test.hpp"

void pair_test(void)
{
	display_fat_header("PAIR TESTS");

	display_header("CONSTRUCTOR");
	NAMESPACE::pair<std::string, int> p1("jacky", 34);
	NAMESPACE::pair<std::string, int> p2(p1);
	NAMESPACE::pair<std::string, int> p3 = p1;

	std::cout << p1.first << " || "<< p1.second  << std::endl;
	std::cout << p2.first << " || "<< p2.second  << std::endl;
	std::cout << p3.first << " || "<< p3.second  << std::endl;

	display_header("PUBLIC MEMBERS");
	p1.first = "manu";
	p2.second = 46;
	std::cout << p1.first << " || "<< p1.second  << std::endl;

	display_header("MAKE PAIR");
	NAMESPACE::pair<std::string, int> p;
	p = NAMESPACE::make_pair<std::string, int>("sylvain", 67);
	std::cout << p.first << " || "<< p.second  << std::endl;
}
#include "test.hpp"
#include <set>
#include <utility>

template <typename T>
void display_set(typename NAMESPACE::set<T> set, std::string name = "set")
{
	std::cout << name << " => { ";
	typename NAMESPACE::set<T>::iterator it = set.begin();
	for(; it != set.end(); it++)
	{
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << "}" << std::endl;
}

void	set_test(void)
{
	display_fat_header("SET TESTS");
	NAMESPACE::set<int> set;

	set.insert(3);
	set.insert(34);
	set.insert(235);
	set.insert(7);
	set.insert(98);
	set.insert(2398);

	display_set<int>(set, "set");

	display_header("CONSTRUCTOR");
	NAMESPACE::set<int> set_copy(set);
	NAMESPACE::set<int> set_assign = set;
	display_set<int>(set_copy, "set_copy");
	display_set<int>(set_assign, "set_assign");
	
	
	display_header("ERASE");
	std::cout << "erasing 98" << std::endl;
	set.erase(98);
	display_set<int>(set, "set");
	std::cout << "erasing 9" << std::endl;

	set.erase(9);
	display_set<int>(set, "set");

	display_header("BOUND");
	std::cout <<  "set.upper_bound(7) = >" << *(set.upper_bound(7))  << std::endl;
	std::cout <<  "set.lower_bound(7) = >" << *(set.lower_bound(7))  << std::endl;

	display_header("EQUAL RANGE");
	std::cout << *(set.equal_range(34).first) << " | "<< *(set.equal_range(34).second) << std::endl;

	NAMESPACE::set<int> set2;

	set2.insert(54);
	set2.insert(42);
	set2.insert(65);
	set2.insert(70);
	set2.insert(98);
	set2.insert(23);
	display_set<int>(set2, "set2");

	display_header("SWAP");
	{
		int myints[]={12,75,10,32,20,25};
		NAMESPACE::set<int> first (myints,myints+3);     // 10,12,75
		NAMESPACE::set<int> second (myints+3,myints+6);  // 20,25,32

		std::cout << "before swapping "<< std::endl;
		display_set<int>(first, "first");
		display_set<int>(second, "second");
		NAMESPACE::swap(first, second);
		std::cout << "after swapping "<< std::endl;
		display_set<int>(first, "first");
		display_set<int>(second, "second");
	}

	display_header("REVERSE_ITERATOR");
	{
		NAMESPACE::set<std::string> names;

		names.insert("polo");
		names.insert("rachid");
		names.insert("jacky");
		names.insert("zoe");
		names.insert("abdoul");
		names.insert("manu");
		display_set<std::string>(names, "names");

		std::cout <<"names set by reverse iterators =>" << std::endl;
		NAMESPACE::set<std::string>::reverse_iterator reverse_it = names.rbegin();
		for (; reverse_it != names.rend(); reverse_it++)
			std::cout << "["<< *reverse_it<< "]"<< std::endl;
	}







}
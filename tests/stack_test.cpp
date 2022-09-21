#include "test.hpp"
#include <list>


void stack_test(void)
{
	display_fat_header("STACK TESTS");

	display_header("CONSTRUCTOR");
	std::list<int> lst(3, 329);   // list with 3 elements
	NAMESPACE::vector<int> vec(2, 456); // vector with 2 elements

	NAMESPACE::stack<int, std::list<int> > stack_1;			 // empty stack
	NAMESPACE::stack<int, std::list<int> > stack_2(lst); // stack initialized to copy of list

	NAMESPACE::stack<int, NAMESPACE::vector<int> > stack_3; // empty stack using vector
	NAMESPACE::stack<int, NAMESPACE::vector<int> > stack_4(vec);

	display_header("SIZE");
	std::cout << "stack_1.size() => " << stack_1.size() << '\n';
	std::cout << "stack_2.size() => " << stack_2.size() << '\n';
	std::cout << "stack_3.size() => " << stack_3.size() << '\n';
	std::cout << "stack_4.size() => " << stack_4.size() << '\n';

	display_header("EMPTY");

	std::cout << "stack_1.empty() => " << stack_1.empty() << '\n';
	std::cout << "stack_2.empty() => " << stack_2.empty() << '\n';

	display_header("PUSH");
	
	NAMESPACE::stack<int> int_stack;
	std::cout << "size after initialisation => " << int_stack.size() << '\n';
	for (int i = 0; i < 5; i++)
		int_stack.push(i);
	std::cout << "size after 5 push => " << int_stack.size() << '\n';

	display_header("POP");
	int_stack.pop();
	std::cout << "size after 1 pop => " << int_stack.size() << '\n';

	display_header("TOP");
	
	NAMESPACE::stack<int> new_stack;
	new_stack.push(30);
	new_stack.push(10);
	new_stack.push(20);
	new_stack.push(40);
	
	std::cout << "new_stack.top() => " << new_stack.top() << '\n';

	display_header("COMPARATORS");
	std::cout << "stack_3 == stack_4 =>" << (stack_3 == stack_4) << std::endl;
	std::cout << "stack_3 != stack_4 =>" << (stack_3 != stack_4) << std::endl;
	std::cout << "stack_3 >= stack_4 =>" << (stack_3 >= stack_4) << std::endl;
	std::cout << "stack_3 <= stack_4 =>" << (stack_3 <= stack_4) << std::endl;
	std::cout << "stack_3 > stack_4 =>" << (stack_3 > stack_4) << std::endl;
	std::cout << "stack_3 < stack_4 =>" << (stack_3 < stack_4) << std::endl;

	display_header("IMPOSSIBLE ITERATORS");
	// NAMESPACE::stack<int>::iterator it = int_stack.begin();
	// for(; it != int_stack.end(); it++)
	// 	;
	
}
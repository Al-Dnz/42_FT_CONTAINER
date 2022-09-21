#pragma once

#include <iostream>
#include <string>
#include <utility>

#ifdef STD

	# define NAMESPACE std
	# define NAMESPACE_STR "std"

	#include <map>
	#include <vector>
	#include <stack>
	#include <set>
	#include <iterator>

#else
	# define NAMESPACE ft
	# define NAMESPACE_STR "ft"

	#include "../srcs/utility.hpp"

	#include "../srcs/Pair.hpp"
	#include "../srcs/Vector.hpp"
	#include "../srcs/Map.hpp"
	#include "../srcs/Set.hpp"
	
	#include "../srcs/Stack.hpp"
	#include "../srcs/Iterator.hpp"
	#include "../srcs/RevIterator.hpp"

	#include "../srcs/RBT.hpp"
	#include "../srcs/RBT_iterator.hpp"

#endif

#include "test_util.cpp"
#include "RBT_test.cpp"
#include "vector_test.cpp"
#include "stack_test.cpp"
#include "map_test.cpp"
#include "set_test.cpp"
#include "pair_test.cpp"

void	RBT_test(void);
void	vector_test(void);
void	stack_test(void);
void	map_test(void);
void	set_test(void);
void	pair_test(void);

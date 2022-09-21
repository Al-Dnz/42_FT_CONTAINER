#include "test.hpp"

#include "../srcs/Vector.hpp"

template <typename T>
void	display_vector(T vec, std::string name = "vec")
{
		std::cout << name <<" => [";
		for (typename T::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it;
			if (it != vec.end() - 1)
				std::cout << ", ";
		}
		std::cout << "]" << std::endl;
}

class Awesome {

	public:

		Awesome( void ) : _n( 42 ) { std::cout << "Default constructor" << std::endl; } //should not happen too often or else there is a wrong use of allocator (which calls the copy constructor)
		Awesome( int n ) : _n( n ) { std::cout << "Int constructor" << std::endl; (void)n; }
		Awesome( Awesome const &rhs ) : _n( 42 ) { *this = rhs;}
		virtual ~Awesome(void) {}

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
		int get( void ) const { return this->_n; }

	private:

		int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template <class T>
void	print_vector(NAMESPACE::vector<T> &test)
{
	typename NAMESPACE::vector<T>::iterator		beg = test.begin();
	typename NAMESPACE::vector<T>::iterator		end = test.end();
	std::cout << "size : " << test.size() << ", capacity : " << test.capacity() << std::endl;
	for (typename NAMESPACE::vector<T>::iterator it = beg; it != end; it++)
	{
		std::cout << *it << " ";
		if (((it - beg) % 10 == 9) && it > beg)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

void vector_test(void)
{
	display_fat_header("VECTOR TEST");
	
	display_header("CONSTRUCTOR");
	{
		NAMESPACE::vector<int> vec_1;									// empty vector of ints
		NAMESPACE::vector<int> vec_2(4, 100);							// four ints with value 100
		NAMESPACE::vector<int> vec_3(vec_2.begin(), vec_2.end());	// iterating through second
		NAMESPACE::vector<int> vec_4(vec_3);							// a copy of third

		int int_array[] = {16, 2, 77, 29};
		NAMESPACE::vector<int> vec_5(int_array, int_array + sizeof(int_array) / sizeof(int));

		display_vector<NAMESPACE::vector<int> >(vec_5, "vec_5");
	}


	display_header("TEMPLATED CLASS");
	{
		std::string colour[4]  = { "Blue", "Red", "Orange", "Yellow" };
		NAMESPACE::vector<std::string> str_vec(colour, colour + 4);
		display_vector<NAMESPACE::vector<std::string> >(str_vec, "str_vec");

		Perso perso_arr[4] = {Perso("jack"), Perso("polo"), Perso("manu"), Perso("tibo")};
		NAMESPACE::vector<Perso> perso_vec(perso_arr, perso_arr + 4);
		display_vector<NAMESPACE::vector<Perso> >(perso_vec, "perso_vec");

		char char_arr[5] = {'!', '8', 'X', 'j', 'B'};
		NAMESPACE::vector<char> char_vec(char_arr, char_arr + 5);
		display_vector<NAMESPACE::vector<char> >(char_vec, "char_vec");

	}

	display_header("ASSIGNATION OPERATOR");
	{
		NAMESPACE::vector<int> foo(3, 0);
		NAMESPACE::vector<int> bar(5, 0);

		bar = foo;
		foo = NAMESPACE::vector<int>();

		std::cout << "Size of foo: " << int(foo.size()) << '\n';
		std::cout << "Size of bar: " << int(bar.size()) << '\n';
	}

	display_header("BEGIN ITERATOR");
	{
		NAMESPACE::vector<int> vec;
		for (int i = 1; i <= 5; i++)
			vec.push_back(i);

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("END ITERATOR");
	{
		NAMESPACE::vector<int> vec;
		for (int i = 1; i <= 5; i++)
			vec.push_back(i);

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("RBEGIN REVERSE ITERATOR");
	{
		NAMESPACE::vector<int> vec(5); // 5 default-constructed ints

		int i = 0;

		NAMESPACE::vector<int>::reverse_iterator rit = vec.rbegin();
		for (; rit != vec.rend(); ++rit)
			*rit = ++i;

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("REND REVERSE ITERATOR");
	{
		NAMESPACE::vector<int> vec(5); // 5 default-constructed ints
		NAMESPACE::vector<int>::reverse_iterator rit = vec.rbegin();

		int i = 0;
		for (rit = vec.rbegin(); rit != vec.rend(); ++rit)
			*rit = ++i;

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("=> COMPARATOR BETWEEN CONST AND SIMPLE ITERATOR");
	{
		NAMESPACE::vector<int> vec;
		for (int i = 1; i <= 5; i++)
			vec.push_back(i);

		NAMESPACE::vector<int>::iterator it = vec.begin() +2;
		NAMESPACE::vector<int>::const_iterator const_it = vec.begin() + 2;

		std::cout << "(it == const_it) => " << (it == const_it) << std::endl;
		std::cout << "(it != const_it) => " << (it != const_it) << std::endl;
		std::cout << "(it > const_it) => " << (it > const_it) << std::endl;
		std::cout << "(it < const_it) => " << (it < const_it) << std::endl;
		std::cout << "(it >= const_it) => " << (it >= const_it) << std::endl;
		std::cout << "(it <= const_it) => " << (it <= const_it) << std::endl;
	}

	display_header("SIZE");
	{
		NAMESPACE::vector<int> int_array;
		std::cout << "0. size: " << int_array.size() << '\n';

		for (int i = 0; i < 10; i++)
			int_array.push_back(i);
		std::cout << "1. size: " << int_array.size() << '\n';

		int_array.insert(int_array.end(), 10, 100);
		std::cout << "2. size: " << int_array.size() << '\n';

		int_array.pop_back();
		std::cout << "3. size: " << int_array.size() << '\n';
	}

	display_header("MAX_SIZE");
	{
		NAMESPACE::vector<int> vec;
		for (int i = 0; i < 100; i++)
			vec.push_back(i);

		std::cout << "size: " << vec.size() << "\n";
		std::cout << "capacity: " << vec.capacity() << "\n";
		std::cout << "max_size: " << vec.max_size() << "\n";
	}

	display_header("RESIZE");
	{
		NAMESPACE::vector<int> vec;

		for (int i = 1; i < 10; i++)
			vec.push_back(i);

		vec.resize(5);
		vec.resize(8, 100);
		vec.resize(12);

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("CAPACITY");
	{
		NAMESPACE::vector<int> vec;

		for (int i = 0; i < 100; i++)
			vec.push_back(i);

		std::cout << "size: " << (int)vec.size() << '\n';
		std::cout << "capacity: " << (int)vec.capacity() << '\n';
		std::cout << "max_size: " << (int)vec.max_size() << '\n';
	}

	display_header("EMPTY");
	{
		NAMESPACE::vector<int> vec;
		int sum(0);

		for (int i = 1; i <= 10; i++)
			vec.push_back(i);

		while (!vec.empty())
		{
			sum += vec.back();
			vec.pop_back();
		}

		std::cout << "total: " << sum << '\n';
	}

	display_header("RESERVE");
	{
		NAMESPACE::vector<int>::size_type sz;

		NAMESPACE::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			foo.push_back(i);
			if (sz != foo.capacity())
			{
				sz = foo.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}

		NAMESPACE::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100); // this is the only difference with foo above
		std::cout << "making bar grow:\n";
		for (int i = 0; i < 100; ++i)
		{
			bar.push_back(i);
			if (sz != bar.capacity())
			{
				sz = bar.capacity();
				std::cout << "capacity changed: " << sz << '\n';
			}
		}
	}

	display_header("OPERATOR[]");
	{
		NAMESPACE::vector<int> vec(10); // 10 zero-initialized elements
		NAMESPACE::vector<int>::size_type sz = vec.size();

		// assign some values:
		for (unsigned i = 0; i < sz; i++)
			vec[i] = i;

		// reverse vector using operator[]:
		for (unsigned i = 0; i < sz / 2; i++)
		{
			int temp;
			temp = vec[sz - 1 - i];
			vec[sz - 1 - i] = vec[i];
			vec[i] = temp;
		}
		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("AT");
	{
		NAMESPACE::vector<int> vec(10); // 10 zero-initialized ints

		// assign some values:
		for (unsigned i = 0; i < vec.size(); i++)
			vec.at(i) = i;

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("FRONT");
	{
		NAMESPACE::vector<int> vec;

		vec.push_back(78);
		vec.push_back(16);

		// now front equals 78, and back 16

		vec.front() -= vec.back();

		std::cout << "vec.front() is now " << vec.front() << '\n';
	}

	display_header("BACK");
	{
		NAMESPACE::vector<int> vec;

		vec.push_back(10);

		while (vec.back() != 0)
			vec.push_back(vec.back() - 1);

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("ASSIGN");
	{
		NAMESPACE::vector<int> first;
		NAMESPACE::vector<int> second;
		NAMESPACE::vector<int> third;

		first.assign(7, 100); // 7 ints with a value of 100

		NAMESPACE::vector<int>::iterator it;
		it = first.begin() + 1;

		second.assign(it, first.end() - 1); // the 5 central values of first

		int int_array[] = {1776, 7, 4};
		third.assign(int_array, int_array + 3); // assigning from array.

		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
		std::cout << "Size of third: " << third.size() << '\n';

		NAMESPACE::vector<Perso> perso_vec;
		Perso p("random_perso");
		perso_vec.assign(10, p);

		display_vector<NAMESPACE::vector<Perso> >(perso_vec, "perso_vec");

		NAMESPACE::vector<Perso> perso_vec2;
		perso_vec2.assign(perso_vec.begin(), perso_vec.end());
		display_vector<NAMESPACE::vector<Perso> >(perso_vec2, "perso_vec2");

	}

	display_header("PUSH_BACK");
	{
		NAMESPACE::vector<int> vec;

		for (int i = 1 ; i <= 10; i++)
			vec.push_back(i);

		std::cout << "vec stores " << int(vec.size()) << " numbers.\n";
	}

	display_header("POP_BACK");
	{
		NAMESPACE::vector<int> vec;
		int sum(0);
		vec.push_back(100);
		vec.push_back(200);
		vec.push_back(300);

		while (!vec.empty())
		{
			sum += vec.back();
			vec.pop_back();
		}

		std::cout << "The elements of vec add up to " << sum << '\n';
	}

	display_header("INSERT");	
	{
		NAMESPACE::vector<int> vec(3, 100);
		NAMESPACE::vector<int>::iterator it;

		it = vec.begin();
		it = vec.insert(it, 200);

		vec.insert(it, 2, 300);

		// "it" no longer valid, get a new one:
		it = vec.begin();

		NAMESPACE::vector<int> anothervector(2, 400);
		display_vector<NAMESPACE::vector<int> >(anothervector, "anothervector");
		vec.insert(it + 3, anothervector.begin(), anothervector.end());
		display_vector<NAMESPACE::vector<int> >(vec, "vec");

		int myarray[] = {501, 502, 503};
		vec.insert(vec.begin(), myarray, myarray + 3);
		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("ERASE");
	{
		NAMESPACE::vector<int> vec;
		display_vector<NAMESPACE::vector<int> >(vec, "vec");
		std::cout << "set some values (from 1 to 10)\n";
		for (int i = 1; i <= 10; i++)
			vec.push_back(i);
		display_vector<NAMESPACE::vector<int> >(vec, "vec");
		std::cout << "erase the 6th element\n";
		vec.erase(vec.begin() + 5);
		display_vector<NAMESPACE::vector<int> >(vec, "vec");
		std::cout << "erase the first 3 elements\n";
		vec.erase(vec.begin(), vec.begin() + 3);
		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("SWAP");
	{
		NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
		NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200

		foo.swap(bar);

		display_vector<NAMESPACE::vector<int> >(foo, "foo");
		display_vector<NAMESPACE::vector<int> >(bar, "bar");
	}	

	display_header("CLEAR");
	{
		NAMESPACE::vector<int> vec;
		vec.push_back(100);
		vec.push_back(200);
		vec.push_back(300);

		display_vector<NAMESPACE::vector<int> >(vec, "vec");

		vec.clear();
		vec.push_back(1101);
		vec.push_back(2202);

		display_vector<NAMESPACE::vector<int> >(vec, "vec");
	}

	display_header("COMPARATORS");
	{
		NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
		NAMESPACE::vector<int> bar(2, 200); // two ints with a value of 200

		if (foo == bar)
			std::cout << "foo == bar\n";
		if (foo != bar)
			std::cout << "foo != bar\n";
		if (foo < bar)
			std::cout << "foo < bar\n";
		if (foo > bar)
			std::cout << "foo > bar\n";
		if (foo <= bar)
			std::cout << "foo <= bar\n";
		if (foo >= bar)
			std::cout << "foo > bar\n";
	}

	display_header("SWAP");
	{
		NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
		NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200
		std::cout << "*before\n";
		display_vector<NAMESPACE::vector<int> >(foo, "foo");
		display_vector<NAMESPACE::vector<int> >(bar, "bar");
		foo.swap(bar);
		std::cout << "*after\n";
		display_vector<NAMESPACE::vector<int> >(foo, "foo");
		display_vector<NAMESPACE::vector<int> >(bar, "bar");
	}

	display_header("AWESOME TESTS");	
	{
		NAMESPACE::vector<Awesome> test(21, 12);
		print_vector<Awesome>(test);
		NAMESPACE::vector<Awesome> test2;
		print_vector<Awesome>(test2);
		test2.push_back(12);
		test2.push_back(8);
		test2.push_back(16);
		print_vector<Awesome>(test2);
		std::cout << "SAME ?" << (test.begin() + 1 == test2.begin() + 1) << std::endl;
		test.assign(test2.begin(), test2.end());
		print_vector<Awesome>(test);
		test = test2;
		print_vector<Awesome>(test);
		std::cout << "SAME ?" << std::endl;
		std::cout << (test.begin() + 1 == test2.begin() + 1) << std::endl;
		test.insert(test.end(), test2.begin(), test2.end());
		print_vector<Awesome>(test);
		test.insert(test.begin(), test2.begin(), test2.end());
		test2 = test;
		print_vector<Awesome>(test);
		std::cout << "end awesome test" << std::endl;
	}
}
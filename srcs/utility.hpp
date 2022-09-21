
#pragma once
#include <cstddef>

namespace ft
{
	template <typename T>
	void swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	// https://cplusplus.com/reference/algorithm/equal/
	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
      			return false;
    		++first1; 
			++first2;
  		}
  		return true;
	}

	// https://cplusplus.com/reference/algorithm/lexicographical_compare/
	template <typename InputIterator1, typename InputIterator2>
  	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
  		while (first1 != last1)
  		{
    		if (first2 == last2 || *first2 < *first1)
				return false;
    		else if (*first1 < *first2)
				return true;
    		++first1; 
			++first2;
  		}
  		return (first2 != last2);
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
//                                                                                 ITERATOR TRAITS                                                                                                            |
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
namespace ft
{
    struct random_access_iterator_tag {};

    template <class Iterator>
    struct iterator_traits
    {
		typedef typename Iterator::value_type           value_type;       		// type de valeur apres dereferncement
        typedef typename Iterator::pointer              pointer;               
        typedef typename Iterator::reference            reference;             
        typedef typename Iterator::difference_type      difference_type;       // distance entre iterateurs
        typedef typename Iterator::iterator_category    iterator_category;     // la catégorie de l'itérateur (input, output, forward, bidirectional, random_access )
    };

    template<typename T>
    struct iterator_traits<T*>
    {
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef ptrdiff_t								difference_type;
		typedef std::random_access_iterator_tag			iterator_category;  
    };

    template<typename T>
    struct iterator_traits<const T*>
    {
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef ptrdiff_t								difference_type;
		typedef std::random_access_iterator_tag			iterator_category;  
    };
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
//                                                                                  ENABLE IF                                                                                                             |
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  // https://en.cppreference.com/w/cpp/types/enable_if

namespace ft
{
	template<bool Cond, class T = void> 
	struct enable_if 
	{};

	template<class T> 
	struct enable_if<true, T> 
	{ 
		typedef T type;
	};
}  
 

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
//                                                                                  IS INTEGRAL                                                                                                             |
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

namespace ft
{
    template <class T>
	struct is_integral { static const bool value = false; };
    template <>
	struct is_integral<bool> { static const bool value = true; };
	template <>
	struct is_integral<char> { static const bool value = true; };
	template <>
	struct is_integral<wchar_t> { static const bool value = true; };
	template <>
	struct is_integral<signed char> { static const bool value = true; };
	template <>
	struct is_integral<short int> { static const bool value = true; };
	template <>
	struct is_integral<int> { static const bool value = true; };
	template <>
	struct is_integral<long int> { static const bool value = true; };
	template <>
	struct is_integral<long long int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned char> { static const bool value = true; };
	template <>
	struct is_integral<unsigned short int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long long int> { static const bool value = true; };
	template <>
	struct is_integral<const bool> { static const bool value = true; };
	template <>
	struct is_integral<const char> {  static const bool value = true; };
	template <>
	struct is_integral<const wchar_t> { static const bool value = true; };
	template <>
	struct is_integral<const signed char> { static const bool value = true; };
	template <>
	struct is_integral<const short int> { static const bool value = true; };
	template <>
	struct is_integral<const int> { static const bool value = true; };
	template <>
	struct is_integral<const long int> { static const bool value = true; };
	template <>
	struct is_integral<const long long int> { static const bool value = true; };
	template <>
	struct is_integral<const unsigned char> { static const bool value = true; };
	template <>
	struct is_integral<const unsigned short int> { static const bool value = true; };
	template <>
	struct is_integral<const unsigned int> { static const bool value = true; };
	template <>
	struct is_integral<const unsigned long int> { static const bool value = true; };
	template <>
	struct is_integral<const unsigned long long int> { static const bool value = true; };

}
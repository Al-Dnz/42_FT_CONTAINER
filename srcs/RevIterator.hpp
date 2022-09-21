#pragma once

#include "utility.hpp"

#include <iostream>


namespace ft
{
    template <class Iterator> 
	class reverse_iterator
    {    
        public:
			typedef 			Iterator                                        iterator_type;              
			typedef typename    iterator_traits<Iterator>::iterator_category    iterator_category;         
			typedef typename    iterator_traits<Iterator>::value_type           value_type;               
			typedef typename    iterator_traits<Iterator>::difference_type      difference_type;           
			typedef typename    iterator_traits<Iterator>::pointer              pointer;                   
			typedef typename    iterator_traits<Iterator>::reference            reference;                
        
        private:
			Iterator	_it;

        public:
        	reverse_iterator() : _it(iterator_type()) {};

      		explicit	reverse_iterator(iterator_type x):
				_it(x) 
			{};

       		template <class I>
        	reverse_iterator (const reverse_iterator<I>& rev_it):
				_it(rev_it.base())
			{};

        	Iterator base() const  {return (_it);};

			pointer                 operator->() const 
			{
				return &(operator*());
			};

			reference               operator[](difference_type n)  
			{
				return _it[-n - 1];
			};
			
			reference               operator*() const 
			{
				iterator_type temp = _it;
				return (*--temp);
			};

			reverse_iterator&       operator++() 
			{
				--_it;
				return *this;
			};

			reverse_iterator        operator++(int) 
			{
				reverse_iterator tmp = *this; 
				++(*this); 
				return tmp;
			};

			reverse_iterator&       operator--() 
			{	
				++_it; 
				return *this;
			};

			reverse_iterator        operator--(int) 
			{
				reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			};

			reverse_iterator        operator+ (difference_type n) const 
			{
				return reverse_iterator(_it - n);
			};

			reverse_iterator&       operator+=(difference_type n) 
			{
				_it -= n;
				return (*this);
			};

			reverse_iterator        operator- (difference_type n) const 
			{
				return reverse_iterator(_it + n);
			};

			reverse_iterator&       operator-=(difference_type n) 
			{
				_it += n; 
				return (*this);
			};
			
    };

	template< class Iterator1, class Iterator2>
	bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2>
	bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2>
	bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2>
	bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2>
	bool operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2> 
	bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template<class It1> 
	reverse_iterator<It1> operator+(typename reverse_iterator<It1>::difference_type n, const reverse_iterator<It1>& rev_it) 
	{
		reverse_iterator<It1> tmp(rev_it); 
		tmp += n; 
		return tmp;
	}

	template<class It1, class It2> 
	typename reverse_iterator<It1>::difference_type	operator-(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{
		return rhs.base() - lhs.base();
	}

};
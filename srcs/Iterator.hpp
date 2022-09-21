#pragma once

#include <iterator>
#include <cstddef>


namespace ft
{

/* 
	----------------------------------------------------------------------------------------------
	| VECTOR ITERATOR                                                                            |
	----------------------------------------------------------------------------------------------  
*/
    template<typename T>
    struct vector_iterator
    {
        typedef vector_iterator<T>					self_t;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef std::random_access_iterator_tag     iterator_category;

		private:
			pointer _ptr;

		public:
			vector_iterator():
				_ptr(NULL) 
			{}
			
			vector_iterator(const pointer& x):
				_ptr(x) 
			{}

			vector_iterator(const vector_iterator& x):
				_ptr(x.base())
			{}
			
			reference operator*() const
			{
				return *_ptr;
			}
			
			pointer operator->() const
			{
				return _ptr;
			}
			
			self_t& operator++()
			{
				_ptr++;
				return *this;
			}

			self_t operator++(int)
			{
				self_t _tmp = *this;
				_ptr++;
				return _tmp;
			}
			
			self_t& operator--()
			{
				_ptr--;
				return *this;
			}
			
			self_t operator--(int)
			{
				self_t _tmp = *this;
				_ptr--;
				return _tmp;
			}

			reference operator[](const difference_type& n) const
			{
				return _ptr[n];
			}

			self_t& operator+=(const difference_type& n)
			{
				_ptr += n;
				return *this;
			}

			self_t operator+(const difference_type& n) const
			{
				return self_t(_ptr + n);
			}

			self_t& operator-=(const difference_type& n)
			{
				_ptr -= n;
				return *this;
			}

			self_t operator-(const difference_type& n) const
			{
				return self_t(_ptr -n);
			}

			bool operator==(const self_t& x) const
			{
				return _ptr == x._ptr; 
			}

			bool operator!=(const self_t& x) const
			{
				return _ptr != x._ptr; 
			}

			bool operator<(const self_t& x) const
			{
				return _ptr < x._ptr;
			}
			

			bool operator>(const self_t& x) const
			{
				return _ptr > x._ptr; 
			}
			

			bool operator<=(const self_t& x) const
			{
				return _ptr <= x._ptr; 
			}

			bool operator>=(const self_t& x) const
			{
				return _ptr >= x._ptr; 
			}
			
			difference_type operator-(const self_t& x) const
			{
				return _ptr - x._ptr;
			}

			const pointer& base() const
			{
				return _ptr;
			}

    };

	template <typename T>
	vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T>& v)
	{
		return vector_iterator<T>(v.base() + n);
	}

/* 
	----------------------------------------------------------------------------------------------
	| VECTOR CONST ITERATOR                                                                      |
	----------------------------------------------------------------------------------------------  
*/

    template<typename T>
    struct vector_const_iterator
    {
        typedef vector_const_iterator<T>			self_t;
		typedef vector_iterator<T>					iterator;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef const T*							pointer;
        typedef const T&							reference;
        typedef std::random_access_iterator_tag     iterator_category;

		private:
			const T* _ptr;

		public:
			vector_const_iterator():
				_ptr(NULL)
			{}

			vector_const_iterator(const pointer& x): 
				_ptr(x)
			{}

			vector_const_iterator(const iterator& x):
				_ptr(x.base())
			{}

			vector_const_iterator(const vector_const_iterator& x):
				_ptr(x.base())
			{}
			
			reference operator*() const
			{
				return *_ptr;
			}
			
			pointer operator->() const
			{
				return _ptr;
			}
			
			self_t& operator++()
			{
				_ptr++;
				return *this;
			}

			self_t operator++(int)
			{
				self_t _tmp = *this;
				_ptr++;
				return _tmp;
			}
			
			self_t& operator--()
			{
				_ptr--;
				return *this;
			}
			
			self_t operator--(int)
			{
				self_t _tmp = *this;
				_ptr--;
				return _tmp;
			}

			reference operator[](const difference_type& n) const
			{
				return _ptr[n];
			}

			self_t& operator +=(const difference_type& n)
			{
				_ptr += n;
				return *this;
			}

			self_t operator+(const difference_type& n) const
			{
				return self_t(_ptr + n);
			}

			self_t& operator-=(const difference_type& n)
			{
				_ptr -= n;
				return *this;
			}

			self_t operator-(const difference_type& n) const
			{
				return self_t(_ptr - n);
			}

			bool operator==(const self_t& x) const
			{ return _ptr == x._ptr; }

			bool operator!=(const self_t& x) const
			{ return _ptr != x._ptr; }

			bool operator<(const self_t& x) const
			{ return _ptr < x._ptr; }

			bool operator>(const self_t& x) const
			{ return _ptr > x._ptr; }

			bool operator<=(const self_t& x) const
			{ return _ptr <= x._ptr; }

			bool operator>=(const self_t& x) const
			{ return _ptr >= x._ptr; }
			
			difference_type operator-(const self_t& x) const
			{
				return _ptr - x._ptr;
			}

			const pointer& base() const
			{
				return _ptr;
			}
    };

	template <typename T>
	vector_const_iterator<T> operator+(typename vector_const_iterator<T>::difference_type n, const vector_const_iterator<T>& v)
	{
		return vector_const_iterator<T>(v.base() + n);
	}

	template <typename T>
	bool operator==(const vector_iterator<T>& lhs, const vector_const_iterator<T>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename T>
	bool operator!=(const vector_iterator<T>& lhs, const vector_const_iterator<T>& rhs)
	{ return lhs.base() != rhs.base(); }
	
	template <typename T>
	bool operator<(const vector_iterator<T>& lhs, const vector_const_iterator<T>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename T>
	bool operator>(const vector_iterator<T>& lhs, const vector_const_iterator<T>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename T>
	bool operator<=(const vector_iterator<T>& lhs, const vector_const_iterator<T>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <typename T>
	bool operator>=(const vector_iterator<T>& lhs, const vector_const_iterator<T>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <typename T>
	typename vector_iterator<T>::difference_type operator-(const vector_iterator<T>& lhs, const vector_const_iterator<T>& rhs)
	{ return lhs.base() - rhs.base(); }


}

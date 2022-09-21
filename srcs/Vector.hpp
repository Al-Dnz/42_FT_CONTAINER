#pragma once

#include "Iterator.hpp"
#include "RevIterator.hpp"
#include "utility.hpp"
#include <memory>


namespace ft 
{
	template <class T, class Allocator = std::allocator<T> >
	class vector 
	{ 

		public:

		/* 
			----------------------------------------------------------------------------------------------
			| TYPES                                                                                      |
			----------------------------------------------------------------------------------------------  
		*/
			typedef	T																						value_type;
			typedef	size_t																					size_type;

			typedef Allocator 																				allocator_type;
			typedef typename Allocator::reference 															reference;
			typedef typename Allocator::const_reference 													const_reference;
			typedef typename Allocator::pointer 															pointer;
			typedef typename Allocator::const_pointer 														const_pointer;

			typedef	vector_iterator<value_type>																iterator;
			typedef	vector_const_iterator<value_type>														const_iterator;
			
			typedef	typename iterator::difference_type						    							difference_type;
			
			typedef	reverse_iterator<const_iterator>														const_reverse_iterator;
        	typedef	reverse_iterator<iterator>																reverse_iterator;

			/* 
			----------------------------------------------------------------------------------------------
			| CONSTRUCT / COPY / DESTROY                                                                 |
			----------------------------------------------------------------------------------------------  
			*/

			
			explicit vector(const Allocator &alloc = Allocator()):
				_arr(NULL),
				_alloc(alloc),
				_size(0),
				_capacity(0)
			{
				return;
				_arr = _alloc.allocate(0);
			};

			explicit vector(size_type n, const T& val = T(), const Allocator& alloc = Allocator()):
				_arr(NULL),
				_alloc(alloc),
				_size(n),
				_capacity(n)
			{
				_arr = _alloc.allocate(n);
				for(size_t i = 0; i < _size; i++)
					_alloc.construct(&_arr[i], val);
			};

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0):
				_alloc(alloc),
				_size(0)
			{
				for (InputIterator it = first; it != last; it++)
					_size++;
				_capacity = _size;
				_arr = _alloc.allocate(_capacity);
				size_t i = 0;
				
				for (InputIterator it = first; it != last; it++)
				{
					_alloc.construct(&_arr[i], *it);
					i++;
				}
			};

			vector(const vector<T, Allocator>& x):
				_alloc(x._alloc),
				_size (x._size),
				_capacity(x._size)
			{
				if (this != &x)
				{
					_arr = _alloc.allocate(x._size);
					for(size_t i = 0; i < _size; i++)
						_alloc.construct(&_arr[i], x._arr[i]);
				}
			};

			~vector()
			{
				this->clear();
				_alloc.deallocate(_arr, _capacity);
			};
			

			vector<T, Allocator>& operator=(const vector<T, Allocator>& x)
			{
				size_t i = 0;

				if (this == &x)
					return *this;
				_alloc = x._alloc;
				while (i < _size)
				{
					_alloc.destroy(&_arr[i]);
					i++;
				}
				if (this->_capacity < x._size)
				{
					if (_capacity != 0)
						_alloc.deallocate(_arr, _capacity);
					_capacity = x._size;
					_arr = this->_alloc.allocate(x._size);
				}
				_size = x._size;
				for(size_t i = 0; i < this->_size; i++)
					_alloc.construct(&_arr[i], x._arr[i]);
				return *this;
			};

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				clear();
				insert(begin(), first, last);
			};

			void assign(size_type n, const T& u)
			{
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = NULL;
				_size = n;
				_capacity = n;
				_arr = _alloc.allocate(n);
				for(size_t i = 0; i < _size; i++)
					_alloc.construct(&_arr[i], u);
			};

			/* 
			----------------------------------------------------------------------------------------------
			| ALLOCATOR                                                                                  |
			----------------------------------------------------------------------------------------------  
			*/

			allocator_type get_allocator() const {return _alloc;};

			/* 
			----------------------------------------------------------------------------------------------
			| ITERATORS                                                                                  |
			----------------------------------------------------------------------------------------------  
			*/

			iterator begin() {return iterator(this->_arr);};
			const_iterator begin() const {return const_iterator(this->_arr);};;
			iterator end() {return iterator(this->_arr + this->_size);};
			const_iterator end() const {return const_iterator(this->_arr + this->_size);};
			reverse_iterator rbegin() {return reverse_iterator(this->end());};
			const_reverse_iterator rbegin() const {return const_reverse_iterator(this->end());};
			reverse_iterator rend() {return reverse_iterator(this->begin());};
			const_reverse_iterator rend() const {return const_reverse_iterator(this->begin());};

			/* 
			----------------------------------------------------------------------------------------------
			| CAPACITY                                                                                   |
			----------------------------------------------------------------------------------------------  
			*/

			size_type size() const { return _size; };

			size_type max_size() const { return _alloc.max_size();};

			/* 
			Resizes the container so that it contains n elements.
			If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
			If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
			If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
			Notice that this function changes the actual content of the container by inserting or erasing elements from it.
			*/	
			void resize(size_type sz, T c = T())
			{
				if (sz > _capacity)
				{
					if (sz < _capacity * 2)
						reserve(_capacity * 2);
					else
						reserve(sz);
				}
				for (size_type i = _size; i < sz; i++)
					_alloc.construct(&this->_arr[i], c);
				for (size_type i = sz; i < _size; i++)
					_alloc.destroy(&this->_arr[i]);
				_size = sz;
			};

			size_type capacity() const { return _capacity;};

			bool empty() const {return (_size == 0);};

			/*
			Requests that the vector capacity be at least enough to contain n elements.
			If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
			In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
			This function has no effect on the vector size and cannot alter its elements.
			*/
			void reserve(size_type n)
			{
				pointer temp;
				size_t initial_size = _size;

				if (n <= _capacity)
					return ;
				if (n > max_size())
					throw std::length_error("vector::reserve");
				
				temp = _alloc.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(temp + i, _arr[i]);
				clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = temp;
				_capacity = n;
				_size = initial_size;
			}

			/* 
			----------------------------------------------------------------------------------------------
			| ELEMENTS ACCESS                                                                            |
			----------------------------------------------------------------------------------------------  
			*/

			reference operator[](size_type n)
			{
				return this->_arr[n];
			};

			const_reference operator[](size_type n) const
			{
				return this->_arr[n];
			};

			const_reference at(size_type n) const
			{
				if (n >= this->size())
                	throw std::out_of_range("vector::out_of_range");
				return _arr[n];
			};

			reference at(size_type n)
			{
				if (n >= this->size())
                	throw std::out_of_range("vector::out_of_range");
				return _arr[n];
			};

			reference front() {return *this->begin();};

			const_reference front() const {return *this->begin();};

			reference back() {return _arr[_size - 1];};

			const_reference back() const {return _arr[_size - 1];};

			/* 
			----------------------------------------------------------------------------------------------
			| MODIFIERS                                                                                 |
			----------------------------------------------------------------------------------------------  
			*/

			void push_back (const T& x)
			{
				if(_size == _capacity)
					reserve(_capacity == 0 ? 1 : _capacity * 2);
				_alloc.construct(_arr + _size, x);
				_size++;
			}

			void pop_back()
			{
				if (this->empty())
					return;
				_alloc.destroy(&_arr[_size - 1]);
				_size--;
			};

			iterator insert(iterator position, const T& x)
			{
				size_type index = position - this->begin();
				insert(position, 1, x);
				return _arr + index;
			};

			void insert(iterator position, size_type n, const T& val)
			{
				ft::vector<T> tmp;
				size_type diff = std::distance(this->begin(), position);
				if (this->_size + n >= this->_capacity * 2)
					tmp.reserve(this->_size + n);
				else if (this->_size + n >= this->_capacity)
					tmp.reserve(this->_size * 2);
				else
					tmp.reserve(this->_capacity);
				size_type i = 0;
				while (i < diff)
					tmp.push_back(this->_arr[i++]);
				while (n--)
					tmp.push_back(val);
				while (i < this->size())
					tmp.push_back(this->_arr[i++]);
				this->swap(tmp);
			};

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				vector		temp = *this;
				size_type	init = position - this->begin();
				size_type	i = init;

                while (first != last)
                {
                    if (i < this->size())
						(*this)[i] = *first;
					else
						push_back(*first);
                    first++;
                    i++;
                }
                iterator it = temp.begin() + init;
                while (it != temp.end())
                {
					if (i < _size)
						(*this)[i] = *it;
					else
						push_back(*it);
                    it++;
                    i++;
				}
			};

			iterator erase(iterator position)
			{
          		int ret = std::distance(begin(), position);
				if (position == end())
					pop_back();
				while (position != this->end() - 1)
				{
					_alloc.destroy(&*position);
					_alloc.construct(&*position, *(position + 1));
					position++;
				}
				_alloc.destroy(&*position);
				_size--;
				return (iterator(this->begin() + ret));
        	};

			iterator erase(iterator first, iterator last)
			{
				int ret = std::distance(this->begin(), first);
				int distance = std::distance(first, last);
				iterator current = first;
				while (current != last)
				{
					_alloc.destroy(&*current);
					current++;
				}
				while (first != this->end() && last != this->end())
				{
					_alloc.construct(&*first, *last);
					_alloc.destroy(&*last);
					first++;
					last++;
				}
				_size -= distance;
				return (begin() + ret);
			};

			void swap(vector<T, Allocator> &x)
			{
				ft::swap(_arr, x._arr);
				ft::swap(_size, x._size);
				ft::swap(_capacity, x._capacity);
				ft::swap(_alloc, x._alloc);
			};

			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_size = 0;
			};

			/* 
			----------------------------------------------------------------------------------------------
			| ATTRIBUTES                                                                                 |
			----------------------------------------------------------------------------------------------  
			*/

			private:
				pointer			_arr;
				allocator_type	_alloc;
				size_type 		_size;  
				size_type 		_capacity;
		};

	template< class T, class Alloc >
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < rhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs > rhs);
	}
	
	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}
}

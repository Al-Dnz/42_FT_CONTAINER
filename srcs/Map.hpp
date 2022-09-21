
#pragma once

#include <memory>
#include <iostream>
#include "RevIterator.hpp"
#include "RBT_iterator.hpp"
#include "Pair.hpp"
#include "RBT.hpp"

namespace ft 
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
/* 
		----------------------------------------------------------------------------------------------
		| TYPES                                                                                      |
		----------------------------------------------------------------------------------------------  
*/

		typedef Key 									key_type;
		typedef T 										mapped_type;
		typedef ft::pair<const Key, T>					value_type;
		typedef Compare 								key_compare;
		typedef Allocator								allocator_type;
		typedef value_type& 							reference;
		typedef const value_type&			 			const_reference;

 		typedef ptrdiff_t								difference_type;
        typedef size_t									size_type;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		
		class value_compare: public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

			private:
				key_compare _comp;

				value_compare(key_compare const & c): 
					_comp(c)
				{}

			public:
				bool operator()(const value_type& x, const value_type& y) const
				{
					return _comp(x.first, y.first);
				}
		};

		typedef RBT<value_type, value_compare, allocator_type> 	tree_type;
		typedef typename tree_type::iterator					iterator;
		typedef typename tree_type::const_iterator				const_iterator;
		typedef typename tree_type::reverse_iterator			reverse_iterator;
		typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;

/* 
		----------------------------------------------------------------------------------------------
		| CONSTRUCT / COPY / DESTROY                                                                 |
		----------------------------------------------------------------------------------------------  
*/
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_RBT(tree_type(comp, alloc)), 
			_alloc(alloc), 
			_compare(comp) 
			{}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_RBT(tree_type(first, last, comp, alloc)),
			_alloc(alloc),
			_compare(comp)
		{}
		
		map(const map<Key,T,Compare,Allocator>& x):
			_RBT(x._RBT),
			_alloc(x._alloc),
			_compare(x._compare)
		{}

		~map()
		{}

/* 
		----------------------------------------------------------------------------------------------
		| ASSIGNATOR                                                                                |
		----------------------------------------------------------------------------------------------  
*/

		map<Key,T,Compare,Allocator>&operator=(const map<Key,T,Compare,Allocator>& rhs)
		{
			if (this != &rhs)
			{
				_alloc = rhs._alloc;
				_compare = rhs._compare;
				_RBT = rhs._RBT;
			}
			return *this;
		};

/* 
		----------------------------------------------------------------------------------------------
		| ALLOCATOR                                                                                |
		----------------------------------------------------------------------------------------------  
*/

		allocator_type get_allocator() const
		{
			return (_RBT.get_allocator());
		}

/* 
		----------------------------------------------------------------------------------------------
		| ITERATORS                                                                                  |
		----------------------------------------------------------------------------------------------  
*/

		iterator begin() {return _RBT.begin();};
		const_iterator begin() const {return _RBT.begin();};

		iterator end() {return _RBT.end();};
		const_iterator end() const {return _RBT.end();};

		reverse_iterator rbegin() {return _RBT.rbegin();};
		const_reverse_iterator rbegin() const {return _RBT.rbegin();};

		reverse_iterator rend() {return _RBT.rend();};
		const_reverse_iterator rend() const {return _RBT.rend();};

/* 
		----------------------------------------------------------------------------------------------
		| CAPACITY                                                                                   |
		----------------------------------------------------------------------------------------------  
*/
		bool empty() const
		{
			return _RBT.empty();
		};

		size_type size() const
		{
			return _RBT.size();
		};

		size_type max_size() const
		{
			return _RBT.max_size();
		};

/* 
		----------------------------------------------------------------------------------------------
		| ELEMENTS ACCESS                                                                            |
		----------------------------------------------------------------------------------------------  
*/
		T& operator[](const key_type& key)
		{
			value_type p = ft::make_pair(key, mapped_type());
			return (_RBT.insert(p).first)->second;
		};

		T& at(const key_type &key)
		{
			iterator it = _RBT.find(ft::make_pair(key, mapped_type()));
			if (it == _RBT.end())
				throw std::out_of_range("map::at: key not found");
			return (it->second);
		}

/* 
		----------------------------------------------------------------------------------------------
		| MODIFIERS                                                                                 |
		----------------------------------------------------------------------------------------------  
*/

		pair<iterator, bool> insert(const value_type& x)
		{
			return (_RBT.insert(x));
		};

		// TO SEE
		iterator insert(iterator position, const value_type& x)
		{
			return (_RBT.insert(position, x));
		};

		template <class InputIterator>
		void insert(typename ft::enable_if< !is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
		{
			_RBT.insert(first, last);
		};


		void erase(iterator position)
		{
			_RBT.erase(position);
		};

		size_type erase(const key_type& key)
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(key, mapped_type());
			return (_RBT.erase(p));
		};

		void erase(iterator first, iterator last)
		{
			_RBT.erase(first, last);
		};

		void swap(map<Key, T, Compare,Allocator>& map)
		{
			ft::swap(_compare, map._compare);
			_RBT.swap(map._RBT);
		};

		void clear()
		{
			_RBT.clear();
		};

/* 
		----------------------------------------------------------------------------------------------
		| OBSERVERS                                                                                 |
		----------------------------------------------------------------------------------------------  
*/
		key_compare key_comp() const
		{
			return _compare;
		};

		value_compare value_comp() const
		{
			return _RBT.value_comp();
		};

/* 
		----------------------------------------------------------------------------------------------
		| MAP OPERATIONS                                                                            |
		----------------------------------------------------------------------------------------------  
*/
		iterator find(const key_type& key)
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(key, mapped_type());
			return _RBT.find(p);

		};

		const_iterator find(const key_type& key) const
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(key, mapped_type());
			return _RBT.find(p);
		};

		size_type count(const key_type& key) const
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(key, mapped_type());
			return _RBT.count(p);
		};

		iterator lower_bound(const key_type& x)
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(x, mapped_type());
			return _RBT.lower_bound(p);
		};

		const_iterator lower_bound(const key_type& x) const
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(x, mapped_type());
			return _RBT.lower_bound(p);
		};

		iterator upper_bound(const key_type& x)
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(x, mapped_type());
			return _RBT.upper_bound(p);
		};

		const_iterator upper_bound(const key_type& x) const
		{
			ft::pair<key_type, mapped_type> p = ft::make_pair(x, mapped_type());
			return _RBT.upper_bound(p);
		};

		ft::pair<iterator, iterator> equal_range(const key_type& x)
		{
			//ft::pair<key_type, mapped_type> p = ft::make_pair(x, mapped_type());
			ft::pair<iterator, iterator> res  = ft::make_pair<iterator, iterator>(lower_bound(x), upper_bound(x));

			return res;

		};

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& x) const
		{
			//ft::pair<key_type, mapped_type> p = ft::make_pair(x, mapped_type());
			ft::pair<const_iterator, const_iterator> res  = ft::make_pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x));
			return res;
		};

/* 
		----------------------------------------------------------------------------------------------
		| FRIENDS                                                                                     |
		----------------------------------------------------------------------------------------------  
*/

		// template<class Key, class T, class Compare, class Allocator>
		friend bool operator==( map<Key, T, Compare, Allocator>  const & lhs, map<Key, T, Compare, Allocator> const & rhs)
		{ 
			return lhs._RBT == rhs._RBT;
		}

		// template<class Key, class T, class Compare, class Allocator>
		friend bool operator<( map<Key, T, Compare, Allocator>  const & lhs,  map<Key, T, Compare, Allocator> const & rhs)
		{ 
			return lhs._RBT < rhs._RBT;
		}

		private:
			tree_type		_RBT;
			allocator_type	_alloc;
			key_compare		_compare;
	};

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	// template <class Key, class T, class Compare, class Alloc>
	// bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ 
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}

}


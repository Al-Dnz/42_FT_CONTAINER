#pragma once

#include "RBT.hpp"
#include "RevIterator.hpp"
#include "RBT_iterator.hpp"
#include "Pair.hpp"
#include <utility>
#include "utility.hpp"
#include "RBT_node.hpp"


namespace ft
{
	template  <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
		public:
			typedef Key 											key_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef key_compare										value_compare;
			typedef key_type										value_type;
			typedef Allocator										allocator_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef RBT<value_type, key_compare, allocator_type>	tree_type;
			typedef typename tree_type::iterator					iterator;
			typedef typename tree_type::const_iterator				const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			tree_type _RBT;
		
		public:
			explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()):
				_RBT(tree_type(comp, alloc)) 
			 {}
			
			template< class InputIt >
			set(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator &alloc = Allocator()):
				_RBT(tree_type(first, last, comp, alloc))
			{}

			set(const set& src): 
				_RBT(tree_type(src._RBT))
			{}

			set &operator=(const set & rhs)
			{
				if (this != &rhs)
					_RBT = rhs._RBT;
				return (*this);
			}

			allocator_type get_allocator() const
			{
				return _RBT.get_allocator();
			}

			size_type size() const
			{
				return (_RBT.size());
			}

			size_type max_size() const
			{
				return (_RBT.max_size());
			}

			bool empty() const
			{
				return (_RBT.empty());
			}

			value_compare value_comp() const
			{
				return (_RBT.value_comp());
			}

			key_compare key_comp() const
			{
				return (Compare());
			}

			iterator begin()
			{
				return (_RBT.begin());
			}

			const_iterator begin() const
			{
				return (_RBT.begin());
			}

			iterator end()
			{
				return (_RBT.end());
			}

			const_iterator end() const
			{
				return (_RBT.end());
			}

			reverse_iterator rbegin()
			{
				return (_RBT.rbegin());
			}

			const_reverse_iterator rbegin() const
			{
				return (_RBT.rbegin());
			}

			reverse_iterator rend()
			{
				return (_RBT.rend());
			}

			const_reverse_iterator rend() const
			{
				return (_RBT.rend());
			}
		
			void clear()
			{
				_RBT.clear();
			}	

			void swap(set & set) 
			{
				_RBT.swap(set._RBT);
			}

			iterator find(const Key& key)
			{
				return _RBT.find(key);
			}
			
			const_iterator find(const Key& key) const 
			{
				return _RBT.find(key);
			}

			size_type count(const Key &key) const
			{
				return _RBT.count(key);
			}

			iterator lower_bound(const key_type& k)
			{
				return _RBT.lower_bound(k);
			}

			const_iterator lower_bound(const key_type& k) const
			{
				return _RBT.lower_bound(k);
			}

			iterator upper_bound(const key_type& k)
			{
				return _RBT.upper_bound(k);
			}

			const_iterator upper_bound(const key_type& k) const
			{
				return _RBT.upper_bound(k);
			}
			
			ft::pair<iterator, iterator> equal_range(const key_type & k)
			{
				return  _RBT.equal_range(k);
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type & k) const
			{
				return  _RBT.equal_range(k);
			}

			ft::pair<iterator, bool> insert( const value_type& value )
			{
				return _RBT.insert(value);
			}

			iterator insert( iterator hint, const value_type& value) {
				return _RBT.insert(hint, value);
			}

			template<class InputIt>
			void insert(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
			{
				_RBT.insert(first, last);
			}

			void erase(iterator pos)
			{
				_RBT.erase(pos);
			}

			size_type erase(const Key & key)
			{
				return _RBT.erase(key);
			}

			void erase(iterator first, iterator last)
			{
				_RBT.erase(first, last);
			}

			template<class K, class Com, class Al>
			friend bool operator==(const set<K, Com, Al>& lhs, const set<K, Com, Al>& rhs);

			template<class K, class Com, class Al>
			friend bool operator<(const set<K, Com, Al>& lhs, const set<K, Com, Al>& rhs);

	};

	template<class K, class Com, class Al>
	bool operator==(const set<K, Com, Al>& lhs, const set<K, Com, Al>& rhs)
	{
		return lhs._RBT == rhs._RBT;	
	};

	template<class K, class Com, class Al>
	bool operator<(const set<K, Com, Al>& lhs, const set<K, Com, Al>& rhs)
	{
		return lhs._RBT < rhs._RBT;
	};


	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return !(lhs > rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class Key,class Compare, class Alloc>
	void swap(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

}




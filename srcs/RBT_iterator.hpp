#pragma once

#include <cstddef>
#include "utility.hpp"
#include "RBT_node.hpp"
#include "RevIterator.hpp"

namespace ft
{

/* 
	----------------------------------------------------------------------------------------------
	| RED BLACK TREE ITERATORS                                                                   |
	----------------------------------------------------------------------------------------------  
*/
	template <class T>
	struct RBT_iterator
	{
		typedef RBT_iterator<T>						self_t;
		typedef Node<T>			    				node_t;
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
		typedef std::bidirectional_iterator_tag     iterator_category;
		typedef ft::reverse_iterator<self_t>        reverse_iterator;

		private:
			node_t* _node_ptr;
		
		public:
			RBT_iterator():
				_node_ptr(NULL)
			{}

			explicit RBT_iterator(node_t* node):
				_node_ptr(node)
			{}

			RBT_iterator(RBT_iterator const &it ): 
				_node_ptr(it.node())
			{}

			node_t* node() const
			{
				return _node_ptr;
			}

			reference operator*() const
			{
				return *(_node_ptr->data);
			}

			pointer operator->() const
			{
				return _node_ptr->data;
			}

			self_t &operator++()
			{
				_node_ptr = successor(_node_ptr);
				return *this;
			}

			self_t operator++(int)
			{

				self_t tmp = *this;
				_node_ptr = successor(_node_ptr);
				return tmp;
			}

			self_t& operator--()
			{
				_node_ptr = predecessor(_node_ptr);
				return *this;
			}

			self_t operator--(int)
			{
				self_t tmp = *this;
				_node_ptr = predecessor(_node_ptr);
				return tmp;
			}

			self_t& operator=(const self_t& src) 
			{
				if (this != &src)
					this->_node_ptr = src._node_ptr;
				return *this;
			}

			bool operator==(const self_t &node) const
			{
				return _node_ptr == node._node_ptr;
			}

			bool operator!=(const self_t &node) const
			{
				return _node_ptr != node._node_ptr;
			}

			private:

			node_t* predecessor(node_t* x)
			{
				node_t* y;
				if (x->left && x->left->is_null == false)
					return x->node_max(x->left);
				y = x->parent;
				while (y->is_null == false && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			node_t* successor(node_t* x)
			{
				node_t* y;

				if (x->right && x->right->is_null == false)
					return x->node_min(x->right);
				y = x->parent;
				while (y->is_null == false && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}
	};

	template<typename A, typename B>
	bool operator==(const RBT_iterator<A> & lhs, const RBT_iterator<B> & rhs)
	{
			return (lhs.node() == rhs.node());
	}

	template<typename A, typename B>
	bool operator!=(const RBT_iterator<A> & lhs, const RBT_iterator<B> & rhs)
	{
			return (lhs.node() != rhs.node());
	}

/* 
	----------------------------------------------------------------------------------------------
	| RED BLACK TREE CONST ITERATORS                                                             |
	----------------------------------------------------------------------------------------------  
*/
	template <class T>
	struct RBT_const_iterator
	{
		typedef RBT_const_iterator<T> 						self_t;
		typedef const Node<T>								node_t;
		typedef RBT_iterator<T>								iterator;
        typedef T											value_type;
        typedef ptrdiff_t									difference_type;
        typedef const T*									pointer;
        typedef const T&                                 	reference;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef ft::reverse_iterator<self_t>				reverse_iterator;

		private:
			const node_t* _node_ptr;

		public:
			RBT_const_iterator():
				_node_ptr()
			{}

			explicit RBT_const_iterator(node_t* node):
				_node_ptr(node)
			{}

			RBT_const_iterator(const iterator &it):
				_node_ptr(it.node())
			{}

			iterator _const_cast() const
			{
				return iterator(static_cast<node_t* >(const_cast<node_t* >(_node_ptr)));
			}

			node_t* node() const
			{
				return _node_ptr;
			}

			reference operator*() const
			{
				return *(_node_ptr->data);
			}

			pointer operator->() const
			{
				return _node_ptr->data;
			}

			self_t &operator++()
			{
				_node_ptr = successor(_node_ptr);
				return *this;
			}

			self_t operator++(int)
			{
				self_t tmp = *this;
				_node_ptr = successor(_node_ptr);
				return tmp;
				
				return *this;
			}

			self_t &operator--()
			{
				_node_ptr = predecessor(_node_ptr);
				return *this;
			}

			self_t operator--(int)
			{
				self_t tmp = *this;
				_node_ptr = predecessor(_node_ptr);
				return tmp;
			}

			self_t& operator=(const self_t& src) 
			{
				if (this != &src)
					this->_node_ptr = src._node_ptr;
				return *this;
			}

			bool operator==(self_t const &node) const
			{
				return _node_ptr == node._node_ptr;
			}

			bool operator!=(self_t const &node) const
			{
				return _node_ptr != node._node_ptr;
			}

		private:
			node_t* predecessor(node_t* x)
			{
				node_t* y;
				if (x->left && x->left->is_null == false)
					return x->node_max(x->left);
				y = x->parent;
				while (y->is_null == false && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			node_t* successor(node_t* x)
			{
				node_t* y;

				if (x->right && x->right->is_null == false)
					return x->node_min(x->right);
				y = x->parent;
				while (y->is_null == false && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}
	};

	template<typename T>
	bool operator==(const RBT_const_iterator<T> & lhs, const RBT_const_iterator<T> & rhs)
	{
			return (lhs.node() == rhs.node());
	}

	template<typename T>
	bool operator!=(const RBT_const_iterator<T> & lhs, const RBT_const_iterator<T> & rhs)
	{
			return (lhs.node() != rhs.node());
	}
}
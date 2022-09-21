// https://www.programiz.com/dsa/red-black-tree


#pragma once
#include <iostream>
#include <cstddef>
#include <memory>

#include "RBT_node.hpp"
#include "RBT_iterator.hpp"
#include "RevIterator.hpp"
#include "utility.hpp"
#include "Pair.hpp"


namespace ft
{
	template<class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RBT
	{
		public:
			typedef T			value_type;
			typedef Compare		value_compare;
			typedef Allocator	allocator_type;
			typedef size_t		size_type;


			typedef typename Allocator::template 
									rebind<Node<T> >::other node_allocator;
			typedef typename allocator_type::pointer pointer;
			typedef	typename node_allocator::pointer node_pointer;
			
			typedef RBT_iterator<T>							iterator;
			typedef RBT_const_iterator<T>					const_iterator;
			typedef	ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

		private:
			node_pointer 				_root;
			node_pointer 				_TNULL;
			node_pointer				_toe;
			allocator_type				_data_alloc;
			node_allocator				_node_alloc;
			value_compare 				_compare;
			size_type					_size;

	/* 
			----------------------------------------------------------------------------------------------
			| INITIALISATION UTILS                                                                       |
			----------------------------------------------------------------------------------------------  
	*/

			void 	init_null(void)
			{
				_TNULL = _node_alloc.allocate(1);
				_node_alloc.construct(_TNULL, Node<value_type>());
				_TNULL->color = black;
				_TNULL->is_null = true;
			}

			void	init_toe(void)
			{
				_toe = _node_alloc.allocate(1);
				_node_alloc.construct(_toe, Node<value_type>());
				_toe->data = _data_alloc.allocate(1);
				_data_alloc.construct(_toe->data,value_type());
				_toe->color = black;
				_toe->is_null = false;
			}

			bool 	readable_node(node_pointer node) const
			{
				if (node == _TNULL || node == _toe)
					return false;
				return true;
			}

			void	adjust_toe(void)
			{
				if (_size == 0)
				{
					_root = _toe;
					return;
				}
				node_pointer node_max = _size > 1 ? rbt_max() : _root;
				node_max->right = _toe;
				_toe->parent = node_max ;
			}

	/* 
			----------------------------------------------------------------------------------------------
			| MOVE UTILS                                                                                 |
			----------------------------------------------------------------------------------------------  
	*/

			void leftRotate(node_pointer x)
			{
				node_pointer y = x->right;
				x->right = y->left;
				if (readable_node(y->left))
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void rightRotate(node_pointer x)
			{
				node_pointer y = x->left;

				x->left = y->right;
				if (readable_node(y->right))
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void transplant(node_pointer u, node_pointer v)
			{
				if (u->parent == NULL)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

	/* 
			----------------------------------------------------------------------------------------------
			| INSERT UTILS                                                                               |
			----------------------------------------------------------------------------------------------  
	*/

			pointer	create_data(const value_type &value)
			{
				pointer new_data = _data_alloc.allocate(1);
				_data_alloc.construct(new_data, value);
				return new_data;
			}

			node_pointer create_node(const value_type& value)
			{
				node_pointer new_node;

				new_node = _node_alloc.allocate(1);
				pointer data = create_data(value);
				_node_alloc.construct(new_node, Node<value_type>(data));
				new_node->left = _TNULL;
				new_node->right = _TNULL;
				
				return new_node;
			}

			node_pointer tree_graft(node_pointer to_insert, node_pointer new_node)
			{
				if (_root == _toe)
					_root = new_node;
				else
					node_graft(to_insert, new_node);
				return (new_node);
			}


			node_pointer	node_graft(node_pointer root, node_pointer new_node)
			{
				
				if (_compare(*new_node->data, *root->data))
				{
					if (readable_node(root->left))
						return (node_graft(root->left, new_node));
					root->left = new_node;
				}
				else if (_compare(*root->data, *new_node->data))
				{
					if (readable_node(root->right))
						return (node_graft(root->right, new_node));
					root->right = new_node;
				}
				new_node->parent = root;

				return (new_node);
			}


			// For balancing the tree after insertion
			void insertFix(node_pointer k)
			{
				node_pointer u;
				if (k == _root || k->parent == _root)
					return;
				while (k->parent && k->parent->color == black)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left;
						if (u->color == black)
						{
							u->color = red;
							k->parent->color = red;
							k->parent->parent->color = black;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								k = k->parent;
								rightRotate(k);
							}
							k->parent->color = red;
							k->parent->parent->color = black;
							leftRotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right;
						if (u->color == red)
						{
							u->color = red;
							k->parent->color = red;
							k->parent->parent->color = black;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								leftRotate(k);
							}
							k->parent->color = red;
							k->parent->parent->color = black;
							rightRotate(k->parent->parent);
						}
					}
					if (k == _root)
						break;
				}
				_root->color = red;
			}

	/* 
			----------------------------------------------------------------------------------------------
			| COPY UTILS                                                                                 |
			----------------------------------------------------------------------------------------------  
	*/

			node_pointer 	new_null(void)
			{
				node_pointer new_node;
				new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node<value_type>());
				new_node->color = red;
				new_node->is_null = true;
				return new_node;
			}

			node_pointer	new_toe(void)
			{
				node_pointer new_node;
				new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node<value_type>());
				new_node->data = _data_alloc.allocate(1);
				_data_alloc.construct(new_node->data,value_type());
				new_node->color = red;
				new_node->is_null = false;
				return new_node;
			}

			node_pointer dup_node(node_pointer original, node_pointer t_null, node_pointer t_toe)
			{
				if (original == _TNULL)
					return t_null;
				if (original == _toe)
					return t_toe;
				node_pointer new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Node<value_type>());
				if(original->data)
				{
					new_node->data = _data_alloc.allocate(1);
					_data_alloc.construct(new_node->data, *original->data);
				}
				new_node->color = original->color;
				new_node->is_null = original->is_null;
				new_node->left = t_null;
				new_node->right = t_null;
				
				return (new_node);
			}
		
			void	dup_child(node_pointer node, node_pointer original, node_pointer t_null, node_pointer t_toe)
			{
				if (original == NULL)
					return ;
				if (original->left->is_null)
					node->left = t_null;
				else
				{
					node->left = dup_node(original->left, t_null, t_toe);
					node->left->parent = node;
					dup_child(node->left, original->left, t_null, t_toe);
				}

				if (original->right->is_null)
					node->right = t_null;
				else if (original->right->right == NULL)
				{
					node->right = t_toe;
					t_toe->parent = node;
				}
				else
				{
					node->right = dup_node(original->right, t_null, t_toe);
					node->right->parent = node;
					dup_child(node->right, original->right, t_null, t_toe);
				}
			}
			
	/* 
			----------------------------------------------------------------------------------------------
			| DELETE UTILS                                                                               |
			----------------------------------------------------------------------------------------------  
	*/
			void 	free_node(node_pointer node)
			{
					if (!node || !readable_node(node))
						return ;
					_data_alloc.destroy(node->data);
					_data_alloc.deallocate(node->data, 1);
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					node = NULL;
			}

			void	free_tree(node_pointer node)
			{
				if (node && readable_node(node))
				{
					free_tree(node->left);
					free_tree(node->right);
					free_node(node);
				}
			}

			void	free_TNULL(void)
			{
					if (_TNULL == NULL)
						return;
					_node_alloc.destroy(_TNULL);
					_node_alloc.deallocate(_TNULL, 1);
					_TNULL = NULL;
			}

			void	free_toe(void)
			{
					if (_toe == NULL)
						return;
					_data_alloc.destroy(_toe->data);
					_data_alloc.deallocate(_toe->data, 1);
					_node_alloc.destroy(_toe);
					_node_alloc.deallocate(_toe, 1);
					_toe = NULL;
			}

			// For balancing the tree after deletion
			void deleteFix(node_pointer x)
			{

				node_pointer s;
				while (x != _root && x->color == black)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == red)
						{
							s->color = black;
							x->parent->color = red;
							leftRotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == black && s->right->color == black)
						{
							s->color = red;
							x = x->parent;
						}
						else
						{
							if (s->right->color == black)
							{
								s->left->color = black;
								s->color = red;
								rightRotate(s);
								s = x->parent->right;
							}
							s->color = x->parent->color;
							x->parent->color = black;
							s->right->color = black;
							leftRotate(x->parent);
							x = _root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == red)
						{
							
							s->color = black;
							x->parent->color = red;
							rightRotate(x->parent);
							s = x->parent->left;
						}

						if (s->right->color == black && s->right->color == black)
						{
							s->color = red;
							x = x->parent;
						}
						else
						{

							if (s->left->color == black)
							{
								s->right->color = black;
								s->color = red;
								leftRotate(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = black;
							s->left->color = black;
							rightRotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = black;
			}

	/* 
			----------------------------------------------------------------------------------------------
			| FIND UTILS                                                                                 |
			----------------------------------------------------------------------------------------------  
	*/
			node_pointer search(const value_type &value, node_pointer node) const
			{
				if(!node || node == _TNULL || node == _toe)
					return NULL;
				if (_compare(value, *node->data))
					return search(value, node->left);
				else if (_compare(*node->data, value))
					return search(value, node->right);
				return node;
			}
			
		public:
	/* 
			----------------------------------------------------------------------------------------------
			| ITERATORS                                                                                 |
			----------------------------------------------------------------------------------------------  
	*/

			iterator	end() { return (iterator(_toe));}
			const_iterator	end() const { return (const_iterator(_toe));}
			iterator	begin()
			{
				if (_size != 0)
					return (iterator(rbt_min()));
				else
					return (iterator(_toe));
			}
			const_iterator	begin() const
			{
				if (_size != 0)
					return (const_iterator(rbt_min()));
				else
					return (const_iterator(_toe));
			}

			reverse_iterator rbegin() { return (reverse_iterator(end()));}	
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(end()));}	
			reverse_iterator rend() { return (reverse_iterator(begin()));}	
			const_reverse_iterator rend() const { return (const_reverse_iterator(begin()));}	

	/* 
			----------------------------------------------------------------------------------------------
			| CANONIC METHODS                                                                            |
			----------------------------------------------------------------------------------------------  
	*/

			RBT(const Compare &comp, const allocator_type& alloc = allocator_type()):
				_root(NULL),
				_TNULL(NULL),
				_data_alloc(alloc),
				_node_alloc(node_allocator()),
				_compare(comp),
				_size(0)
			{
				init_null();
				init_toe();
				_root = _toe;
			}

			RBT(void):
				_root(NULL),
				_TNULL(NULL),
				_data_alloc(allocator_type()),
				_node_alloc(node_allocator()),
				_compare(value_compare()),
				_size(0)
			{
				init_null();
				init_toe();
				_root = _toe;
			}

			RBT(const RBT& src):
				_root(NULL),
				_compare(src._compare)
			{
				*this = src;
			}

			RBT& operator=(const RBT& rhs)
			{
				if (this != &rhs)
				{
					if (this->_root != NULL)
					{
						free_tree(_root);
						free_toe();
						free_TNULL();
						_root = NULL;
					}
						clear();
					_data_alloc = rhs._data_alloc;
					_node_alloc = rhs._node_alloc;
					_compare = rhs._compare;
					_size = rhs._size;
					_TNULL = new_null();
					_toe = new_toe();
					if (_size == 0)
						_root = _toe;
					else
					{
						this->_root = dup_node(rhs._root, this->_TNULL, this->_toe);
						dup_child(this->_root, rhs._root, this->_TNULL, this->_toe);
					}
				}
				return *this;
			}

			template<class InputIterator>
			RBT(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last, const value_compare& comp, const allocator_type& alloc = allocator_type()):	
				_root(NULL),
				_TNULL(NULL),
				_data_alloc(alloc),
				_node_alloc(node_allocator()),
				_compare(comp),
				_size(0)
			{
				init_null();
				init_toe();
				_root = _toe;
				for (; first != last; ++first)
					insert(*first);
			}

			~RBT()
			{
				free_tree(_root);
				free_toe();
				free_TNULL();
			}

	/* 
			----------------------------------------------------------------------------------------------
			| PUBLIC METHODS                                                                            |
			----------------------------------------------------------------------------------------------  
	*/

			node_pointer rbt_min() const
			{
				node_pointer node = _root;
				while (node != NULL && readable_node(node->left))
					node = node->left;
				return node;
			}

			node_pointer rbt_max() const
			{
				node_pointer node = _root;
				while (node != NULL && readable_node(node->right))
					node = node->right;
				return node;
			}

			void erase(iterator pos)
			{
				
				node_pointer y = pos.node();
				if (y == NULL)
					return;
				node_pointer tmp = y;
				node_pointer x;
				node_pointer z;
				z = y;
				int y_original_color = y->color;
				
			
				if (readable_node(y->left)== false)
				{
					x = y->right;
					transplant(y, y->right);
				}
				else if (readable_node(y->right) == false)
				{
					x = y->left;
					transplant(y, y->left);
				}
				else
				{
					y = z->node_min(z->right);
					y_original_color = y->color;
					x = y->right;

					if (y->parent == z)
						x->parent = y;
					else
					{
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				free_node(tmp);
				if (y_original_color == 0)
					deleteFix(x);
				_size--;
				adjust_toe();
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			size_type erase(const value_type& value)
			{
				node_pointer res = search(value, _root);
				if (res != NULL)
					erase(iterator(res));
				return (res != NULL);
			}

			size_type count(const value_type& value) const
			{
				 return (find(value) != end());
			}

			size_type size() const {return (_size);}

			size_type max_size() const {return (_data_alloc.max_size() / 2);}
			
			bool empty() const {return (_size == 0);}

			value_compare value_comp() const  {return (_compare);}

			allocator_type get_allocator() const{ return (_data_alloc);}

			void	clear(void)
			{
				free_tree(_root);
				// free_toe();
				// free_TNULL();
				_size = 0;
				_root = _toe;
			}

			iterator lower_bound(const value_type& value)
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if(!_compare(*first, value))
						return (first);
				}
				return (last);
			}

			const_iterator lower_bound(const value_type& value) const
			{
				const_iterator last = end();
				for (const_iterator first = begin(); first != last; first++)
				{
					if(!_compare(*first, value))
						return (first);
				}
				return (last);
			}

			iterator upper_bound(const value_type& value)
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if(_compare(value, *first))
						return (first);
				}
				return (last);
			}

			const_iterator upper_bound(const value_type& value) const
			{
				const_iterator last = end();
				for (const_iterator first = begin(); first != last; first++)
				{
					if(_compare(value, *first))
						return (first);
				}
				return (last);
			}

			void swap(RBT &tree)
			{
				ft::swap(_node_alloc, tree._node_alloc);
				ft::swap(_data_alloc, tree._data_alloc);
				ft::swap(_root, tree._root);
				ft::swap(_TNULL, tree._TNULL);
				ft::swap(_toe, tree._toe);
				ft::swap(_size, tree._size);
				ft::swap(_compare, tree._compare);
			}

			ft::pair<iterator, iterator> equal_range(const value_type &value)
			{
				ft::pair<iterator, iterator> p = ft::make_pair<iterator, iterator>(lower_bound(value), upper_bound(value));
				return (p);
			}

			// ft::pair<const_iterator, const_iterator> equal_range(const value_type &value)
			// {
			// 	ft::pair<iterator, iterator> p = ft::make_pair<const_iterator, const_iterator>(lower_bound(value), upper_bound(value));
			// 	return (p);
			// }

			ft::pair<iterator, bool> insert(value_type const &value)
			{

				node_pointer to_find = search(value, _root);
				if (to_find != NULL)
					return ft::pair<iterator, bool>(iterator(to_find), false);
				node_pointer new_node = create_node(value);
				tree_graft(_root, new_node);
				insertFix(new_node);
				_size++;
				ft::pair<iterator, bool> p(iterator(new_node), true);
				adjust_toe();
				return p;
			} 

			iterator insert(iterator position, const value_type& value)
			{
				node_pointer new_node = search(value,_root);
				if (new_node != NULL)
					return (iterator(new_node));
				new_node = create_node(value);
				if (position == begin())
				{
					if (position != end() && _compare(value, *position))
						tree_graft(rbt_min(), new_node);
					else
						tree_graft(_root, new_node);
				}
				else if (position == end())
				{
					if (position != begin() && _compare(*(--position), value))
						tree_graft(_toe->parent, new_node);
					else
						tree_graft(_root, new_node);
				}
				else
					tree_graft(_root, new_node);

				insertFix(new_node);
				_size++;
				adjust_toe();
				return (iterator(new_node));
			}

			template<class InputIterator>
			void insert(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last) 
			{
				for (; first != last; ++first)
					insert(*first);
			}

			iterator	find(const value_type& value)
			{
				node_pointer res = search(value, _root);

				if (res == NULL)
					return end();
				else
					return iterator(res);
			}

			const_iterator	find(const value_type& value) const
			{
				node_pointer res = search(value, _root);

				if (res == NULL)
					return end();
				else
					return const_iterator(res);
			}
	};

		template<class T, class Compare, class Allocator>
		bool operator<( RBT<T, Compare, Allocator> const & lhs,   RBT<T, Compare, Allocator> const & rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		template<class T, class Compare, class Allocator>
		bool operator>( RBT<T, Compare, Allocator> const & lhs,   RBT<T, Compare, Allocator> const & rhs)
		{
			return (rhs < lhs);
		}

		template<class T, class Compare, class Allocator>
		bool operator==( RBT<T, Compare, Allocator>  const & lhs,  RBT<T, Compare, Allocator>  const & rhs)
		{
			return  lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}	

}



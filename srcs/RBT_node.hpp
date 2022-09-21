#pragma once
#include <cstddef>

namespace ft
{

	enum e_color
	{
		black,
		red
	};

	template <class T>
	struct Node
	{
		T				*data;
		Node*			parent;
		Node*			left;
		Node*			right;
		bool			color;
		bool			is_null;

		Node(T *data = NULL):
			data(data),
			parent(NULL),
			left(NULL),
			right(NULL),
			color(red),
			is_null(false)
		{}

		Node( Node const & src) 
		{
			data = src.data;
			parent = src.parent;
			left = src.left;
			right = src.right;
			color = src.color;
			is_null = src.is_null;
		}

		Node& operator=(const Node& rhs)
		{
			if (this != &rhs)
			{
				data = rhs.data;
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				color = rhs.color;
				is_null = rhs.is_null;
			}
			return *this;
		}

		~Node(){};

		static Node* node_min( Node* x)
        {
            while (x->left != NULL && x->left->is_null == false)
                x = x->left;
            return x;
        }

        static const Node* node_min(const Node* x)
        {
            while (x->left != NULL && x->left->is_null == false)
                x = x->left;
            return x;
        }

        static Node* node_max(Node* x)
        {
            while (x->right != NULL && x->right->is_null == false)
                x = x->right;
            return x;
        }

        static const Node* node_max(const Node* x)
        {
            while (x->right != NULL && x->right->is_null == false)
                x = x->right;
            return x;
        }

	};

}




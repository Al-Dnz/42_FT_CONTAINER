#pragma once

#include "Vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack 
	{
		public:
			typedef T 								value_type;
			typedef Container 						container_type;
			typedef typename Container::size_type	size_type;
			typedef value_type& 					reference;
			typedef const value_type& 				const_reference;

		protected:
			Container c;

		public:
			explicit stack(const Container& cont = Container()):
				c(cont)
			{};

			stack(const stack& src): 
				c(src.c)
			{}

			stack& operator=(stack const & rhs)
			{
				if (this != &rhs)
					c = rhs.c;
				return (*this);
			}

			bool empty() const { return c.empty(); };
			const size_type size() const { return c.size(); };
			value_type& top() { return c.back(); };
			const value_type& top() const { return c.back(); };
			void push(const value_type& x) { c.push_back(x); };
			void pop() { c.pop_back(); };

			void swap (stack& x)
			{
				Container tmp = x.c;

				x.c = this->c;
				this->c = tmp;
			};


			friend bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return (x.c == y.c);
			};

			friend bool operator< (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return (x.c < y.c);
			};

			friend bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return (x.c != y.c);
			};

			friend bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return (x.c > y.c);
			};

			friend bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return (x.c >= y.c);
			};

			friend bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return (x.c <= y.c);
			};
		};

}
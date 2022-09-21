#pragma once

namespace ft
{
    template <typename T1, typename T2>
    class pair
    {
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			T1 first;
			T2 second;

			pair(void):
				first(T1()),
				second(T2())
			{};

			template <typename U, typename V>
			pair(pair<U, V> const &src):
				first(src.first),
				second(src.second)
			{};

			pair(first_type const &a, second_type const &b) : 
				first(a),
				second(b)
			{};

			pair &operator=(pair const &src)
			{
				if (this != &src)
				{
					first = src.first;
					second = src.second;
				}
				return (*(this));
			}

			
    };


	template <class A, class B>
	pair<A, B> make_pair (A x, B y)
	{
		return ( pair<A, B>(x, y) );
	};

    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }
    template <typename T1, typename T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (!(lhs == rhs));
    }
    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }
    template <typename T1, typename T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (!(rhs < lhs));
    }
    template <typename T1, typename T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (rhs < lhs);
    }
    template <typename T1, typename T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (!(lhs < rhs));
    }

}
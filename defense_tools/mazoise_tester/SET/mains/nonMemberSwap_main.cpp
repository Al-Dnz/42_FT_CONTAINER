/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonMemberSwap_main.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2022/07/14 09:41:21 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.hpp"
#include "SET_UC.HPP"
#include <set>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

template <class T>
void	print(set<T>& lst)
{
	for (typename set<T>::iterator it = lst.begin(); it != lst.end(); it++)
		cout << it->first << " => " << it->second << '\n';
}

int main ()
{
  int myints[]={12,75,10,32,20,25};
  set<int> first (myints,myints+3);     // 10,12,75
  set<int> second (myints+3,myints+6);  // 20,25,32

  NAMESPACE::swap(first,second);

  cout << "first contains:";
  for (set<int>::iterator it=first.begin(); it!=first.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  cout << "second contains:";
  for (set<int>::iterator it=second.begin(); it!=second.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  return 0;
}

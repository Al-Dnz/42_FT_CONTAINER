#include "test.hpp"
#include "../srcs/Pair.hpp"
#include "../srcs/RBT.hpp"
#include "../srcs/RBT_iterator.hpp"


typedef ft::pair<std::string, int>  pair_type;

void	RBT_test(void)
{
	display_fat_header("RBT TEST");

	ft::RBT<pair_type> tree;
	std::cout << "tree._size = "<< tree.size() <<std::endl;	
	pair_type p = ft::make_pair<std::string, int>("polo", 56);
	tree.insert(p);
	std::cout << "tree._size = "<< tree.size() <<std::endl;	

	p = ft::make_pair<std::string, int>("william", 12);
	tree.insert(p);
	std::cout << "tree._size = "<< tree.size() <<std::endl;
	p = ft::make_pair<std::string, int>("sylvain", 88);
	tree.insert(p);
	std::cout << "tree._size = "<< tree.size() <<std::endl;
	p = ft::make_pair<std::string, int>("zoe", 10);
	tree.insert(p);
	std::cout << "tree._size = "<< tree.size() <<std::endl;
	p = ft::make_pair<std::string, int>("manu", 35);
	tree.insert(p);
	std::cout << "tree._size = "<< tree.size() <<std::endl;
	p = ft::make_pair<std::string, int>("albert", 63);
	tree.insert(p);
	std::cout << "tree._size = "<< tree.size() <<std::endl;
	p = ft::make_pair<std::string, int>("jakeline", 192);
	tree.insert(p);
	std::cout << "tree._size = "<< tree.size() <<std::endl;

	
	std::cout << "tree min => "<< tree.rbt_min()->data << ", " << tree.rbt_min()->data->second <<  std::endl;
	std::cout << "tree max => "<< tree.rbt_max()->data << ", " << tree.rbt_max()->data->second <<  std::endl;
	
	std::cout << tree.size() <<std::endl;
	std::cout << tree.empty() <<std::endl;


	ft::RBT<pair_type>::iterator it;
	it = tree.begin();
	ft::RBT<pair_type>::iterator ite;
	ite = tree.find(p);
	for (; it != ite ; it++)
		std::cout << it->first << " => " << it->second << std::endl;

	display_header("REVERSE ITERATORS");

	ft::RBT<pair_type>::reverse_iterator r_it;
	r_it = tree.rbegin();
	
	ft::RBT<pair_type>::reverse_iterator r_ite;
	r_ite = tree.rend();
	for (; r_it != r_ite ; r_it++)
		std::cout << r_it->first << " => " << r_it->second << std::endl;

	display_header("COPY RBT");

	ft::RBT<pair_type> tree2 = tree;
	ft::RBT<pair_type>::iterator it2;
	it2 = tree2.begin();
	ft::RBT<pair_type>::iterator ite2;
	ite2 = tree2.end();
	for (; it2 != ite2 ; it2++)
		std::cout << it2->first << " -----> " << it2->second << std::endl;

	display_header("COMPARATORS");

	ft::RBT<pair_type> tree3;
	p = ft::make_pair<std::string, int>("chaton", 12);
	tree3.insert(p);
	p = ft::make_pair<std::string, int>("sfdfs", 88);
	tree3.insert(p);
	p = ft::make_pair<std::string, int>("panda", 10);
	tree3.insert(p);
	p = ft::make_pair<std::string, int>("ours", 35);
	tree3.insert(p);
	p = ft::make_pair<std::string, int>("rat", 63);
	tree3.insert(p);
	p = ft::make_pair<std::string, int>("coquelicot", 192);
	tree3.insert(p);

	std::cout <<"tree == tree => " << (tree == tree) <<std::endl;
	std::cout <<"tree == tree2 => " << (tree == tree2) <<std::endl;
	std::cout <<"tree == tree3 => " << (tree == tree3) <<std::endl;
	std::cout <<"tree < tree3 => " << (tree < tree3) <<std::endl;
	std::cout <<"tree > tree3 => " << (tree > tree3) <<std::endl;
}
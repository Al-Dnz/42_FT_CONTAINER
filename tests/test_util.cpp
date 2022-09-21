#pragma once
#include "test.hpp"

class Perso
{
	public:
		std::string _name;
		Perso():_name("anonymous") {};
		Perso(std::string name):_name(name) {};
		~Perso() {};
		Perso(Perso const & perso)
		{
			*this = perso;
		};
		Perso& operator=(Perso const & rhs)
		{
			if (this != &rhs)
				_name = rhs._name;
			return *this;
		};
};

std::ostream& operator<<(std::ostream& os , Perso const & perso)
{
	os << perso._name;
	return os;
}


void display_header(std::string str)
{
	int dimension = 50;
	int str_size = str.size();

	std::cout << std::endl;
	for (int i = 0; i < dimension; i++)
		std::cout << "-";
	std::cout << "\n";
	std::cout << "| ";
	std::cout << str;
	for (int i = 0; i < dimension - str_size - 3; i++)
		std::cout << " ";
	std::cout << "|" << "\n";
	for (int i = 0; i < dimension; i++)
		std::cout << "-";
	std::cout << std::endl;

}

void display_fat_header(std::string str)
{
	int dimension = 75;
	int str_size = str.size();

	std::cout << "\n";
	for (int i = 0; i < dimension; i++)
		std::cout << "=";
	std::cout << "\n";
	std::cout << "|| ";
	std::cout << str;
	for (int i = 0; i < dimension - str_size - 5; i++)
		std::cout << " ";
	std::cout << "||" << "\n";
	for (int i = 0; i < dimension; i++)
		std::cout << "=";
	std::cout << std::endl;
}
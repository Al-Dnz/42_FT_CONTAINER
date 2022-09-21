
#include "test.hpp"

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

typedef ft::pair<std::string, int>  pair_type;


void map_test(void)
{
        display_fat_header("MAP TEST");

		{	
			NAMESPACE::map<std::string, int> map;
			map["jacky"] = 53;
			map["polo"] = 76;
			map["abdoul"] = 32;
			map["wiliam"] = 12;
			map["sergrio"] = 65;

			display_header("MAP");
			NAMESPACE::map<std::string, int>::iterator it = map.begin();
			NAMESPACE::map<std::string, int>::iterator ite = map.end();
			for (; it != ite; ++it)
				std::cout << it->first << " => " << it->second << '\n';

			display_header("MAP2 (COPY CONSTRUCTOR)");
			NAMESPACE::map<std::string, int> map2(map);
			NAMESPACE::map<std::string, int>::iterator it2 = map2.begin();
			NAMESPACE::map<std::string, int>::iterator ite2 = map2.end();
			for (; it2 != ite2; ++it2)
				std::cout << it2->first << " => " << it2->second << '\n';

			display_header("MAP3 (OPERATOR =)");
			NAMESPACE::map<std::string, int> map3 = map;
			NAMESPACE::map<std::string, int>::iterator it3 = map3.begin();
			NAMESPACE::map<std::string, int>::iterator ite3 = map3.end();

			display_header("CLEAR");
			std::cout << "before clear" << std::endl;
			for (; it3 != ite3; ++it3)
				std::cout << it3->first << " => " << it3->second << '\n';
			map3.clear();
			std::cout << "after clear" << std::endl;
			for (; it3 != ite3; ++it3)
				std::cout << it3->first << " => " << it3->second << '\n';

		}

		display_header("OPERATOR []");
		{
			NAMESPACE::map<std::string, int> map;

			map["jacky"] = 53;
			map["polo"] = 76;
			map["abdoul"] = 32;
			map["wiliam"] = 12;
			map["sergio"] = 65;
			map["polo"] = 88;

			std::cout <<" map[\"polo\"] = "<< map["polo"]<< std::endl;
			std::cout <<" map[\"raimon\"] = "<< map["raimon"]<< std::endl;

			NAMESPACE::pair<std::string, int> p;
			p  = NAMESPACE::make_pair<std::string, int>("rachel", 57);
			map.insert(p);

			display_header("UNIQUE KEY");
			p  = NAMESPACE::make_pair<std::string, int>("polo", 7);
			map.insert(p);
			std::cout << "polo should appears once" << std::endl;
			
			for( NAMESPACE::map<std::string, int>::iterator it = map.begin(); it!=map.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
			
			display_header("ITERATORS");
			NAMESPACE::map<std::string, int>::iterator it;
			for(it= map.begin(); it!=map.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			display_header("REV_ITERATORS");
			NAMESPACE::map<std::string, int>::reverse_iterator rit;
			for(rit= map.rbegin(); rit!=map.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << '\n';

			display_header("COUNT");
			std::cout << "map.count(\"polo\") = " << map.count("polo")<< std::endl;
			std::cout << "map.count(\"anabelle\") = " << map.count("anabelle")<< std::endl;
			
			display_header("SIZE");
			std::cout << "map.size() = " << map.size()<< std::endl;

			display_header("SWAP");
			NAMESPACE::map<std::string, int> map_bis;
			map_bis["chien"] = 427;
			map_bis["chat"] = 109;
			map_bis["tortue"] = 2345;
			map_bis["zebre"] = 34;
			map_bis["poisson"] = 456;

			std::cout << "## before swap" << std::endl;
			std::cout << "map => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map.begin(); it!=map.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			std::cout << "\nmap_bis => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map_bis.begin(); it!=map_bis.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			map.swap(map_bis);
			std::cout << "\n\n## after swap" << std::endl;
			std::cout << "map => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map.begin(); it!=map.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			std::cout << "\nmap_bis => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map_bis.begin(); it!=map_bis.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			std::cout << std::endl;

			display_header("BOUND");
			std::string to_find = "chien";
			std::cout <<"map.lower_bound(" <<to_find << ") = " << (map.lower_bound(to_find))->first<< std::endl;
			std::cout <<"map.upper_bound(" << to_find << ") = " << (map.upper_bound(to_find))->first<< std::endl;

			to_find = "poisson";
			std::cout <<"map.lower_bound(" <<to_find << ") = " << (map.lower_bound(to_find))->first<< std::endl;
			std::cout <<"map.upper_bound(" << to_find << ") = " << (map.upper_bound(to_find))->first<< std::endl;

			to_find = "ragondin";
			std::cout <<"map.lower_bound(" <<to_find << ") = " << (map.lower_bound(to_find))->first<< std::endl;
			std::cout <<"map.upper_bound(" << to_find << ") = " << (map.upper_bound(to_find))->first<< std::endl;

			display_header("EQUAL_RANGE");
			to_find = "chien";
			NAMESPACE::pair<NAMESPACE::map<std::string,int>::iterator, NAMESPACE::map<std::string,int>::iterator > eq_r;
			
			eq_r = map.equal_range(to_find);
			NAMESPACE::map<std::string, int>::iterator ub = eq_r.first;
			NAMESPACE::map<std::string, int>::iterator lb = eq_r.second;
			std::cout <<"map.upper_bound("<< to_find <<") = [" << ub->first << ", "<< lb->first << "]" << std::endl;

			display_header("ERASE");
			std::cout << "deleting " << to_find << std::endl;
			map.erase(to_find);
			std::cout << "map => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map.begin(); it!=map.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			to_find = "poisson";
			std::cout << "\n\ndeleting " << to_find << std::endl;
			map.erase(map.find("poisson"));
			std::cout << "map => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map.begin(); it!=map.end(); ++it)
			std::cout << it->first << "(" << it->second << ") | ";

		}

		display_header("FIND");
		{
			NAMESPACE::map<char,int> mymap;
			NAMESPACE::map<char,int>::iterator it;

			mymap['a']=50;
			mymap['b']=100;
			mymap['c']=150;
			mymap['d']=200;

			it = mymap.find('d');
			if (it != mymap.end())
				mymap.erase (it);

		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';

		}		

		display_header("CONST MAP ITERATOR");
		{	
			NAMESPACE::map<std::string, int> map;
			map["jacky"] = 53;
			map["polo"] = 76;
			map["abdoul"] = 32;
			map["wiliam"] = 12;
			map["sergrio"] = 65;

			const NAMESPACE::map<std::string, int> mapy(map.begin(), map.end());

			for(NAMESPACE::map<std::string, int>::const_iterator it = mapy.begin(); it!= mapy.end(); it++)
				std::cout << it->first << "(" << it->second << ") | ";
		}

		display_header("COMPARATORS");
		{

			NAMESPACE::map<std::string, int> map;
			map["chien"] = 427;
			map["chat"] = 109;
			map["tortue"] = 2345;
			map["zebre"] = 34;
			map["poisson"] = 456;

			NAMESPACE::map<std::string, int> map_2 = map;

			NAMESPACE::map<std::string, int> map_3;
			map_3["jacky"] = 53;
			map_3["polo"] = 76;
			map_3["abdoul"] = 32;
			map_3["wiliam"] = 12;
			map_3["sergrio"] = 65;

			std::cout << "map   => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map.begin(); it!=map.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			std::cout << std::endl;
			std::cout << "map_2 => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map_2.begin(); it!=map_2.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			std::cout << std::endl;
			std::cout << "map_3 => ";
			for(NAMESPACE::map<std::string, int>::iterator it = map_3.begin(); it!=map_3.end(); ++it)
				std::cout << it->first << "(" << it->second << ") | ";
			std::cout << "\n" << std::endl;

			std::cout << "map == map_2 => "  << (map == map_2) << std::endl;
			std::cout << "map != map_2 => "  << (map != map_2) << std::endl;
			std::cout << "map > map_2 => "  << (map > map_2) << std::endl;
			std::cout << "map < map_2 => "  << (map < map_2) << std::endl;
			std::cout << "map >= map_2 => "  << (map >= map_2) << std::endl;
			std::cout << "map <= map_2 => "  << (map <= map_2) << std::endl;
			std::cout << std::endl;
			std::cout << "map == map_3 => "  << (map == map_3) << std::endl;
			std::cout << "map != map_3 => "  << (map != map_3) << std::endl;
			std::cout << "map > map_3 => "  << (map > map_3) << std::endl;
			std::cout << "map < map_3 => "  << (map < map_3) << std::endl;
			std::cout << "map >= map_3 => "  << (map >= map_3) << std::endl;
			std::cout << "map <= map_3 => "  << (map <= map_3) << std::endl;
			
		}	
}


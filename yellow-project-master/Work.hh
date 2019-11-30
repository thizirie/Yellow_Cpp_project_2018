#pragma once
#include <vector>
#include <string.h>
#include <map>	
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Artist.hh"
#include <random> 

class Work{
protected:
	std::string _title; 
	//Since we are just going to display these values, we can keep them in a string format
	std::string _length; 
	std::string _width; 
	std::string _date;
	std::string _in;
	int _id;
	std::vector<std::string> names;

public:
	virtual std::map<char,std::string> generateProp(std::string, const int alea ) = 0;
	virtual void lists_generator() = 0;
	friend std::ostream& operator<<(std::ostream& os, Work& p) ;
	std::string get_title(){return _title;};
};

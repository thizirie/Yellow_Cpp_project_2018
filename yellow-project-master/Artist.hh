#pragma once
#include <iostream> //
#include <vector>

class Artist{
private:
	int _id;
	std::string _name;
	std::string _century;
	std::string _movement;
	std::string _description;

	std::vector<std::string> _id_ls, _name_ls, _century_ls, _movement_ls,_description_ls, _portrait_ls;
public:
	Artist();
	Artist(const int id); //ID of the Artist we have to create
	~Artist();
	std::vector<std::string> getNames(){return _name_ls;};
	void lists_generator();
};

#include "Artist.hh"
#include "csvreader.h"

Artist::Artist(){
	lists_generator();
}

Artist::Artist(const int id){ //The id got from Paint._id

	lists_generator();
	_id=std::stoi(_id_ls[id]);
	_name = _name_ls[id];
	_century=_century_ls[id];
	_movement=_movement_ls[id];
	_century=_century_ls[id];
}

Artist::~Artist(){

}

//generates all the lists we will use for the propositions ..etc
void Artist::lists_generator(){

	CSVReader read("DB_Artists.csv");
	std::vector<std::vector<std::string>> dataLst;
	read.getData(dataLst);

	// Fill the lists
	for(std::vector<std::string> vect : dataLst)
	{
		_id_ls.push_back(vect[0]);
		_name_ls.push_back(vect[1]);
		_century_ls.push_back(vect[2]);
		_movement_ls.push_back(vect[3]);
		_description_ls.push_back(vect[4]);
		_portrait_ls.push_back(vect[5]);
	}
}

#pragma once
#include "deuxD.hh"


class Paint : public deuxD{ //Op

private:
	std::string _paint_type;

	//Lists that will be created/initialized in lists_generator
	std::vector<std::string> _title_ls, _artist_ls, _support_ls, _paintType_ls, _exposedIn_ls, _year_ls, _height_ls, _width_ls, _fig_ls;

public:
	// constructors
	Paint();
	Paint(const int rnd);

	//Destructor
	~Paint();

	//Generates the propositions to the user
	std::map<char,std::string> generateProp(std::string, const int rnd);
	
	//Saves the answer
	std::string enterRep();

	//Compares the correct answer to the player's answer and gives the result
	int generateSol(std::string rep,std::map<char,std::string> prop,std::string numQ, const int rnd);
	
	//Operator << overload
	friend std::ostream& operator<<(std::ostream& os, Paint& p);  
	
	//Generates the lists of all attributes from the .csv file
	void lists_generator(); 

	//get method
	int get_paintNbr() const{return _title_ls.size(); };

	//Displays the paintings on the screen 
	void print(const int rnd);
};

//for errors while loading a picture. Used in Paint::print 
int load(sf::Texture& texture,std::string tab);

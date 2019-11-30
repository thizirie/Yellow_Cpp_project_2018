#pragma once
#include "troisD.hh"

class Sculpture:public troisD{
protected:
	std::string _material;
	//Lists that will be created/initialized in lists_generator
	std::vector<std::string> _title_ls, _artist_ls, _material_ls, _fig_ls;
	
public:
	// constructors
	Sculpture();
	Sculpture(const int rnd);
	
	/* Destructor */
	~Sculpture(){}; 
	
	//Generates the propositions to the user
	std::map<char,std::string> generateProp(std::string, const int rnd);

	//Saves the answer
	std::string enterRep();

	//Compares the correct answer to the player's answer and gives the result
	int generateSol(std::string rep,std::map<char,std::string> prop,std::string numQ, const int rnd);

	//Operator << overload
	friend std::ostream& operator<<(std::ostream& os, Sculpture& p);  

	//Generates the lists of all attributes from the .csv file
	void lists_generator(); //creates all the lists of the different attributes of a Sculpture

	//get method
	int get_sculptNbr() const{return _title_ls.size(); };

	//Displays the sculpture's picture on the screen 
	void print(const int rnd);

};

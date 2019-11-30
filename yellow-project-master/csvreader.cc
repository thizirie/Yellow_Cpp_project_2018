#include "csvreader.h"

/*
Parses through csv file line by line and returns the data in vector of vector of strings */

void CSVReader::getData(std::vector<std::vector<std::string>>& dataList){

	std::ifstream file(_filename);
 
	//std::vector<std::vector<std::string>> dataList;

 	bool count = 0;	// used to skip the first line of the csv
 	
	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
	   	if (count)
	   	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(_delimeter));
		dataList.push_back(vec);     
		}
		if (count==0)
			count = 1;
	}
	// Close the File
	file.close();
 
	//return dataList;
}
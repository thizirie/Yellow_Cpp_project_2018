/* https://thispointer.com/how-to-read-data-from-a-csv-file-in-c/ */

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
 
class CSVReader
{
	std::string _filename;
	std::string _delimeter;
 
public:
	CSVReader(std::string filename, std::string delm = ",") :
			_filename(filename), _delimeter(delm)
	{ } //default deimiter : ","
 
	// Function to fetch data from a CSV File
	void getData(std::vector<std::vector<std::string>>& dataList);
};
 

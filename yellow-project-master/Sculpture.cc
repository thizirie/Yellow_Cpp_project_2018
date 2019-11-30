#include "Sculpture.hh"
#include "csvreader.h"
#include "Artist.hh"


// constructor just for an initialization
Sculpture::Sculpture(){
	lists_generator();
}

//Constructor for the right answer each time
Sculpture::Sculpture(const int rnd){
	lists_generator();
	_title=_title_ls[rnd];
	_material=_material_ls[rnd];

	int idA=std::stoi(_artist_ls[rnd]);//here, we link the id in Sculpture with the Id in Artist
	Artist A(idA);
	names = A.getNames();
	_id=idA;
}


// generate propositions to answer
std::map<char,std::string> Sculpture::generateProp(std::string numQ, const int rnd){
	int nbr_Sculptures=_title_ls.size(); 
	std::vector<std::string> choice;//This vector will give wich list ihas all the choices
	std::map<char,std::string> prop; //save the different choices shown to the player (5)
	
	char code;// Code of the question. for now, either A for Artist, T for Title or M for material used
	srand(time(NULL));
		
	//Question about a Sculpture's title
	if (numQ.compare(0,1,"T") == 0)	// look substring position 0, length 1 letter
	{	
		choice = _title_ls;
		code = 'T';
	}

	
	//Question about the Artist
	if (numQ.compare(0,1,"A") == 0){
		choice=_artist_ls;
		code= 'A';		
	}

	//Question about the material used
	if (numQ.compare(0,1,"M") == 0)
	{	
		choice = _material_ls; 
		code = 'M';
	}

	std::cout << "----- Choose A, B, C, D or E -----" << std::endl;
	int x = rand()%nbr_Sculptures; 
	if(x=rnd)
		++x;

	int div=x%nbr_Sculptures;
	prop.insert(std::pair<char,std::string> ('A',choice[div])); //0

	++x;
	div=x%nbr_Sculptures;
	prop.insert(std::pair<char,std::string> ('B',choice[div])); //1
	
	x+=4;
	div=x%nbr_Sculptures;
	prop.insert(std::pair<char,std::string> ('C',choice[div])); //2
	
	x+=3;
	div=x%nbr_Sculptures;
	prop.insert(std::pair<char,std::string> ('D',choice[div])); //3

	prop.insert(std::pair<char,std::string> ('E',"Anonyme/inconnu"));  //4


	//Making sure the correct answer is always displayed in the choices
	char i = char(rand()%4+65);	// i = A, B, C, or D
	
	//Sculpture title questions
	if (code == 'T'){
		std::map<char, std::string>::iterator it = prop.find(i); 
 		if (it != prop.end())
 			(*it).second = _title_ls[rnd];
		}

	//Material
	if (code == 'M'){
		prop[i] = _material_ls[rnd];
	}

	//Artist questions. We have to change here what's displayed, from just an id of the artist to her or his name
	if (code == 'A')
	{
		prop['A']=names[std::stoi(prop['A'])];
		prop['B']=names[std::stoi(prop['B'])];
		prop['C']=names[std::stoi(prop['C'])];
		prop['D']=names[std::stoi(prop['D'])];
		prop[i]=names[std::stoi(_artist_ls[rnd])];
	}

	//display the props
	for (std::map<char,std::string>::iterator iter = prop.begin(); iter != prop.end(); iter++)
	{
	    std::cout << iter->first << ". " << iter->second << std::endl;
	}
	std::cout << std::endl << std::endl;
		
	return prop;  	
}

//allows to give an answer and saves it
std::string Sculpture::enterRep()
{
	std::string rep;
	std::cout << "What is your answer ?" << std::endl;
	std::cin >> rep; 
	  
	while ((rep!="A")&&(rep!="B")&&(rep!="C")&&(rep!="D")&&(rep!="E")){
		std::cout << "I said ----- Choose A, B, C, D or E... -----" << std::endl;
	    std::cin >> rep;
	}
	  
	return rep;
}

// generates the solution, dealing with the three diffrent cases (Artist, Title, material questions)
int Sculpture::generateSol(std::string rep,std::map<char,std::string> prop,std::string numQ, const int rnd)
{
	char rep2=rep[0];
	if (numQ.compare(0,1,"T") == 0)
	{
	  	if (prop[rep2] == _title){
		std::cout << "YOU GOT IT, You genius! Carry on!" << std::endl;
		return 1; 
		}
	  	else{
		std::cout << "No, sorry ... actually it was: " << _title << std::endl;
		return 0; 
		}
	}

	if (numQ.compare(0,1,"M") == 0)
	{

	  	if (prop[rep2] == _material_ls[rnd])
		{ std::cout << "Wonderful! That's correct!" << std::endl;
		return 1; 
		}
	  	else
		{ 
			std::cout << "Too bad... This is actually made with: " << _material << std::endl;
			return 0; 
		}
	}
	

	if (numQ.compare(0,1,"A") == 0)
	{
		if (prop[rep2] == names[std::stoi(_artist_ls[rnd])]){

		std::cout << "You nailed it! We're so proud of you!" << std::endl;
		return 1; 
		}

	  	else{

		std::cout << "Shaaaame! Don't you know " << names[std::stoi(_artist_ls[rnd])] << "?" << std::endl;
		return 0; 
		}
	}

}

//Operator << overload
std::ostream& operator<<(std::ostream& os, Sculpture& p)
{
	os << "\n* * * " << "I am \"" << p._title << "\" modeled with " << p._material << " by " << p.names[p._id] << " * * *\n" << std::endl;
	return os;
}

//generates all the lists we will use for the propositions ..etc
void Sculpture::lists_generator(){
	CSVReader reader("DB_Sculptures.csv");
	std::vector<std::vector<std::string> > dataList;
	reader.getData(dataList);

	// Fill the lists
	for(std::vector<std::string> vect : dataList)
	{
		_title_ls.push_back(vect[0]);
		_artist_ls.push_back(vect[1]);
		_material_ls.push_back(vect[2]);
		_fig_ls.push_back(vect[3]);
	}
}


void Sculpture::print(const int rnd){ //displays the pictures
	// create window
	sf::RenderWindow window(sf::VideoMode(800, 600),"Tableau");

	while (window.isOpen())
	{
	// download texture from PNG file
	sf::Texture texture, texture2;
	texture.loadFromFile(_fig_ls[rnd]);
	texture2.loadFromFile("consigne.png");

	// enable the smooth filter
	texture.setSmooth(true);

	// Create the sprite and apply the texture
	sf::Sprite sprite, sprite2;
	sprite.setTexture(texture);	
	sprite2.setTexture(texture2);
	sprite2.scale(0.5f, 0.5f);
    
	sf::Event event;
	while (window.pollEvent(event))
	{
	// Close the window if a key is pressed or if requested
	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
		window.close();	
	}
	
	// Clear window and apply white background
	window.clear(sf::Color(255,255,255));

	// Draw the sprites
	if (texture.getSize().x> 450)
		sprite.setPosition(window.getSize().x/120, window.getSize().y/20);
	else
		sprite.setPosition(window.getSize().x/3.5, window.getSize().y/20);
	window.draw(sprite);
	sprite2.setPosition(window.getSize().x/3.3, window.getSize().y/1.3);
	window.draw(sprite2);        

	// Update display and wait for vsync
	window.display();
    }
}


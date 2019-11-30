#include "Paint.hh"
#include "csvreader.h"
#include "Artist.hh"

//This is a list with different types of paints. It has 12 elements. As much as the number of paintings we have in the .csv file. This is something we will have to deal with once we build a database with more paintings. We would create a link between this and the type of each painting and choose the other types in propositions here. Basically, ifs to implement in case of a question type "S"
std::vector<std::string> list_types = {"oil", "watercolor", "pastels", "pens", "gouache", "acrylic", "cerra-colla", "pastels", "colored inks", "wax paint", "tempera", "spray"};

// constructor just for an initialization
Paint::Paint(){
	lists_generator();
}

//Constructor for the right answer each time
Paint::Paint(const int rnd){

	lists_generator();

	_title=_title_ls[rnd];
	_length=_height_ls[rnd];
	_width=_width_ls[rnd];
	_date=_year_ls[rnd];
	_support=_support_ls[rnd];
	_in=_exposedIn_ls[rnd];
	_paint_type=_paintType_ls[rnd];

	int idA=std::stoi(_artist_ls[rnd]);	//here, we link the id in Paint with the Id in Artist
	Artist A(idA);
	names = A.getNames();
	_id = idA;
}

// destructor, empty since we are not dealing with pointers...
Paint::~Paint(){

}

// generate propositions to answer
std::map<char,std::string> Paint::generateProp(std::string numQ, const int rnd){
	
	int nbr_paints=_title_ls.size();
	std::vector<std::string> choice; //This vector will give wich list ihas all the choices
	std::map<char,std::string> prop; //save the different choices shown to the player (5)
	
	char code;// Code of the question. for now, either A for Artist, T for Title or S for painttype/support
	srand(time(NULL));
	
	//Question about a Painting's title
	if (numQ.compare(0,1,"T") == 0)	// look substring position 0, length 1 letter
	{	
		choice = _title_ls;
		code = 'T';
	}

	//Question about a painting's paint type/support
	if (numQ.compare(0,1,"S") == 0)
	{	
		choice = list_types; //If we put _support_types here you would have oil almost everytime	
		code = 'S';
	}

	//Question about the Artist who created a painting
	if (numQ.compare(0,1,"A") == 0)
	{
		choice=_artist_ls;
		code= 'A';		
	}


	std::cout << "----- Choose A, B, C, D or E -----" << std::endl;
	int x = rand()%nbr_paints; 
	if(x=rnd)
		++x;

	int div=x%nbr_paints;
	prop.insert(std::pair<char,std::string> ('A',choice[div])); //0

	++x;
	div=x%nbr_paints;
	prop.insert(std::pair<char,std::string> ('B',choice[div])); //1
	
	x+=4;
	div=x%nbr_paints;
	prop.insert(std::pair<char,std::string> ('C',choice[div])); //2
	
	x+=3;
	div=x%nbr_paints;
	prop.insert(std::pair<char,std::string> ('D',choice[div])); //3

	prop.insert(std::pair<char,std::string> ('E',"Unknown"));  //4

	
	//Making sure the correct answer is always displayed in the choices
	char i = char(rand()%4+65);	// i = A, B, C, or D
	
	//Painting title questions
	if (code == 'T'){
		std::map<char, std::string>::iterator it = prop.find(i); 
 		if (it != prop.end())
 			(*it).second = _title_ls[rnd];
		}

	//support type questions/Paint type
	if ((code == 'S') && (_paintType_ls[rnd]!="")){
		prop[i] = _paintType_ls[rnd];
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
std::string Paint::enterRep()
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

// generates the solution, dealing with the three diffrent cases (Artist, Title, paint type questions)
int Paint::generateSol(std::string rep,std::map<char,std::string> prop,std::string numQ, const int rnd)
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

	if (numQ.compare(0,1,"S") == 0)
	{

	  	if (prop[rep2] == _paintType_ls[rnd])
		{ std::cout << "Wonderful! That's correct!" << std::endl;
		return 1; 
		}
	  	else
		{ 
		//Making sure that if we don't know the paint_type, the player won't have -1 on his total score
			if (_paint_type == "")
				{ std::cout << "Admit you have choosen randomly! Actually we don't know either so... next." << std::endl;
				return 2; } 
			else
				{ std::cout << "Too bad... This is actually made with: " << _paint_type << std::endl;
				return 0; }
		}
	}

	if (numQ.compare(0,1,"A") == 0)
	{
		if (prop[rep2] == names[std::stoi(_artist_ls[rnd])])
		{ std::cout << "You nailed it! We're so proud of you!" << std::endl;
		return 1; 
		}
	  	else
		{ std::cout << "Shaaaame! Don't you know " << names[std::stoi(_artist_ls[rnd])] << "?" << std::endl;
		return 0; 
		}
	}

}


//Operator << overload
std::ostream& operator<<(std::ostream& os, Paint& p)
{
	os << "\n* * * " << "I am \"" << p._title << "\" painted with " << p._paint_type << " by " << p.names[p._id] << " in " << p._date << " * * *\n" << std::endl;
	return os;
}



//generates all the lists we will use for the propositions ..etc
void Paint::lists_generator(){
	CSVReader reader("DB_Paints.csv");
	std::vector<std::vector<std::string> > dataList;
	reader.getData(dataList);
	
	// Fill the lists
	for(std::vector<std::string> vect : dataList)
	{
		_title_ls.push_back(vect[0]);
		_artist_ls.push_back(vect[1]);
		_year_ls.push_back(vect[2]);
		_height_ls.push_back(vect[3]);
	   	_width_ls.push_back(vect[4]);
	   	_support_ls.push_back(vect[5]);
		_paintType_ls.push_back(vect[6]);	 
		_exposedIn_ls.push_back(vect[7]);	
		_fig_ls.push_back(vect[8]);
	}
}

//load verification
int load(sf::Texture& texture,std::string tab) //loads the pictures
{
    if (!texture.loadFromFile(tab))
    {
        std::cerr << "Error while loading texture" << std::endl;
        return -1;
    }
}

//displays a windows containing the Painting
void Paint::print(const int rnd){ //displays the pictures
	// create window
	sf::RenderWindow window(sf::VideoMode(800, 600),"Tableau");

	while (window.isOpen())
	{
	// download texture from PNG file
	sf::Texture texture, texture2;
	load(texture,_fig_ls[rnd]);
	load(texture2,"consigne.png");

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


#include <iostream>
#include <vector>
#include <string>
#include <random>	
#include <fstream>	//

#include "Paint.hh"
#include "Artist.hh"
#include "Player.hh"
#include "Sculpture.hh"
#include "Music.hpp"


//Declarations 
int paints_game();
int sculptures_game();
void all_games(int& score);


int main()
{

	/* MUSIC CHOICE */
	std::string n;
	std::cout << "Who's your favorite? 1, 2 or 3?" << std::endl;
	std::cout << "1. The Beatles;" << std::endl << "2. Coldplay;"<< std::endl << "3. Wiz Khalifa." << std::endl;	
	std::cin >> n ;


	//Plays the theme song according to the player's choice
	sf::Music music;

	if (n=="2")
	{
		music.openFromFile("Yellow.flac");
	}
	else if (n=="3")
	{
		music.openFromFile("Black and Yellow.flac");
	}
	else
	{
		music.openFromFile("Yellow Submarine.flac");
	}
	
	music.play();



	//The game begins
	std::cout<<"----- Now let's start! You have 5 points! -----"<<std::endl << "Try to win more points and challenge yourself. Good luck, mate!"<< std::endl;
	int score;
	

	//In this case, we have 0.8 chances to call paints_game and 0.2 to call sculptures_games. Once the .csv files have enough artworks in both paints and sculptures, we can replace %5 by %2 and 4 by 1 or 0 in the function defined below 
  	all_games(score); 


  	// END OF THE GAME
	if (score>0)
		std::cout<< "Congrats! You're a winner! Did you get 15 points? No? You should play one more time anyway!"<<std::endl;

	
	return 0;
}







/* FUNCTIONS */









int paints_game(){

	/* INITIALIZING VARIABLES */
	srand(time(NULL));
	std::string rep;
	std::map<char,std::string> prop;
	std::string question;


	/* POSSIBLE QUESTIONS */
	std::string Q1="T/ What is my name?";
	std::string Q2="S/ Which paint type did my creator use to create me?";
	std::string Q3="A/ Who's the genius who created me?";
	
	/* Construction */
	Paint p1;
	int paints_nbr=p1.get_paintNbr();


	/* PLAYER'S PART */
	Player joueur;
	int point;
	int x;
	std::string next;

	/* QUESTIONS */
	// Chooses a question randomly	
	
		int rnd=rand()%paints_nbr; //Chooses a random artwork in the .csv
		Paint p(rnd); //Creation of the object located in the rnd-th position of the lists generated (or rnd+1'th line in the .csv file)

		x = rand()%3;	//Question to ask from the 3 (Q1, Q2, Q3) above
		if (x==0)
		{	
			question=Q1;
			std::cout << std::endl << Q1 << std::endl;
			p.print(rnd);
		}
		if (x==1)
		{	
			question=Q2;
			std::cout << std::endl << Q2 << std::endl;
			p.print(rnd);
		}
		if (x==2)
		{	
			question=Q3;
			std::cout << std::endl << Q3 << std::endl;
			p.print(rnd);
		}
		std::cout << std::endl;


		/* DISPLAYS THE CHOICES, SAVES THE PLAYER'S ANSWER AND GIVES THE RIGHT ONE */ 
		prop = p.generateProp(question,rnd);
		rep = p.enterRep();
		point = p.generateSol(rep,prop,question,rnd);
		std::cout << p;



		/* UPDATES THE PLAYER'S SCORE */
		joueur.update(point);
		
		/* TO CONTINUE */ 
		std::cout << "----- Press any letter + \"enter\" to move on the next question -----" << std::endl;
		std::cin >> next;


	/* END OF THE GAME */
	return joueur.get();//returns the score

}



int sculptures_game(){

	/* INITIALIZING VARIABLES */
	srand(time(NULL));
	std::string rep;
	std::map<char,std::string> prop;
	std::string question;


	/* POSSIBLE QUESTIONS */
	std::string Q1="T/ What is my name?";
	std::string Q2="M/ Do you know what I'm made of?";
	std::string Q3="A/ Who's the genius who created me?";
	
	/* CONSTRUCTION */
	Sculpture s1;
	int sculpt_nbr=s1.get_sculptNbr();

	/* PLAYER'S PART */
	Player joueur;
	int point;
	int x;
	std::string next;

	/* QUESTIONS */
	// Chooses a question randomly	
	
		int rnd=rand()%sculpt_nbr; //Chooses a random artwork in the .csv of sculptures
		Sculpture s (rnd); //Creation of the object located in the rnd-th position of the lists generated (or rnd+1'th line in the .csv file)
	
		x = rand()%3;	//Question to ask from the 3 (Q1, Q2, Q3) above
		if (x==0)
		{	
			question=Q1;
			std::cout << std::endl << Q1 << std::endl;
			s.print(rnd);
		}
		if (x==1)
		{	
			question=Q2;
			std::cout << std::endl << Q2 << std::endl;
			s.print(rnd);			
		}
		if (x==2)
		{	
			question=Q3;
			std::cout << std::endl << Q3 << std::endl;
			s.print(rnd);
		}

		std::cout << std::endl;

		/* DISPLAYS THE CHOICES, SAVES THE PLAYER'S ANSWER AND GIVES THE RIGHT ONE */ 
		prop = s.generateProp(question,rnd);
		rep = s.enterRep();
		point = s.generateSol(rep,prop,question,rnd);
		std::cout << s << std::endl;

		
		/* UPDATES THE PLAYER'S SCORE */
		joueur.update(point);
		
		/* TO CONTINUE */ 
		std::cout << "----- Press any letter + \"enter\" to move on the next question -----" << std::endl;
		std::cin >> next;
	

	/* END OF THE GAME */
	return joueur.get();//returns the score

	
}

void all_games(int& score){
	srand(time(NULL));
	int rnd_var = rand()%3;

	
	for (int i=0;i<10;i++) //10 questions asked if the player has more than 0 points each round
	{
		if (rnd_var==2)
		{
			score=sculptures_game();		
		}
		else
			score=paints_game();

		
		/* IF PLAYER LOSES */
		if (score==0){
			std::cout<<"Game over... - Keep trying, \" Those who dare to fail miserably can achieve greatly \". Don't stop champion! Arts are waiting for you."<<std::endl;
			break; 
		}
	}

}

/// THE END.
#include "Player.hh"

void Player::update(int res){
	if (_pt>0)	
	{
		std::cout<<"==============="<<std::endl;

		if (res==0) 
		{	
			_pt--;
			std::cout<<"-1, score : "<<_pt<<std::endl; 
		} 
		else if (res==2) 
		{	
			std::cout<<"Same score : " <<_pt<<std::endl; 
		}
		else
		{
			_pt++;
			std::cout<<"+1, score : " <<_pt<<std::endl; 			
		}
		std::cout<<"==============="<<std::endl; 
	}
}

int Player::get(){
	return _pt;
}

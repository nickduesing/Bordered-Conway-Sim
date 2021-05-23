#include <array>

#include "Cell.h"

using namespace std;
/*Cell::Cell(){
	pos = {0,0};
	age = 0;
	state = 'e';
}*/

Cell::Cell(int xPos, int yPos, int cellAge, char cellState){
	pos = {xPos, yPos};
	age = cellAge;
	state = cellState;
}

Cell::Cell(const Cell& c){	
	pos = c.pos;
	age = c.age;
	state = c.state;
}

Cell& Cell::operator= (const Cell& c){
	if (this != &c){
		pos = c.pos;
		age = c.age;		
		state = c.state;
	}
	return *this;
}

void Cell::cellBirth(int cellAge){
	setState('b');
	age = cellAge + 1;
	if (age > 100) age = 100;
}

void Cell::cellDeath(){
	setState('c');
}

void Cell::fixState(){
	switch (this -> state){
		case 'b':{
			setState('a');
			break;
		}
		case 'c':{
			setState('d');
			age = 0;
			break;
		}
		case 'd':{
			setState('e');
			break;
		}
	}	
}

array<int, 2> Cell::getPos(){
	return pos;
}

int Cell::getAge(){ 
	return age;
}

char Cell::getState(){
	return state;
}

void Cell::setState(char newState){
	state = newState;
}

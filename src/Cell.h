#ifndef CELL_H
#define CELL_H

#include <array>

class Cell {
	public:
		//Cell();
		Cell(int = 0, int = 0, int = 0, char = 'e');
		Cell(const Cell&);
		
		Cell& operator= (const Cell&);
		
		void cellBirth(int);
		void cellDeath();
		void fixState();
				
		std::array<int, 2> getPos();
		char getState();
		int getAge();
		
		void setState(char);
				
	private:
		std::array<int, 2> pos;
		int age;
		char state;
	
};

#endif

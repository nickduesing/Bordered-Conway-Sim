#ifndef GAME_H
#define GAME_H

#include <array>
#include <vector>

#include "Cell.h"

class Game {
	public:
		Game(bool = false, int = 25);
		
		void addCell(int, int);
		void addLines(int, int, int, int);
				
		void removeCell(int, int);
				
		void startGame(bool, int);
		
		int stepGame();
		
		void displayFrame(int = 0);
		
		void getNeighborhood(std::array<int, 2>);
		int countNeighbors();
		int neighborAge();
		
		int getSize();
		bool getRules();
		char getCellState(int, int);
	private:
		int size;
		int middle;
		bool rules;
		std::vector<std::vector<Cell>> cellField;
		std::array<std::array<Cell, 3>, 3> neighborhood;
		
		
	
};

#endif

#include <iostream>
#include <string>

#include <array>
#include <vector>

#include <chrono>
#include <ratio>

#include "Game.h"
#include "Cell.h"

using namespace std;
using namespace std::chrono;

Game::Game(bool applyRules, int gameSize){
	rules = applyRules;
	size = (gameSize > 100) ? 100 : gameSize;
	middle = size / 2;
	
	cellField.resize(size);
	for (int i{0}; i < size; i+=1){
		cellField[i].resize(size);
		for (int j{0}; j < size; j+=1){
			cellField[i][j] = Cell(j, i);
		}
	}
}

void Game::addCell(int x, int y){
	cellField[y][x].setState('a');
}

void Game::addLines(int x1, int y1, int x2, int y2){
	for (int i{x1}; i <= x2; i += 1){
		for (int j{y1}; j <= y2; j += 1){
			addCell(i, j);
		}
	}
}

void Game::removeCell(int x, int y){
	cellField[y][x].setState('e');
}

void Game::startGame(bool showFrames, int cycles){
	bool vis{showFrames}, time{false};
	int loop{0}, final{0};
	typedef duration<int, milli> ms_type;
	
	if (vis) displayFrame();
	
	while (loop < cycles && final == 0){
		time_point<steady_clock, ms_type> t1;
		if (vis) t1 = time_point_cast<ms_type>(steady_clock::now());
		
		final = stepGame();
		
		++loop;
		
		if (vis){
			displayFrame();
			while (!time){
				time = 333 < duration_cast<ms_type>(time_point_cast<ms_type>(steady_clock::now()) - t1).count();
			}
			time = false;
		} 
	}
	displayFrame(final);
}

int Game::stepGame(){
	for (vector<Cell>& v : cellField){
		for (Cell& c : v){
			getNeighborhood(c.getPos());
			int census = countNeighbors();
			char state = c.getState();
			
			switch (census){
				case 3:
					if (state == 'd' || state == 'e') c.cellBirth(neighborAge());
				case 2:
					break;
				default:
					if (state == 'a') c.cellDeath();
			}
		}
	}
	
	for (vector<Cell>& v : cellField){
		for (Cell& c : v){
			c.fixState();
		}
	}
	if (!rules) return 0;
	getNeighborhood({middle, middle});
	return (neighborAge() == 0) ? 0 : neighborAge() * countNeighbors();
}

void Game::displayFrame(int score){
	cout << string(10, '\n');
	char temp{};
	
	for (vector<Cell>& v : cellField){
		for (Cell& c : v){
			switch (c.getState()){
				case 'a': {
					temp = 'O';
					break;
				}
				case 'd': {
					temp = '+';
					break;
				}
				default:
					temp = '-';
			}
			cout << temp;
		}
		cout << endl;
	}
	if (score != 0){
		cout << "\nFinal score is: " << score << endl;
	}
	
}

void Game::getNeighborhood(array<int, 2> pos){
	int xPos{pos[0]}, yPos{pos[1]};
	
	for (int j{0}; j < 3; j += 1){
		int y = yPos + j - 1;
		if (y < 0 || y >= size){
			neighborhood[j].fill(Cell());
			continue;
		}
		for (int i{0}; i < 3; i += 1){
			int x = xPos + i - 1;
			if (x < 0 || x >= size || (i == 1 && j == 1)){
				neighborhood[j][i] = Cell();	
			} else {
				neighborhood[j][i] = cellField[y][x];
			}
		}
	}
}

int Game::countNeighbors(){
	int count{0};
	
	for (array<Cell, 3>& a : neighborhood){
		for (Cell& c : a){
			char neighbor = c.getState();
			if (neighbor == 'a' || neighbor == 'c') ++count;
		}
	}
		
	return count;
}

int Game::neighborAge(){
	int hoodAge{0};
	
	for (array<Cell, 3>& a : neighborhood){
		for (Cell& c : a){
			hoodAge = (hoodAge > c.getAge()) ? hoodAge : c.getAge();
		}
	}	
	
	return hoodAge;
} 

int Game::getSize(){
	return size;
}

bool Game::getRules(){
	return rules;
}

char Game::getCellState(int x, int y){
	return cellField[y][x].getState();
}

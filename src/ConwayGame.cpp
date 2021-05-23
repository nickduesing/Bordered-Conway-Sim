#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Game.h"
#include "Cell.h"

using namespace std;

int main(){
	int x{0}, y{0}, num{0}, choice{0};
	bool bolan{false};
	string file{}, tempStr{};
	Game game;
	
	while (choice != 6){
		cout << "1) Make a new game" << "\n2) Add cells to board" << "\n3) Remove cells from board";
		cout << "\n4) Display/save current board" << "\n5) Start game" << "\n6) Exit" << "\n\nChoice: ";
		cin >> choice;
		
		switch (choice){
			case 1: {
				cout << "\n1 for standard\n2 for special\n3 for custom\n4 to import\n5 to exit\n: ";
				cin >> num;
				switch (num){
					case 1: {
						game = Game(false);
						break;
					}
					case 2:{
						game = Game(true);
						break;
					}
					case 3: {
						cout << "Special ruleset? (1=y/0=n)\n: ";
						cin >> bolan;
						cout << "Enter size: ";
						cin >> x;
						game = Game(bolan, x);
						break;
					}
					case 4: {
						string line{};
						cout << "Enter existing image import file or 0 to exit\n: ";
						cin >> file;
						if (file == "0") break;
						
						ifstream gameFile{file};
															
						if (!gameFile){
							cout << "\nImport Failed\n";
							break;							
						}
						getline(gameFile, tempStr);
						bolan = atoi(tempStr.c_str());
						getline(gameFile, line);
						cout << bolan << "\n";
						int numb = (line.length() > 100) ? 100 : line.length();	
					
						game = Game(bolan, numb);
						for (int j{0}; j < game.getSize(); j += 1){
							cout << line << " // // " << j << endl;
							for (int i{0}; i < line.length(); i += 1){
								if (line.at(i) == '0') game.addCell(i, j);
							}	
							getline(gameFile, line);
						}
						gameFile.close();
						cout << "\nFile Imported\n";
						break;
					}
					default:{
						break;
					}
						
				}
				break;
			}
			case 2: {
				cout << "1 to enter individual cells\n2 to enter areas of cells\n3 to enter an external list\n4 to return to menu\n: ";
				cin >> num;
				
				switch (num){
					case 1: {
						cout << "Enter the position in \"x y\" form" << "\nwith \"0 0\" being the top-left corner";
						cout << "\nand \""<< game.getSize() - 1 << " " << game.getSize() - 1 << "\" being the bottom-right.";
						cout << "\nEnter a negative value to return to menu." << endl;
						
						while (true){
							cout << "Add: ";
							cin >> x >> y;
						
							if (x < 0 || y < 0) break;
					
							game.addCell(x,y);					
						}
						break;
					}
					case 2: {
						int xt{0}, yt{0};
						cout << "Enter the position in \"x y\" form" << "\nwith \"0 0\" being the top-left corner";
						cout << "\nand \""<< game.getSize() - 1 << " " << game.getSize() - 1 << "\" being the bottom-right.";
						cout << "\nEnter a negative value to return to menu." << endl;
					
						while (true){
							cout << "First point: ";
							cin >> x >> y;
							
							if (x < 0 || y < 0) break;
					
							cout << "Second point: ";
							cin >> xt >> yt;
				
							if (xt < 0 || yt < 0) break;
												
							game.addLines(x, y, xt, yt);					
						}
						break;
					}
					case 3: {
						char type[3];
					
						cout << "Enter exact file name or enter 0 to return to menu: ";
						cin >> file;
		
						if (file == "0") break;
		
						ifstream cellFile{file};
		
						if (!cellFile){
							cout << "\nImport Failed\n";
							break;
						}
						
						cellFile >> type;
						while (type[0] != 'e'){
							switch (type[0]){
								case 'c': {
									cellFile >> x >> y;
									game.addCell(x, y);
									break;
								}
								case 'l': {
									int xa{0}, ya{0};
									cellFile >> x >> y >> xa >> ya;
									game.addLines(x, y, xa, ya);
									break;
								}
								default:
									if (type[0] == 'e') break;
									x = atoi(type);
									cellFile >> y;
									game.addCell(x, y);
							}
							if (type[0] == 'e') break;	
							cellFile >> type;				
						}
						
						cellFile.close();
						cout << "\nFile imported\n";
						break;
					}
				}
				
				
				break;
			}
			case 3: {
				cout << "Enter the position in \"x y\" form" << "\nwith \"0 0\" being the top-left corner";
				cout << "\nand \""<< game.getSize() - 1 << " " << game.getSize() - 1 << "\" being the bottom-right.";
				cout << "\nEnter a negative value to return to menu." << endl;
				
				while (true){
					cout << "Remove: ";
					cin >> x >> y;
						
					if (x < 0 || y < 0) break;
											
					game.removeCell(x,y);					
				}
						
				break;
			}
			case 4: {
				cout << "\n1 to display current board" << "\n2 to save current board to a .txt" << "\n3 to return to menu\n: ";
				cin >> num;
				switch (num){
					case 1:{
						game.displayFrame(0);
						break;
					}
					case 2:{
						cout << "Enter the document name or type 0 to exit to menu: ";
						cin >> file;
						if (file == "0") break;
						
						ofstream gameFile{file += ".txt"};
						
						if (!gameFile){
							cout << "\nFailed to open file.\n";
							break;
						}
						
						gameFile << game.getRules() << "\n";
						
						for (int i{0}; i < game.getSize(); i += 1){
							for (int j{0}; j < game.getSize(); j += 1){
								if (game.getCellState(i, j) == 'a'){
									gameFile << '0';
								} else {
									gameFile << '-';
								}
							}
							gameFile << '\n';
						}
						gameFile << '\n';
						
						gameFile.close();
						cout << "\nBoard Exported\n";
						break;
					}
				}
				break;
			}
			case 5: {
				cout << "Enter maximum number of cycles" << "\nor enter 0 to return to menu." << "\nCycles: ";
				cin >> num;
				
				if (num == 0) break;
							
				cout << "Show game frames? (1=y/0=n): ";
				cin >> bolan;
				
				game.startGame(bolan, num);
				
				break;
			}
			case 6:
				break;
			default:
				choice = 0;
		}
		cout << "\n";
	}
}

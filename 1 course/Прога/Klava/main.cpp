#include <iostream>
#include "klava.h"
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <windows.h>

void mainLoop (clock_t delay);

int main() {
	srand (time (NULL) + rand ());
	const int size = 7;
	int difficulty;
	float seconds;
	
	system ("color 3");
	SetConsoleCP (1251);
	SetConsoleOutputCP (1251);
	
	std::cout << "\t\tDifficulty:\n";
	std::cout << "1 -> Very easy;\n";
	std::cout << "2 -> Hard;\n";
	std::cout << "3 -> Impossible;\n";
	std::cout << "... ";

	std::cin >> difficulty;
	
	switch (difficulty) {
		case 1:
			seconds = 7;
			break;
			
		case 2:
			seconds = 6;
			break;
			
		case 3:
			seconds = 4;
			break;
			
		default:
			std::cout << "\nERROR! Invalid value!";
			exit (1);
	}
	
	std::cout << "Press \"space\" to clear screen";
	getch();	
	system ("cls");
	clock_t delay = seconds * CLOCKS_PER_SEC;
	mainLoop (delay);
	
	return 0;
}

void mainLoop (clock_t delay) {	
	srand (time (NULL) + rand ());
	clock_t start = clock();
	const int buff = 100;
	int count = 0;
	
    std::string words [buff];
	std::ifstream myWords ("words.txt");
	
	for (; count < buff; count++) {
		myWords >> words [count];
		if (myWords.eof())
			break;
	}
		
	KEYS curKey = NOKEY;
	
	std::string curString = words [0 + rand () % count];
	std::string enteredString;
	
	while (clock() - start < delay ) {
		system ("cls");
		std::cout << "TIME: " << clock() << "\n";
		std::cout << "-> " << curString;
	    curKey = keyPressed ();
		
		switch (curKey) {
			case a:
				enteredString += "a";
				break;
				
			case b:
				enteredString += "b";
				break;
				
			case c:
				enteredString += "c";
				break;
				
			case d:
				enteredString += "d";
				break;
				
			case e:
				enteredString += "e";
				break;
				
			case f:
				enteredString += "f";
				break;
				
			case g:
				enteredString += "g";
				break;
				
			case h:
				enteredString += "h";
				break;
				
			case i:
				enteredString += "i";
				break;
				
			case j:
				enteredString += "j";
				break;
				
			case k:
				enteredString += "k";
				break;
				
			case l:
				enteredString += "l";
				break;
			
			case m:
				enteredString += "m";
				break;
				
			case n:
				enteredString += "n";
				break;
				
			case o:
				enteredString += "o";
				break;
				
			case p:
				enteredString += "p";
				break;
				
			case q:
				enteredString += "q";
				break;
				
			case r:
				enteredString += "r";
				break;
				
			case s:
				enteredString += "s";
				break;
				
			case t:
				enteredString += "t";
				break;
				
			case u:
				enteredString += "u";
				break;
			
			case v:
				enteredString += "v";
				break;	
				
			case w:
				enteredString += "w";
				break;
				
			case x:
				enteredString += "x";
				break;
				
			case y:
				enteredString += "y";
				break;
				
			case z:
				enteredString += "z";
				break;
				
			default:
					if (curKey == space) {
						std::string source = "";
						enteredString = source;
					}
					curKey = NOKEY;
				break;
		}
		
		std::cout << "\n... " << enteredString;
		Sleep (100);
		 
		if (curString.size() == enteredString.size()) {
				if (curString  != enteredString ) {
					Beep (160, 220);
					std::cout << "\nFAIL!";
					system ("PAUSE >> NULL");
					exit (1);
				}
				else {
					Beep (500, 100);
					std::cout << "\nGOOD!";
					mainLoop (delay);
				}
		}
    }
    
    system ("cls");
    Beep (160, 220);
    std::cout << "Time is out :(";
    system ("PAUSE >> NULL");
}

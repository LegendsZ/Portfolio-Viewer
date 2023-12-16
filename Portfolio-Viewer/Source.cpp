#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include "Portfolio.h"

//put version in port bin file to check compatability?
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)
#define VERSION_STRING STRINGIFY(VERSION_MAJOR) "." STRINGIFY(VERSION_MINOR) "." STRINGIFY(VERSION_PATCH)


void printMenu();
void viewPositions();
void addNewPosition();
void addToPosition();
void removePosition();
void removeFromPosition();
void saveAndExit();
void exitWithoutSave();

HANDLE hConsole;
typedef void(*funcPtr)(void);
funcPtr functions[7] = {&viewPositions,&addNewPosition,&addToPosition,&removePosition,&removeFromPosition, &saveAndExit, &exitWithoutSave };
Portfolio* portfolio = new Portfolio();
std::string defaultFileToRead = "portfolio.bin";
std::string fileToRead = defaultFileToRead;
bool createNew = false;

int main() {
	system("title PORTFOLIO-VIEWER");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*for (int k = 1; k < 255; k++)
	{
		SetConsoleTextAttribute(hConsole, k);
		std::cout << k << " I want to be nice today!" << std::endl;
	}
	system("pause");*/
	SetConsoleTextAttribute(hConsole, 15);
	
	while (true) {
		system("cls");
		std::cout << "Welcome to PORTFOLIO-VIEWER V" << VERSION_STRING << "\n";
		std::cout << "Read portfolio from (default: '" << fileToRead << "'): ";
		std::string input;
		std::getline(std::cin, input);
		if (input.length() != 0) {
			fileToRead = input;
		}
		std::ifstream file;
		file.open(fileToRead);
		bool exists = file ? true : false;
		file.close();
		if (!exists) {
			while (true) {
				system("cls");
				std::cout << "Portfolio file '" << fileToRead << "'does not exist\nWould you like to try again or create a new profile ('1' / '2'): ";
				fileToRead = defaultFileToRead;
				std::getline(std::cin, input);
				if (input == "1" || input == "2") {
					break;
				}
			}
			if (input == "2") {
				createNew = true;
				break;
			}
		}
		else {
			break;
		}
	}

	std::cout << "Loading...";
	if (!createNew) {
		portfolio->Read(fileToRead);
	}
	std::cout << "DONE!\n";
	system("cls");
	while (true) {
		system("cls");
		printMenu();
		std::cout << ">";
		int keyIn = (int)(std::cin.get());
		if (keyIn >= 49 && keyIn <= 55) { // add decrease range for menu mods
			functions[keyIn - 49]();
		}
	}
	system("pause");
	return 0;
}

void printMenu() {
	const int borderwidth = 37;
	for (int i = 0; i < borderwidth/2 - 2; ++i) {
		std::cout << "=";
	}
	std::cout << "MENU";
	for (int i = 0; i < borderwidth / 2 - 1; ++i) { //-1 or -2 if width is odd/even respective
		std::cout << "=";
	}
	std::cout << "\n";

	std::cout << "1 -> View current positions/portfolio\n";
	std::cout << "2 -> Add new position\n";
	std::cout << "3 -> Add to position\n";
	std::cout << "4 -> Remove position\n";
	std::cout << "5 -> Remove from position\n";
	std::cout << "6 -> Save & Exit\n";
	std::cout << "7 -> Exit\n";

	for (int i = 0; i < borderwidth; ++i) {
		std::cout << "=";
	}
	std::cout << "\n";
}

void viewPositions() {
	system("cls");
	portfolio->printPositions(hConsole);
	system("pause");
}
void addNewPosition() {
	Position* pos = new Position();
	std::string input;
	
	std::cout << "Token name: ";
	std::cin.ignore();
	std::getline(std::cin, input);
	pos->tokenName = input;

	std::cout << "Token count: ";
	std::getline(std::cin, input);
	try {
		pos->tokenCount = std::stof(input);
	}
	catch (std::exception e) {
		std::cout << "Invalid input!\n";
		system("pause");
		return;
	}

	std::cout << "Invested amount: ";
	std::getline(std::cin, input);
	try {
		pos->investedAmount = std::stof(input);
	}
	catch (std::exception e) {
		std::cout << "Invalid input!\n";
		system("pause");
		return;
	}

	pos->averageBuyIn = pos->investedAmount / (pos->tokenCount);
	pos->currentValuation = NULL; //implement after

	std::cout << "Set colour (range: 1 to 15 inclusive, default: 15): ";
	std::getline(std::cin, input);
	int colourID;
	try {
		colourID = std::stoi(input);
	}
	catch (std::exception e) {
		std::cout << "Invalid input!\n";
		system("pause");
		return;
	}
	pos->colour = colourID >= 1 && colourID <= 15 ? colourID : 15;
	portfolio->addPosition(pos);
	std::cout << "Added position!\n";
	system("pause");
}
void addToPosition() {
	system("pause");
}
void removePosition() {
	std::string input;
	int indexToRemove;

	std::cout << "Index to remove: ";
	std::cin.ignore();
	std::getline(std::cin, input);
	try {
		indexToRemove = std::stoi(input);
	}
	catch (std::exception e) {
		std::cout << "Invalid input!\n";
		system("pause");
		return;
	}

	if (indexToRemove >= 0 && indexToRemove < portfolio->positionCount) {
		portfolio->removePosition(indexToRemove);
	}
	std::cout << "Removed position!\n";
	system("pause");
}
void removeFromPosition() {
	system("pause");
}

void saveAndExit() {
	system("cls");
	if (createNew) {
		std::cout << "Path to write to (default: '" << fileToRead << "'): ";
		std::string input;
		std::getline(std::cin, input);
		if (input.size() != 0) {
			fileToRead = input;
		}
	}
	portfolio->Write(fileToRead);
	exit(0);
}

void exitWithoutSave() {
	exit(0);
}
#pragma once
#include <Windows.h> //printings
#include <string>
 //need version compatability... for position -> portfolio
class Position {
public:
	std::string tokenName; //change to char* and length name var
	int colour;
	float tokenCount;
	double investedAmount;
	double averageBuyIn;
	double currentValuation;

	void print(HANDLE hConsole) {
		SetConsoleTextAttribute(hConsole, colour);
		std::cout << "Token name: $" << tokenName <<
			"\n" << "Token count: " << tokenCount <<
			"\n" << "Invested amount: " << investedAmount <<
			"\n" << "Average buy in: " << averageBuyIn <<
			"\n" << "Current valuatiaon: " << currentValuation << "\n";
	}
};
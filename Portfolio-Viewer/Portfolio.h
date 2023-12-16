#pragma once
#include <vector>
#include "Position.h"
#include "Serializer.h"

class Portfolio : Serializer{ //singleton?
public:
	int positionCount;
	std::vector<Position*> positions;
	//add future string for location on local machine?
	//add name/identifier?

	Portfolio() : positions(std::vector<Position*>()), positionCount(0) {
	}

	void Read(std::string name) {
		dataChunks.clear();
		dataChunks.push_back({ &positionCount,sizeof(int) });
		DeserializeWithIntegerCount(name, sizeof(Position));
		if (positionCount != 0) {
			for (int i = 1; i < dataChunks.size(); ++i) {
				positions.push_back((Position*)dataChunks[i].data);
			}
		}
	}

	void Write(std::string name) {
		dataChunks.clear();
		dataChunks.push_back({ &positionCount, sizeof(int) });
		for (int i = 0; i < positionCount;++i) {
			dataChunks.push_back({ &positions[i], sizeof(Position)});
		}
		Serialize(name);
	}

	void printPositions(HANDLE hConsole) {
		int index = 0;
		for (Position* position : positions) {
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "Index: " << index << "\n";
			position->print(hConsole);
			std::cout << "\n";
		}
		SetConsoleTextAttribute(hConsole, 15);
	}

	void addPosition(Position* pos) {
		positions.push_back(pos);
		positionCount++;
	}
	
	void removePosition(int index) {
		positions.erase(positions.begin() + index);
		positionCount--;
	}
};

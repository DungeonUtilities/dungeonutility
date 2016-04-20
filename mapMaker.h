#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;
class mapMaker
{
private:
	//variables
	int playerCoord;
	int terrainMod;
	int coordinates[676];
	bool hasMap = false;
	bool quit;
	int playerMap[26][26];
	int trueSize;

public:
	//methods
	void mainMenu();
	void newMapMenu();
	void newMap(int terrain);
	void viewMap();
	void editMap();
	void distance();
	void findDist(int x1, int y1, int x2, int y2);
	const int feetPerUnit = 5;

	//corresponding arrays for movement coordinates
	char alphaCoords[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int numCoords[26] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	//char strCoords[26] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26' };
	char strCoords[26] = { 'a', 'b', 'c', 'd', 'e' };

	//corresponding arrays for terrains and their movement effects
	std::string terrain[11] = {"C", "F", "D", "M", "R", "S", "FD", "CB", "B", "FS", "T" };
	int movValue[11] = { 1, 2, 2, 3, 3, 4, 1, -1, -1, -1, 1 };
};

struct map
{
	//creates a map structure
	int size;
	int mapArray[26][26];
	int terrainChoice;

	void viewer(int userSize, int choice)
	{
		size = userSize;
		terrainChoice = choice;
		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; i < 26; j++)
				mapArray[i][j] = -1;
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				mapArray[i][j] = terrainChoice - 1;
		}
	}
};

//main menu
void mapMaker::mainMenu()
{
	//menu options
	int choice;
	std::cout << "Map Menu:" << std::endl;
	std::cout << "(1) Create New Map" << std::endl;
	std::cout << "(2) View Map" << std::endl;
	std::cout << "(3) Edit Tiles" << std::endl;
	std::cout << "(4) Check Distance" << std::endl;
	std::cout << "(5) Return to Main Menu" << std::endl;

	std::cin >> choice;
	//choice validation
	while (!std::cin || choice < 1 || choice > 5)
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout << " Invalid choice, please try again." << std::endl;
		std::cin >> choice;
	}

	//executes different methods based on input
	switch (choice)
	{
	case 1:
		mapMaker::newMapMenu();
		break;
	case 2:
		viewMap();
		break;
	case 3:
		editMap();
		break;
	case 4:
		distance();
		break;
	case 5:
		mapMaker::quit = true;
		break;
	default:
		std::cout << "Invalid option, please try again." << std::endl;
		mainMenu();
		break;

	}
}

//calculates distance
void mapMaker::distance()
{
	//sends user back to main menu if a map is not created
	if (mapMaker::hasMap == false)
	{
		std::cout << "You don't have a map! Pleas make a new map!" << std::endl;
		mapMaker::mainMenu();
	}
	std::cout << "Enter coordinates of two tiles separated by enter (ex. A5 or H26)" << std::endl;
	int coordCount = 1;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	while (coordCount < 3)
	{
		switch (coordCount)
		{
		case 1:
		{
			char temp[256];
			std::cin >> temp;
			int tempLength;
			bool noGood = false;
			int charCount = 0;
			while (!noGood)
			{
				int i = 0;
				while (temp[i] != 0)
				{
					charCount++;
					i++;
				}
				if (charCount == 2)
				{
					noGood = true;
					//try catch int
					//converts the characters to integers for the player map
					for (int j = 0; j < 26; j++)
					{
						if (temp[0] == alphaCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								distance();
							}

							x1 = numCoords[j];
						}
					}
					//converts the characters to integers for the player map
					if (temp[1] - 49 < 0 || temp[1] - 49 > 25)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
						distance();
					}
					if (temp[1] - 48 > trueSize)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
						std::cout << std::endl;
						distance();
					}
					for (int j = 0; j < 26; j++)
					{
						if ((temp[1] - 48) == numCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								distance();
							}
							y1 = numCoords[j];
						}
					}
					//std::cout << x1 << y1 << std::endl;
				}
				else if (charCount == 3)
				{
					noGood = true;
					//try catch int
					//converts the characters to integers for the player map
					for (int j = 0; j < 26; j++)
					{
						if (temp[0] == alphaCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								distance();
							}
							x1 = numCoords[j];
						}
					}
					if (temp[1] - 49 < 0 || temp[1] - 49 > 25)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
						distance();
					}
					if (temp[1] - 48 > trueSize)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
						std::cout << std::endl;
						distance();
					}
					if (temp[2] - 49 < 0 || temp[2] - 49 > 25)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
						distance();
					}
					if (temp[2] - 48 > trueSize)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
						std::cout << std::endl;
						distance();
					}
					int twoDigit = ((temp[1] - 48) * 10) + temp[2] - 48;
					//converts the characters to integers for the player map
					for (int j = 0; j < 26; j++)
					{
						if (twoDigit == numCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								distance();
							}
							y1 = numCoords[j];
						}
					}
					//std::cout << x1 << y1 << std::endl;
				}
				else
				{
					std::cout << "Invalid input, please enter a two-perameter coordinate separated by a space (ex. 'A5' or 'H25)" << std::endl;
					std::cin >> temp;
				}
			}
			coordCount++;
			break;
		}
		case 2:
		{
			char temp[256];
			std::cin >> temp;
			int tempLength;
			bool noGood = false;
			int charCount = 0;
			while (!noGood)
			{
				int i = 0;
				while (temp[i] != 0)
				{
					charCount++;
					i++;
				}
				if (charCount == 2)
				{
					noGood = true;
					//converts the characters to integers for the player map
					for (int j = 0; j < 26; j++)
					{
						if (temp[0] == alphaCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								distance();
							}
							x2 = numCoords[j];
						}
					}
					if (temp[1] - 49 < 0 || temp[1] - 49 > 25)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
						distance();
					}
					if (temp[1] - 48 > trueSize)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
						std::cout << std::endl;
						distance();
					}
					for (int j = 0; j < 26; j++)
					{
						if ((temp[1] - 48) == numCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								distance();
							}
							y2 = numCoords[j];
						}
					}
				}
				else if (charCount == 3)
				{
					noGood = true;
					//converts the characters to integers for the player map
					for (int j = 0; j < 26; j++)
					{
						if (temp[0] == alphaCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								std::cout << std::endl;
								distance();
							}
							x2 = numCoords[j];
						}
					}
					if (temp[1] - 49 < 0 || temp[1] - 49 > 25)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
						distance();
					}
					if (temp[1] - 48 > trueSize)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
						std::cout << std::endl;
						distance();
					}
					if (temp[2] - 49 < 0 || temp[2] - 49 > 25)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
						distance();
					}
					if (temp[2] - 48 > trueSize)
					{
						std::cin.clear();
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
						std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
						std::cout << std::endl;
						distance();
					}
					int twoDigit = ((temp[1] - 48) * 10) + temp[2] - 48;
					for (int j = 0; j < 26; j++)
					{
						if (twoDigit == numCoords[j])
						{
							if (j + 1 > trueSize)
							{
								std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
								distance();
							}
							y2 = numCoords[j];
						}
					}
				}
				else
				{
					std::cout << "Invalid input, please enter a two-perameter coordinate separated by a space (ex. 'A5' or 'H25)" << std::endl;
					std::cin >> temp;
				}
			}
			coordCount++;
			break;
		}
		default:
		{
			break;
		}
		}
	}
	double distance = sqrt ( (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1) ) * 5;
	if (distance < 0)
	{
		distance = distance * -1;
	}
	std::cout << "The the distance between these points is " << distance << " feet." << std::endl;
	std::cout << std::endl;
	mainMenu();
}

//menu for initial new map
void mapMaker::newMapMenu()
{
	std::cout << "New Map Terrain Options:" << std::endl;
	std::cout << "(1) Clear              (C)" << std::endl;
	std::cout << "(2) Forest             (F)" << std::endl;
	std::cout << "(3) Desert             (D)" << std::endl;
	std::cout << "(4) Back To Map Menu" << std::endl;
	int choice;
	std::cin >> choice;
	while (!std::cin || choice < 1 || choice > 4)
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout << " Invalid choice, please try again." << std::endl;
		std::cin >> choice;
	}

	switch (choice)
	{
	case 1:
		mapMaker::newMap(choice);
		break;
	case 2:
		mapMaker::newMap(choice);
		break;
	case 3:
		mapMaker::newMap(choice);
		break;
	case 4:
		mapMaker::mainMenu();
		break;
	default:
		std::cout << "Invalid option, please try again." << std::endl;
		mapMaker::newMapMenu();
		break;
	}
}

//Creates new map
void mapMaker::newMap(int terrain)
{
	//struct map *userMap = new map;
	bool goodInput = false;
	int size; 
	while (goodInput == false)
	{
		std::cout << "Enter a single integer value for the dimensions of your square map:" << std::endl;
		std::cin >> size;
		while (!std::cin || size < 1 || size > 26)
		{
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cout << " Invalid size, please try again." << std::endl;
			std::cin >> size;
		}
		if (size > 26)
		{
			size = 26;
			std::cout << "Your input is a bit too large, largest possible map of size 26 now in use." << std::endl;
		}
		if (size < 1)
		{
			size = 1;
			std::cout << "Map dimensions cannot be negative, smallest possible map of size 1 now in use." << std::endl;
		}
			goodInput = true;
			trueSize = size;
	}
	//userMap->terrainChoice = terrain;
	mapMaker::hasMap = true;
	//std::cout << "Map made successfully! Returning to map menu" << std::endl;
	
	//int mapArray[26][26];
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			playerMap[i][j] = -1;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			mapMaker::playerMap[i][j] = terrain - 1;
	}

	std::cout << "Map made successfully! Returning to map menu." << std::endl;
	std::cout << std::endl;
	mapMaker::mainMenu();
	//mapMaker::playerMap[26][26] = mapArray[26][26];
}

//Map editor
void mapMaker::editMap()
{
	//sends user back to main menu if a map is not created
	if (mapMaker::hasMap == false)
	{
		std::cout << "You don't have a map! Pleas make a new map!" << std::endl;
		std::cout << std::endl;
		mapMaker::mainMenu();
	}
	std::cout << "Enter coordinates of tile(s) separated by enter then followed by 'stop'." << std::endl;

	bool letsStop = false;
	int arrayCount = 0;
	char temp[256];
	int charCount = 0;
	int placement = 0;

	//Check if program should stop taking data
	while (!letsStop)
	{
		std::cin >> temp;
		bool noGood = false;
		//Make sure data is valid
		
		while (!noGood)
		{
			charCount = 0;
			int i = 0;
			while (temp[i] > 0)
			{
				charCount++;
				i++;
			}
			//std::cout << charCount << std::endl;
			if (temp[0] == 's' && temp[1] == 't' && temp[2] == 'o' && temp[3] == 'p')
			{
				letsStop = true;
				noGood = true;
			}
			else if (charCount == 2)
			{
				for (int k = 0; k < 26; k++)
				{
					if (temp[0] == alphaCoords[k])
					{
						if (k + 1 > trueSize)
						{
							std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
							std::cout << std::endl;
							editMap();
						}
						temp[0] = k;
					}
				}
				coordinates[placement] = temp[0];
				if (temp[1] - 49 < 0 || temp[1] - 49 > 25)
				{
					std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
					editMap();
				}
				if (temp[1] - 48 > trueSize)
				{
					std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
					std::cout << std::endl;
					editMap();
				}
				coordinates[placement + 1] = temp[1] - 49;
				placement = placement + 2;
				noGood = true;
			}
			else if (charCount == 3)
			{
				for (int k = 0; k < 26; k++)
				{
					if (temp[0] == alphaCoords[k])
					{
						if (k + 1 > trueSize)
						{
							std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
							std::cout << std::endl;
							editMap();
						}
						temp[0] = k;
					}
				}
				coordinates[placement] = temp[0];
				if (temp[1] - 49 < 0 || temp[1] - 49 > 25)
				{
					std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
					editMap();
				}
				if (temp[2] - 49 < 0 || temp[2] - 49 > 25)
				{
					std::cout << "Invalid coordinate, please enter a two-perameter coordinate (ex. 'A5' or 'H25')" << std::endl;
					editMap();
				}
				if (temp[1] - 48 > trueSize)
				{
					std::cout << "This coordinate does not exist on your map, please try again." << std::endl;
					std::cout << std::endl;
					editMap();
				}
				coordinates[placement + 1] = ((temp[1] - 49) * 10) + (temp[2] - 49);
				noGood = true;
				placement = placement + 2;
			}
			else
			{
				std::cout << "Invalid input, please enter a two-perameter coordinate (ex. 'A5' or 'H25)" << std::endl;
				std::cin >> temp;
			}
		}
		arrayCount++;
	}

	//int i = 0;
	//while (coordinates[i] >= 0)
	//{
	//	std::cout << coordinates[i] << " ";
	//	i++;
	//}

	std::cout << std::endl;
	std::cout << "Terrain Options:" << std::endl;
	std::cout << "(1)  Clear              (C)" << std::endl;
	std::cout << "(2)  Forest             (F)" << std::endl;
	std::cout << "(3)  Desert             (D)" << std::endl;
	std::cout << "(4)  Mountain           (M)" << std::endl;
	std::cout << "(5)  River              (R)" << std::endl;
	std::cout << "(6)  Swamp              (S)" << std::endl;
	std::cout << "(7)  Ford               (FD)" << std::endl;
	std::cout << "(8)  Catch-Basin        (CB)" << std::endl;
	std::cout << "(9)  Base               (B)" << std::endl;
	std::cout << "(10) Food Source        (FS)" << std::endl;
	std::cout << "(11) Trail              (T)" << std::endl;
	std::cout << "(12) Back To Map Menu" << std::endl;
	std::cout << std::endl;

	int choice;
	int i = 0;
	std::cin >> choice;
	while (!std::cin || choice < 1 || choice > 12)
	{
		std::cin.clear();
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		std::cout << " Invalid choice, please try again." << std::endl;
		std::cin >> choice;
	}

	switch (choice)
	{
	case 1:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 2:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 3:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 4:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 5:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 6:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 7:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 8:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 9:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 10:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 11:
		i = 0;
		while (coordinates[i] >= 0)
		{
			playerMap[coordinates[i]][coordinates[i + 1]] = choice - 1;
			i = i + 2;
		}
		mainMenu();
		break;
	case 12:
		mainMenu();
		break;
	default:
		std::cout << "invalid option, please try again." << std::endl;
		std::cout << std::endl;
		mainMenu();
		break;
	}
}

//displays map
void mapMaker::viewMap()
{
	//sends user back to main menu if a map is not created
	if (mapMaker::hasMap == false)
	{
		std::cout << "You don't have a map! Please make a new map!" << std::endl;
		std::cout << std::endl;
		mapMaker::mainMenu();
	}
	if (mapMaker::hasMap == true)
	{
		//std::cout << "This works" << std::endl;
		std::cout << " ";
		for (int i = 0; i < trueSize; i++)
		{
			std::cout << std::setw(4);
			std::cout << i + 1;
		}
		std::cout << std::endl;
		int temp;
		for (int i = 0; i < 26; i++)
		{
			std::cout << alphaCoords[i];
			for (int j = 0; j < 26; j++)
			{
				if (i < trueSize)
				{
					temp = playerMap[i][j];
				}
				//cout << temp << " ";
				if (temp != -1)
				{
					switch (temp)
					{
					case 0:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 1:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 2:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 3:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 4:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 5:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 6:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 7:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 8:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 9:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 10:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					case 11:
					{
						std::cout << std::setw(4);
						std::cout << terrain[temp];
						break;
					}
					default:
						break;
					}
					
				}
			}
			if (i < trueSize)
			{
				std::cout << std::endl;
			}
		}
		mainMenu();
	}
	//std::cout << "This works" << std::endl;
	int temp=0;
}
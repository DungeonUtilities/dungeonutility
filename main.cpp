#include <iostream>
#include <string>
#include "items.h"
#include "dice.h"
#include "Characters.h"
#include "enemy.h"
#include "mapMaker.h"


using namespace std;



int main() {
	Character *characterArray[5]; //array of pointers to character object, makes it so we can call this array and move through it as needed
	int numOfCharacter = 0; //int used to keep track of characters, very important, many uses throughout main method
	while (true){
		
		int choice = 0;
		cout << "\nWhat would you like to do?" << endl; //this is the main menu
		cout << "\n(1) Environment Generation" << endl;
		cout << "(2) Random Encounter Generation" << endl;
		cout << "(3) Character Generaton" << endl;
		cout << "(4) Display Character Information" << endl;
		cout << "(5) Level Up a Character" << endl;
		cout << "(6) Load/Save Game" << endl;
		cout << "(7) Dice Roller" << endl;
		cout << "(8) Exit." << endl;
		cout << "\nChoice: ";
		cin >> choice;

		while (!cin || choice > 8 || choice < 1 || cin.fail()) { //input validation
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid input!" << endl;
			cout << "What would you like to do?" << endl;
			cin >> choice;
		}
		
		if (choice == 1) { //map maker
			mapMaker map;
			map.mainMenu();
		}
		if (choice == 2) { //Random Encounter
			if (numOfCharacter > 0){ //checks to make sure there is at least character to avoid errors
				int totalLvl = 0;
				for (int i = 0; i < numOfCharacter; i++) {
					totalLvl += (characterArray[i]->getLvl()); //this for loop is designed to get the toal level of the party to pass it into the generateEncounter() method
				}
				generateEncounter(numOfCharacter, totalLvl); //generates an encounter
			}
			else { //only if there are no characters
				cout << "\nYou must make a character first!" << endl;
			}
		}
		if (choice == 3) { //character creation 
			if (numOfCharacter == 0){ //This is used if no characters have been created or loaded in yet.
				cout << "\nHow many characters would you like to create? (1 to 5 characters are allowed)" << endl;
				cout << "\nChoice: ";
				cin >> numOfCharacter;
				while (!cin || numOfCharacter > 5 || numOfCharacter < 1 || cin.fail()) { //input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nInvalid Input!" << endl;
					cout << "How many characters would you like to create? (1 to 5 characters are allowed)" << endl;
					cout << "\nChoice: ";
					cin >> numOfCharacter;
				}
				for (int i = 0; i < numOfCharacter; i++) {
					characterArray[i] = new Character(); //initializes and constructs (numOfCharacter) amount of new characters
				}
			}
			else if (numOfCharacter < 5) { //this option is used if characters have already been created or loaded in and have not reached the max amount of characters
				int x;
				cout << "\nWould you like to add an additional character?" << endl;
				cout << "(1) Yes\n(2) No" << endl;
				cout << "\nChoice: ";
				cin >> x;
				if (x == 1) {
					characterArray[numOfCharacter] = new Character(); //adds a character at reference [numOfCharacter]
					numOfCharacter += 1;							//adds one to the character counter
				}
			}
			else {
				cout << "You already have the maximum amount of characters! (5 characters)" << endl;
			}
		}
		if (choice == 4) { //Character information
			if (numOfCharacter > 0){
				for (int i = 0; i < numOfCharacter; i++) { //Prints out the name of each exitsting character
					cout<< "(" << i+1 << ") " << characterArray[i]->getName() << "\n";
				}
				cout << "Which character would you like to see info for? \n(Type the number of the character)" << endl;
				int charChoice;
				cout << "Choice: ";
				cin >> charChoice;
				while (!cin || charChoice < 1 || charChoice > numOfCharacter || cin.fail()) { //input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nInvalid Input!" << endl;
					cout << "What character would you like to see info for?" << endl;
					cout << "\nChoice: ";
					cin >> charChoice;
				}
				characterArray[charChoice - 1]->charInfo(); //calls charInfo to display basic character info
				characterArray[charChoice - 1]->displayStats(); //calls displayStats to display basic stats
				characterArray[charChoice - 1]->charInventory(); //calls charInventory to display inventories
			}
			else {
				cout << "You haven't made your characters yet!" << endl;
			}
		}
		if (choice == 5) { //level up characters
			if (numOfCharacter > 0){
				int x;
				cout << "Which character would you like to level up?" << endl;

				for (int i = 0; i < numOfCharacter; i++) { //prints out prompts and options
					cout << "(" << i + 1 << ") " << characterArray[i]->getName() << "\n";
				}
				cout << "Type the number of the character you wish to level up." << endl;
				cout << "\nChoice: ";
				cin >> x;
				while (!cin || x < 1 || x > numOfCharacter || cin.fail()) { //input validation
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nInvalid Input!" << endl;
					cout << "Type the number of the character you wish to level up." << endl;
					cout << "\nChoice: ";
					cin >> x;
				}
				characterArray[x - 1]->levelUp(); //levels up the character 
				cout << characterArray[x - 1]->getName() << " has progressed to level " << characterArray[x - 1]->getLvl() << "." << endl;
			}
			else {
				cout << "You have no characters to level up!" << endl;
			}
		}
		if (choice == 6) {//Load or save your characters
			int x;
			cout << "What would you like to do?\n(1) Load\n(2) Save \n\nChoice: ";
			cin >> x;
			while (!cin || x > 2 || x < 1 || cin.fail()) { //input validation
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nInvalid input!" << endl;
				cout << "What would you like to do?" << endl;
				cin >> x;
			}
			if (x == 1) {
				string charName;
				cout << "To load a character, type its name. (Case Sensitive)" << endl;
				cout << "To exit, type \"0\" with no quotation marks." << endl;
				cout << "Name : ";
				cin >> charName;
				bool alreadyExists = false;
				for (int i = 0; i < numOfCharacter; i++) {
					if (charName.compare(characterArray[i]->getName()) == 0){
						alreadyExists = true;
					}
				}
				if (alreadyExists) {
					cout << "A character with that name already exists or has already been loaded." << endl; //makes sure two character with the same name won't be loaded in
				}
				if (charName.compare("0")==0) { //exit option
					cout << "Exiting to menu." << endl;
				}
				else if (numOfCharacter >= 0 && numOfCharacter < 5 && !alreadyExists) { //checks to make sure characters can be loaded
					numOfCharacter++; //adds a character to the character counter
					characterArray[numOfCharacter-1] = new Character(charName); //adds the character from the file
				}
				else if (numOfCharacter >= 5){
					cout << "You have already reached the maximum amount of characters." << endl;
				}
				
			}
			if (x == 2) {
				if (numOfCharacter > 0) { //makes sure there is a character to save
					for (int i = 0; i < numOfCharacter; i++) {
						cout << "(" << i + 1 << ") " << characterArray[i]->getName() << "\n";
						characterArray[i]->saveCharacter(); //calls upon the save character method which prints readable information to a text file
					}
					cout << "The characters listed above were saved to individual text files." << endl;
				}
				if (numOfCharacter == 0) { //if there a no characters
					cout << "You have no characters to save!" << endl;
					cout << "Nothing will be saved." << endl;
				}
			}
		}
		if (choice == 7) { //dice roll function
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Dice::typeRoll(); //calls upon typeRoll() to roll a dice
		}
		if (choice == 8) {
			break; //break statement to exit the program
		}
	}
}


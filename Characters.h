#pragma once
#include <iostream>
#include <limits>
#include <vector>
#include <string> 
#include <sstream>
#include <fstream>
#include "dice.h"
#include "items.h"

class Character {
private:
	int bstr = 0, bdex = 0, bcon = 0, bintel = 0, bwis = 0, bchar = 0; //base stats
	int mstr = 0, mdex = 0, mcon = 0, mintel = 0, mwis = 0, mchar = 0; //base stat modifiers
	int hp, speed;
	int armorClass;//will need to organize equipment in order to calculate AC correctly.
	int proficiencyS = 0; //skill proficiency counter
	int expertise = 0; //skill counter
	int languages = 0; //how many languages the character can speak 
	int lvl, exp, profBonus; //leveling 
	string race, gender, background, morals, classType, toolprof, armorprof, weaponprof;
	string skillList;
	string hitDice; //hitDice in the format #dice+dice type e.g. 1d10
	string savingThrow;
	string name;
	ItemList inventory;

	void setName();
	void setBStats();
	void setMStats();
	void setRace();
	void setGender();
	void setBackground();
	void setAlign();
	void setClass();
	void setSkills();

	void calcAC();

	int statExist(int[], int);
	int statExist(string[], int);
	int calcMod(int);


public:
	Character();
	Character(string);
	void displayStats();
	void charInfo();
	string getName();
	void saveCharacter();
	void loadCharacter(string);
	void charInventory();
	void levelUp();
	int getLvl();

	int getBstr();
	int getBdex();
	int getBcon();
	int getBintel();
	int getBwis();
	int getBchar();

	int getMstr();
	int getMdex();
	int getMcon(); 
	int getMintel();
	int getMwis();
	int getMchar();
};
//constructor for making a new character
Character::Character() {
	Character::setName();
	Character::setBStats();
	Character::setMStats();
	Character::setRace();
	Character::setGender();
	Character::setAlign();
	Character::setBackground();
	Character::setClass();
	Character::setSkills();
	Character::calcAC();
	lvl = 1;
	exp = 0;
	profBonus = 2;
}
//constructor for loading in a character by their name
Character::Character(string n) {
	Character::loadCharacter(n);
}

void Character::setName() {
	cout << "What is the name of your Character?" << endl;
	cin >> name;
}
void Character::setBStats() {
	int statChoice[6];//holding array for a character's rolled stats
	int holding[6];//clone of statChoice (for future implementation of changing stats on the fly)
	int choice, holdChar;

	srand(time(NULL));
	for (int x = 0; x < 6; x++) {
		statChoice[x] = Dice::abilityScore();
	}
	for (int x = 0; x < 6; x++) {
		holding[x] = statChoice[x];
	}
	cout << "The following numbers can be assigned to a unique stat: ";
	for (int x = 0; x < 6; x++) {
		cout << statChoice[x] << " ";

	}
	cout << endl;
	cout << endl;
	//assigning to strength
	cout << "The following numbers can each be assigned to strength: ";
	for (int x = 0; x < 6; x++) {
		if (statChoice[x] != 0) {
			cout << statChoice[x] << " ";
		}
	}
	cout << endl;
	cout << "Which stat value will be assigned to strength? Input value: ";
	cin >> choice;
	while (!cin || statExist(statChoice, choice) == -1 || cin.fail()) {//statExists checks the statChoice array to make sure the stat in question is avaliable for assignment 
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "The following numbers can each be assigned to strength: ";
		for (int x = 0; x < 6; x++) {
			if (statChoice[x] != 0) {
				cout << statChoice[x] << " ";
			}
		}
		cout << endl;
		cout << "Which stat value will be assigned to strength? Input value: ";
		cin >> choice;
	}
	bstr = statChoice[statExist(statChoice, choice)];
	statChoice[statExist(statChoice, choice)] = 0;
	cout << endl;
	//assigning to dex
	cout << "The following numbers can each be assigned to dexterity: ";
	for (int x = 0; x < 6; x++) {
		if (statChoice[x] != 0) {
			cout << statChoice[x] << " ";
		}
	}
	cout << endl;
	cout << "Which stat value will be assigned to dexterity? Input value: ";
	cin >> choice;
	while (!cin || statExist(statChoice, choice) == -1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "The following numbers can each be assigned to dexterity: ";
		for (int x = 0; x < 6; x++) {
			if (statChoice[x] != 0) {
				cout << statChoice[x] << " ";
			}
		}
		cout << endl;
		cout << "Which stat value will be assigned to dexterity? Input value: ";
		cin >> choice;
	}
	bdex = statChoice[statExist(statChoice, choice)];
	statChoice[statExist(statChoice, choice)] = 0;
	cout << endl;
	//assigning to constitution
	cout << "The following numbers can each be assigned to constitution: ";
	for (int x = 0; x < 6; x++) {
		if (statChoice[x] != 0) {
			cout << statChoice[x] << " ";
		}
	}
	cout << endl;
	cout << "Which stat value will be assigned to constitution? Input value: ";
	cin >> choice;
	while (!cin || statExist(statChoice, choice) == -1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "The following numbers can each be assigned to constitution: ";
		for (int x = 0; x < 6; x++) {
			if (statChoice[x] != 0) {
				cout << statChoice[x] << " ";
			}
		}
		cout << endl;
		cout << "Which stat value will be assigned to constitution? Input value: ";
		cin >> choice;
	}
	bcon = statChoice[statExist(statChoice, choice)];
	statChoice[statExist(statChoice, choice)] = 0;
	cout << endl;
	//assigning to intelligence
	cout << "The following numbers can each be assigned to intelligence: ";
	for (int x = 0; x < 6; x++) {
		if (statChoice[x] != 0) {
			cout << statChoice[x] << " ";
		}
	}
	cout << endl;
	cout << "Which stat value will be assigned to intelligence? Input value: ";
	cin >> choice;
	while (!cin || statExist(statChoice, choice) == -1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "The following numbers can each be assigned to intelligence: ";
		for (int x = 0; x < 6; x++) {
			if (statChoice[x] != 0) {
				cout << statChoice[x] << " ";
			}
		}
		cout << endl;
		cout << "Which stat value will be assigned to intelligence? Input value: ";
		cin >> choice;
	}
	bintel = statChoice[statExist(statChoice, choice)];
	statChoice[statExist(statChoice, choice)] = 0;
	cout << endl;
	//assigning to wisdom
	cout << "The following numbers can each be assigned to wisdom: ";
	for (int x = 0; x < 6; x++) {
		if (statChoice[x] != 0) {
			cout << statChoice[x] << " ";
		}
	}
	cout << endl;
	cout << "Which stat value will be assigned to wisdom? Input value: ";
	cin >> choice;
	while (!cin || statExist(statChoice, choice) == -1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "The following numbers can each be assigned to wisdom: ";
		for (int x = 0; x < 6; x++) {
			if (statChoice[x] != 0) {
				cout << statChoice[x] << " ";
			}
		}
		cout << endl;
		cout << "Which stat value will be assigned to wisdom? Input value: ";
		cin >> choice;
	}
	bwis = statChoice[statExist(statChoice, choice)];
	statChoice[statExist(statChoice, choice)] = 0;

	//assigning to charisma it's the last one so.... yeah.
	for (int x = 0; x < 6; x++) {
		if (statChoice[x] != 0) {
			holdChar = x;
		}
	}
	bchar = statChoice[holdChar];
	statChoice[holdChar] = 0;

	//display all stats
	cout << endl;
	cout << "The following are the assigned stats for this character" << endl;
	cout << "Strength: " << bstr << endl;
	cout << "Dexterity: " << bdex << endl;
	cout << "Constitution: " << bcon << endl;
	cout << "Intelligence: " << bintel << endl;
	cout << "Wisdom: " << bwis << endl;
	cout << "Charisma: " << bchar << endl;
}
void Character::setMStats() {
	mstr += calcMod(bstr);
	mdex += calcMod(bdex);
	mcon += calcMod(bcon);
	mintel += calcMod(bintel);
	mwis += calcMod(bwis);
	mchar += calcMod(bchar);
}
void Character::setRace() {
	int choice;
	cout << "What Race is your character?" << endl;
	cout << "1. Human" << endl;
	cout << "2. Dwarf" << endl;
	cout << "3. Elf" << endl;
	cout << "4. Halfling" << endl;
	cin >> choice;
	while (!cin || choice > 4 || choice < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "What Race is your character?" << endl;
		cout << "1. Human" << endl;
		cout << "2. Dwarf" << endl;
		cout << "3. Elf" << endl;
		cout << "4. Halfling" << endl;
		cin >> choice;
	}
	if (choice == 1) {
		race = "Human";
		mstr++;
		mdex++;
		mcon++;
		mintel++;
		mwis++;
		mchar++;
		speed = 30;
	}
	if (choice == 2) {
		race = "Dwarf";
		mcon += 2;
		speed = 25;
	}
	if (choice == 3) {
		race = "Elf";
		mdex += 2;
		speed = 30;
	}
	if (choice == 4) {
		race = "Halfling";
		mdex += 2;
		speed = 25;
	}
}
void Character::setGender() {
	int choice;
	cout << "What will the gender of your character be?" << endl;
	cout << "1. Female" << endl;
	cout << "2. Male" << endl;
	cin >> choice;
	while (!cin || choice > 2 || choice < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "What will the gender of your character be?" << endl;
		cout << "1. Female" << endl;
		cout << "2. Male" << endl;
		cin >> choice;
	}
	if (choice == 1) {
		gender = "Female";
	}
	if (choice == 2) {
		gender = "Male";
	}
}
void Character::setAlign() {
	int choice;
	cout << "Where does your character align themselves?" << endl;
	cout << "1. Lawful Good" << endl;
	cout << "2. Lawful Neutral" << endl;
	cout << "3. Lawful Evil" << endl;
	cout << "4. Neutral Good" << endl;
	cout << "5. True Neutral" << endl;
	cout << "6. Neutral Evil" << endl;
	cout << "7. Chaotic Good" << endl;
	cout << "8. Chaotic Neutral" << endl;
	cout << "9. Chaotic Evil" << endl;
	cin >> choice;
	while (!cin || choice > 9 || choice < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "Where does your character align themselves?" << endl;
		cout << "1. Lawful Good" << endl;
		cout << "2. Lawful Neutral" << endl;
		cout << "3. Lawful Evil" << endl;
		cout << "4. Neutral Good" << endl;
		cout << "5. True Neutral" << endl;
		cout << "6. Neutral Evil" << endl;
		cout << "7. Chaotic Good" << endl;
		cout << "8. Chaotic Neutral" << endl;
		cout << "9. Chaotic Evil" << endl;
		cin >> choice;
	}
	if (choice == 1) {
		morals = "Lawful Good";
	}
	if (choice == 2) {
		morals = "Lawful Neutral";
	}
	if (choice == 3) {
		morals = "Lawful Evil";
	}
	if (choice == 4) {
		morals = "Neutral Good";
	}
	if (choice == 5) {
		morals = "True Neutral";
	}
	if (choice == 6) {
		morals = "Neutral Evil";
	}
	if (choice == 7) {
		morals = "Chaotic Good";
	}
	if (choice == 8) {
		morals = "Chaotic Neutral";
	}
	if (choice == 9) {
		morals = "Chaotic Evil";
	}
}
void Character::setBackground() {//it should be noted that clothes were not added in this, as that's really more for the player to decide.
	int choice, subChoice;
	cout << "What is your character's background?" << endl;
	cout << "1. Acolyte" << endl;
	cout << "2. Criminal" << endl;
	cout << "3. Folk Hero" << endl;
	cout << "4. Noble/Knight" << endl;
	cout << "5. Sage" << endl;
	cin >> choice;
	while (!cin || choice > 5 || choice < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "What is your character's background?" << endl;
		cout << "1. Acolyte" << endl;
		cout << "2. Criminal" << endl;
		cout << "3. Folk Hero" << endl;
		cout << "4. Noble" << endl;
		cout << "5. Sage" << endl;
		cin >> choice;
	}
	if (choice == 1) {
		background = "Acolyte";
		proficiencyS += 2;
		languages += 2;
		inventory.addItem(new Coinage(15, "coins", 15, 0, 0, 0, 0));
		inventory.addItem(new Gear(1, "Holy Gift", 100, 1.5, "Gift given upon entering preisthood."));
		inventory.addItem(new Gear(1, "Prayer book", 250, 5, "A Book of Prayers."));
		inventory.addItem(new Gear(5, "Incense", 10, .5, "A stick of incense"));
	}
	if (choice == 2) {
		background = "Criminal";
		proficiencyS += 2;
		languages += 1;
		toolprof = "A gaming set, thieves tools ";
		inventory.addItem(new Coinage(15, "coins", 15, 0, 0, 0, 0));
		inventory.addItem(new Gear(1, "Crowbar", 200, 5, "Multiple purpose tool"));
	}
	if (choice == 3) {
		background = "Folk Hero";
		proficiencyS += 2;
		languages += 1;
		inventory.addItem(new Coinage(15, "coins", 0, 0, 0, 15, 0));
		toolprof = "One artisan tool, Vehicles (land) ";
		cout << "This background can have one of the following tools, select one of the following:" << endl;
		cout << "1. Alchemist's Supplies" << endl;
		cout << "2. Cook's Supplies" << endl;
		cout << "3. Smith's Tools" << endl;
		cout << "4. Tinker's Tools" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 4 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "This background can have one of the following tools, select one of the following:" << endl;
			cout << "1. Alchemist's Supplies" << endl;
			cout << "2. Cook's Supplies" << endl;
			cout << "3. Smith's Tools" << endl;
			cout << "4. Tinker's Tools" << endl;
			cin >> choice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Gear(1, "Alchemist's Supplies", 5000, 8, "Artisan Tools for an Alchemist."));
		}
		if (subChoice == 2) {
			inventory.addItem(new Gear(1, "Cook's Supplies", 100, 8, "Artisan Tools for a Cook."));
		}
		if (subChoice == 3) {
			inventory.addItem(new Gear(1, "Smith's Tools", 2000, 8, "Artisan Tools for a Smith."));
		}
		if (subChoice == 4) {
			inventory.addItem(new Gear(1, "Tinker's Tools", 5000, 10, "Artisan Tools for a Tinker."));
		}
		inventory.addItem(new Gear(1, "Iron Pot", 200, 10, "An iron pot."));
		inventory.addItem(new Gear(1, "Shovel", 200, 5, "A shovel."));
	}
	if (choice == 4) {
		background = "Noble";
		proficiencyS += 2;
		toolprof = "A gaming set ";
		languages += 1;
		inventory.addItem(new Coinage(15, "coins", 0, 0, 0, 25, 0));
		inventory.addItem(new Gear(1, "Signet Ring", 500, .1, "A ring bearing a crest"));
	}
	if (choice == 5) {
		background = "Sage";
		proficiencyS += 2;
		languages += 2;
		inventory.addItem(new Coinage(15, "coins", 0, 0, 0, 10, 0));
	}
}
void Character::setClass() {//note that leveling abilities will be done in level up method
	int choice, subChoice;
	cout << "What class will your character be?" << endl;
	cout << "1. Cleric" << endl;
	cout << "2. Fighter" << endl;
	cout << "3. Rogue" << endl;
	cout << "4. Wizard" << endl;
	cin >> choice;
	while (!cin || choice > 4 || choice < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Input!" << endl;
		cout << "What class will your character be?" << endl;
		cout << "1. Cleric" << endl;
		cout << "2. Fighter" << endl;
		cout << "3. Rogue" << endl;
		cout << "4. Wizard" << endl;
		cin >> choice;
	}
	if (choice == 1) {//Cleric Class
		classType = "Cleric";
		hitDice = "1d8"; //per level
		hp = 8 + mcon;//higher levels - current hp + 1d8 + mcon (Need to Verify)
		armorprof = "Light, Medium Armor and Shields";
		weaponprof = "Simple Weapons";
		//toolprof
		savingThrow = "Wisdom, Charisma";
		proficiencyS += 2;
		cout << "Your character's base stats are:" << endl;
		displayStats();
		//setting primary weapon
		cout << "Choose your cleric's starting primary weapon: " << endl;
		cout << "1. Mace" << endl;
		cout << "2. Warhammer" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your cleric's starting primary weapon: " << endl;
			cout << "1. Mace" << endl;
			cout << "2. Warhammer" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Weapon(1, "Mace", 500, "1d6", 4, false));
		}
		if (subChoice == 2) {
			inventory.addItem(new Weapon(1, "Warhammer", 1500, "1d8", 2, false));
		}
		//setting starting armor
		cout << "Choose your cleric's starting armor: " << endl;
		cout << "1. Scale Mail" << endl;
		cout << "2. Leather armor" << endl;
		cout << "3. Chain Mail" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 3 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your cleric's starting armor: " << endl;
			cout << "1. Scale Mail" << endl;
			cout << "2. Leather armor" << endl;
			cout << "3. Chain Mail" << endl;
			cin >> subChoice;
		}
		int mArmorClass = mdex;
		if (subChoice == 1) {
			if (mdex > 2) {//AC modifier
				mArmorClass = 2;
			}
			inventory.addItem(new Armor(1, "Scale Mail", 5000, 14 + mArmorClass, false, 45));
		}
		if (subChoice == 2) {
			inventory.addItem(new Armor(1, "Leather armor", 1000, 11 + mArmorClass, true, 10));
		}
		if (subChoice == 3) {
			inventory.addItem(new Armor(1, "Chain Mail", 7500, 16, false, 55));
		}
		//setting secondary weapon
		cout << "Choose your cleric's starting secondary weapon: " << endl;
		cout << "1. Light Crossbow (with 20 bolts)" << endl;
		cout << "2. Dagger" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your cleric's starting secondary weapon: " << endl;
			cout << "1. Light Crossbow (with 20 bolts)" << endl;
			cout << "2. Dagger" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Weapon(1, "Light Crossbow", 2500, "1d8", 5, true));
			inventory.addItem(new Gear(1, "Crossbow Bolts (20)", 100, 1.5, "Ammunition for a crossbow"));
		}
		if (subChoice == 2) {
			inventory.addItem(new Weapon(1, "Dagger", 200, "1d4", 1, false));
		}
		//consider adding the packs (between explorer or preist's for cleric)
		//adding shield
		inventory.addItem(new Armor(1, "Shield", 1000, 2, true, 6));
	}
	if (choice == 2) {//Fighter Class
		classType = "Fighter";
		hitDice = "1d10"; //per level
		hp = 10 + mcon;//higher levels - current hp + 1d10 + mcon (Need to Verify)
		armorprof = "Light, Medium, Heavy Armor and Shields";
		weaponprof = "Simple, Martial Weapons";
		//toolprof
		savingThrow = "Strength, Constitution";
		proficiencyS += 2;
		cout << "Your character's base stats are:" << endl;
		displayStats();
		//setting armor
		cout << "Choose your Fighter's starting armor: " << endl;
		cout << "1. Chain Mail" << endl;
		cout << "2. Leather with Longbow/20 arrows" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your Fighter's starting armor: " << endl;
			cout << "1. Chain Mail" << endl;
			cout << "2. Leather with Longbow/20 arrows" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Armor(1, "Chain Mail", 7500, 16, false, 55));
		}
		if (subChoice == 2) {
			int mArmorClass = mdex;
			if (mdex > 2) {//AC modifier
				mArmorClass = 2;
			}
			inventory.addItem(new Armor(1, "Leather armor", 1000, 11 + mArmorClass, true, 10));
			inventory.addItem(new Weapon(1, "Longbow", 50 * 100, "1d8", 2, true));
			inventory.addItem(new Gear(20, "Arrows(20)", 100, 1, "Ammunition for a bow"));
		}
		//setting primary weapon 
		cout << "Choose your Fighter's starting primary weapon preference: " << endl;
		cout << "1. One Martial Weapon with Shield" << endl;
		cout << "2. Two Martial Weapons" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your Fighter's starting primary weapon preference: " << endl;
			cout << "1. One Martial Weapon with Shield" << endl;
			cout << "2. Two Martial Weapons" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			cout << "Choose your Fighter's starting weapon: " << endl;
			cout << "1. Greatsword" << endl;
			cout << "2. Longsword" << endl;
			cout << "3. Pike" << endl;
			cout << "4. Morningstar" << endl;
			cin >> subChoice;
			while (!cin || subChoice > 4 || subChoice < 1 || cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid Input!" << endl;
				cout << "Choose your Fighter's starting weapon: " << endl;
				cout << "1. Greatsword" << endl;
				cout << "2. Longsword" << endl;
				cout << "3. Pike" << endl;
				cout << "4. Morningstar" << endl;
				cin >> subChoice;
			}
			if (subChoice == 1) {
				inventory.addItem(new Weapon(1, "Greatsword", 50 * 100, "2d6", 6, false));
				inventory.addItem(new Armor(1, "Shield", 10 * 100, 2, true, 6));
			}
			if (subChoice == 2) {
				inventory.addItem(new Weapon(1, "Longsword", 15 * 100, "1d8", 3, false));
				inventory.addItem(new Armor(1, "Shield", 10 * 100, 2, true, 6));
			}
			if (subChoice == 3) {
				inventory.addItem(new Weapon(1, "Pike", 5 * 100, "1d10", 18, false));
				inventory.addItem(new Armor(1, "Shield", 10 * 100, 2, true, 6));
			}
			if (subChoice == 4) {
				inventory.addItem(new Weapon(1, "Morningstar", 15 * 100, "1d8", 4, false));
				inventory.addItem(new Armor(1, "Shield", 10 * 100, 2, true, 6));
			}
		}
		if (subChoice == 2) {
			cout << "Choose your Fighter's 1st starting weapon: " << endl;
			cout << "1. Greatsword" << endl;
			cout << "2. Longsword" << endl;
			cout << "3. Pike" << endl;
			cout << "4. Morningstar" << endl;
			cin >> subChoice;
			while (!cin || subChoice > 4 || subChoice < 1 || cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid Input!" << endl;
				cout << "Choose your Fighter's 1st starting weapon: " << endl;
				cout << "1. Greatsword" << endl;
				cout << "2. Longsword" << endl;
				cout << "3. Pike" << endl;
				cout << "4. Morningstar" << endl;
				cin >> subChoice;
			}
			if (subChoice == 1) {
				inventory.addItem(new Weapon(1, "Greatsword", 50 * 100, "2d6", 6, false));
			}
			if (subChoice == 2) {
				inventory.addItem(new Weapon(1, "Longsword", 15 * 100, "1d8", 3, false));
			}
			if (subChoice == 3) {
				inventory.addItem(new Weapon(1, "Pike", 5 * 100, "1d10", 18, false));
			}
			if (subChoice == 4) {
				inventory.addItem(new Weapon(1, "Morningstar", 15 * 100, "1d8", 4, false));
			}
			cout << "Choose your Fighter's 2nd starting weapon: " << endl;
			cout << "1. Greatsword" << endl;
			cout << "2. Longsword" << endl;
			cout << "3. Pike" << endl;
			cout << "4. Morningstar" << endl;
			cin >> subChoice;
			while (!cin || subChoice > 4 || subChoice < 1 || cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid Input!" << endl;
				cout << "Choose your Fighter's 2nd starting weapon: " << endl;
				cout << "1. Greatsword" << endl;
				cout << "2. Longsword" << endl;
				cout << "3. Pike" << endl;
				cout << "4. Morningstar" << endl;
				cin >> subChoice;
			}
			if (subChoice == 1) {
				inventory.addItem(new Weapon(1, "Greatsword", 50 * 100, "2d6 slashing", 6, false));
			}
			if (subChoice == 2) {
				inventory.addItem(new Weapon(1, "Longsword", 15 * 100, "1d8 slashing", 3, false));
			}
			if (subChoice == 3) {
				inventory.addItem(new Weapon(1, "Pike", 5 * 100, "1d10 piercing", 18, false));
			}
			if (subChoice == 4) {
				inventory.addItem(new Weapon(1, "Morningstar", 15 * 100, "1d8 piercing", 4, false));
			}
		}
		//setting secondary weapon
		cout << "Choose your Fighter's starting secondary weapon: " << endl;
		cout << "1. Light Crossbow (with 20 bolts)" << endl;
		cout << "2. Two Handaxes" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your Fighter's starting secondary weapon: " << endl;
			cout << "1. Light Crossbow (with 20 bolts)" << endl;
			cout << "2. Two Handaxes" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Weapon(1, "Light Crossbow", 2500, "1d8", 5, true));
			inventory.addItem(new Gear(20, "Crossbow Bolts(20)", 100, 1.5, "Ammunition for a crossbow"));
		}
		if (subChoice == 2) {
			inventory.addItem(new Weapon(2, "Handaxe", 500, "1d6", 2, true));
		}
	}
	if (choice == 3) {//Rogue Class
		classType = "Rogue";
		hitDice = "1d8"; //per level
		hp = 8 + mcon;//higher levels - current hp + 1d8 + mcon (Need to Verify)
		armorprof = "Light Armor";
		weaponprof = "Simple Weapons, Crossbows, Longswords, Rapiers, Shortswords";
		if (background != "Criminal") {
			toolprof += "Thieves' Tools";
		}
		savingThrow = "Dexterity, Intelligence";
		proficiencyS += 2;
		cout << "Your character's base stats are:" << endl;
		displayStats();
		//setting primary weapon
		cout << "Choose your rogue's starting primary weapon: " << endl;
		cout << "1. Rapier" << endl;
		cout << "2. Shortsword" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your rogue's starting primary weapon: " << endl;
			cout << "1. Rapier" << endl;
			cout << "2. Shortsword" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Weapon(1, "Rapier", 2500, "1d8", 2, false));
		}
		if (subChoice == 2) {
			inventory.addItem(new Weapon(1, "Shortsword", 1000, "1d6", 2, false));
		}
		//setting secondary weapon
		cout << "Choose your rogue's starting secondary weapon: " << endl;
		cout << "1. Shortbow (with 20 arrows)" << endl;
		cout << "2. Shortsword" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your rogue's starting secondary weapon: " << endl;
			cout << "1. Shortbow (with 20 arrows)" << endl;
			cout << "2. Shortsword" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Weapon(1, "Shortbow", 2500, "1d6", 2, true));
			inventory.addItem(new Gear(1, "Arrows (20)", 100, 1, "Ammunition for a bow"));
		}
		if (subChoice == 2) {
			inventory.addItem(new Weapon(1, "Shortsword", 1000, "1d6", 2, false));
		}
		//adding starting armor, two daggers and thieves tools
		int mArmorClass = mdex;
		if (mdex > 2) {//AC modifier
			mArmorClass = 2;
		}
		inventory.addItem(new Armor(1, "Leather armor", 1000, 11 + mArmorClass, true, 10));
		inventory.addItem(new Weapon(2, "Dagger", 200, "1d4", 1, false));
		inventory.addItem(new Gear(1, "Thieves' Tools", 2500, 1, "Used to disarm traps, pick locks"));
	}
	if (choice == 4) {//Wizard Class
		classType = "Wizard";
		hitDice = "1d6"; //per level
		hp = 6 + mcon;//higher levels - current hp + 1d6 + mcon (Need to Verify)
					  //armorprof
		weaponprof = " Daggers, Darts, Slings, Quarterstaffs, Light Crossbows";
		//toolprof
		savingThrow = "Intelligence, Wisdom";
		proficiencyS += 2;
		cout << "Your character's base stats are:" << endl;
		displayStats();
		//setting primary weapon 
		cout << "Choose your Wizard's starting primary weapon: " << endl;
		cout << "1. Quarterstaff" << endl;
		cout << "2. Dagger" << endl;
		cin >> subChoice;
		while (!cin || subChoice > 2 || subChoice < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Choose your Wizard's starting primary weapon: " << endl;
			cout << "1. Quarterstaff" << endl;
			cout << "2. Dagger" << endl;
			cin >> subChoice;
		}
		if (subChoice == 1) {
			inventory.addItem(new Weapon(1, "Quarterstaff", 20, "1d6", 4, false));
		}
		if (subChoice == 2) {
			inventory.addItem(new Weapon(1, "Dagger", 200, "1d4", 1, false));
		}
		inventory.addItem(new Gear(1, "Spellbook", 25 * 100, 5, "Book of spells"));
	}
}
void Character::setSkills() {
	int choice;
	string skills[18] = { "Athletics","Acrobatics","Sleight of Hand",
		"Stealth","Arcana","History",
		"Investigation","Nature","Religion",
		"Animal Handling","Insight","Medicine",
		"Perception","Survival","Deception",
		"Intimidation","Performance","Persuasion" };
	cout << "Your character can have " << proficiencyS << " of the following skills:" << endl;
	for (int x = 0; x < 18; x++) {
		cout << x << ". " << skills[x] << endl;
	}
	for (int x = 0; x < proficiencyS; x++) {
		if (x > 0) {
			cout << "Your character can have " << proficiencyS - x << " of the following skills:" << endl;
			for (int x = 0; x < 18; x++) {
				cout << x << ". " << skills[x] << endl;
			}
		}
		cout << "From the list, pick skill #" << x + 1 << ": ";
		cin >> choice;
		while (!cin || statExist(skills, choice) == -1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input!" << endl;
			cout << "Your character can choose " << proficiencyS - x << " more of the following skills:" << endl;
			for (int x = 0; x < 18; x++) {
				cout << x << ". " << skills[x] << endl;
			}
			cout << "From the list, pick skill #" << x << ": ";
			cin >> choice;
		}
		skillList += skills[choice] + " ";
		skills[choice] += "-Taken";
	}
}
void Character::calcAC() {
	inventory.orderList();
	armorClass = inventory.getArmorClass();
}

void Character::levelUp() {
	//increasing proficiency bonus as needed
	lvl++;
	if (lvl == 1 || lvl == 4) {
		profBonus = 2;
	}
	if (lvl == 5 || lvl == 8) {
		profBonus = 3;
	}
	if (lvl == 9 || lvl == 12) {
		profBonus = 4;
	}
	if (lvl == 13 || lvl == 16) {
		profBonus = 5;
	}
	if (lvl == 17 || lvl == 20) {
		profBonus = 6;
	}
	//class specific leveling
	//leveling for a cleric
	srand(time(NULL));
	if (classType == "Cleric") {
		hp += Dice::roll(8) + mcon;
	}
	if (classType == "Fighter") {
		hp += Dice::roll(10) + mcon;
	}
	if (classType == "Rogue") {
		hp += Dice::roll(8) + mcon;
	}
	if (classType == "Wizard") {
		hp += Dice::roll(6) + mcon;
	}
}

int Character::statExist(int a[], int check) {
	for (int x = 0; x < 6; x++) {
		if (a[x] == check) {
			return x;
		}
	}
	return -1;
}
int Character::statExist(string a[], int check) {
	if (check > 17 || check < 0) {
		return -1;
	}
	if (a[check].find("Taken") != -1) {
		return -1;
	}
	return check;
}
void Character::displayStats() {
	cout << "Strength: " << bstr << " Modifier: " << mstr << endl;
	cout << "Dexterity: " << bdex << " Modifier: " << mdex << endl;
	cout << "Constitution: " << bcon << " Modifier: " << mcon << endl;
	cout << "Intelligence: " << bintel << " Modifier: " << mintel << endl;
	cout << "Wisdom: " << bwis << " Modifier: " << mwis << endl;
	cout << "Charisma: " << bchar << " Modifier: " << mchar << endl;
	cout << "Armor Class: " << armorClass << endl;
	cout << endl;
}
void Character::charInfo() {
	cout << "Character Name: " << name << endl;
	cout << "Level: " << lvl << endl;
	cout << "Proficiency Bonus: " << profBonus << endl;
	cout << "Race: " << race << endl;
	cout << "Gender: " << gender << endl;
	cout << "Alignment: " << morals << endl;
	cout << "Background: " << background << endl;
	cout << "Tool Proficiency: " << toolprof << endl;
	cout << "Armor Proficiency: " << armorprof << endl;
	cout << "Weapon Proficiency: " << weaponprof << endl;
	cout << "Class: " << classType << endl;
	cout << "Number of Languages: " << languages << endl;
	cout << "Skill List: " << skillList << endl;
	cout << endl;
}
void Character::charInventory() {
	inventory.getValues();
}
int Character::calcMod(int x) {
	if (x == 1) {
		return -5;
	}
	if (x == 2 || x == 3) {
		return -4;
	}
	if (x == 4 || x == 5) {
		return -3;
	}
	if (x == 6 || x == 7) {
		return -2;
	}
	if (x == 8 || x == 9) {
		return -1;
	}
	if (x == 10 || x == 11) {
		return 0;
	}
	if (x == 12 || x == 13) {
		return 1;
	}
	if (x == 14 || x == 15) {
		return 2;
	}
	if (x == 16 || x == 17) {
		return 3;
	}
	if (x == 18 || x == 19) {
		return 4;
	}
	if (x == 20 || x == 21) {
		return 5;
	}
	if (x == 22 || x == 23) {
		return 6;
	}
	if (x == 24 || x == 25) {
		return 7;
	}
	if (x == 26 || x == 27) {
		return 8;
	}
	if (x == 28 || x == 2) {
		return 9;
	}
	if (x == 30) {
		return 10;
	}
}
string Character::getName() {
	return name;
}

void Character::saveCharacter() {
	string saveName = name + ".txt";
	string saveLine, saveLine2;
	string newLine = "\n";
	string out;
	ofstream save(saveName);
	save << "Character Name: " + name + "\n";
	save << "Level: " + to_string(lvl) + "\n";
	save << "Proficiency Bonus: " + to_string(profBonus) + "\n";
	save << "Strength: " + to_string(bstr) << " Modifier: " + to_string(mstr) + "\n";
	save << "Dexterity: " + to_string(bdex) << " Modifier: " + to_string(mdex) + "\n";
	save << "Constitution: " + to_string(bcon) << " Modifier: " + to_string(mcon) + "\n";
	save << "Intelligence: " + to_string(bintel) << " Modifier: " + to_string(mintel) + "\n";
	save << "Wisdom: " + to_string(bwis) << " Modifier: " + to_string(mwis) + "\n";
	save << "Charisma: " + to_string(bchar) << " Modifier: " + to_string(mchar) + "\n";
	save << "Armor Class: " + to_string(armorClass) + "\n";
	save << "Race: " + race + "\n";
	save << "Gender: " + gender + "\n";
	save << "Alignment: " + morals + "\n";
	save << "Background: " + background + "\n";
	save << "Tool Proficiency: " + toolprof + "\n";
	save << "Armor Proficiency: " + armorprof + "\n";
	save << "Weapon Proficiency: " + weaponprof + "\n";
	save << "Class: " + classType + "\n";
	save << "Number of Languages: " + to_string(languages) + "\n";
	save << "Skill List: " + skillList + "\n";
	inventory.saveFile(name);
	save.close();
}
void Character::loadCharacter(string n) {
	int counter = 0;
	string fileName = n + ".txt";
	string line, possible;
	ifstream file;
	file.open(fileName);
	while (!file) {
		cout << "No file exists." << endl;
		cout << "To load a character, type its name. (Case Sensitive)" << endl;
		cout << "Name : ";
		cin >> possible;
		fileName = possible + ".txt";
		file.open(fileName);
	}
	while (getline(file, line)) {
		if (counter == 0) {
			name = line.substr(line.find(":") + 2);
		}
		if (counter == 1) {
			lvl = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 2) {
			profBonus = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 3) {
			bstr = stoi(line.substr((line.find(":") + 2), (line.find(":") + 4)));
			line = line.substr((line.find(":") + 2));
			mstr = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 4) {
			bdex = stoi(line.substr((line.find(":") + 2), (line.find(":") + 4)));
			line = line.substr((line.find(":") + 2));
			mdex = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 5) {
			bcon = stoi(line.substr((line.find(":") + 2), (line.find(":") + 4)));
			line = line.substr((line.find(":") + 2));
			mcon = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 6) {
			bintel = stoi(line.substr((line.find(":") + 2), (line.find(":") + 4)));
			line = line.substr((line.find(":") + 2));
			mintel = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 7) {
			bwis = stoi(line.substr((line.find(":") + 2), (line.find(":") + 4)));
			line = line.substr((line.find(":") + 2));
			mwis = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 8) {
			bchar = stoi(line.substr((line.find(":") + 2), (line.find(":") + 4)));
			line = line.substr((line.find(":") + 2));
			mchar = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 9) {
			armorClass = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 10) {
			race = line.substr(line.find(":") + 2);
		}
		if (counter == 11) {
			gender = line.substr(line.find(":") + 2);
		}
		if (counter == 12) {
			morals = line.substr(line.find(":") + 2);
		}
		if (counter == 13) {
			background = line.substr(line.find(":") + 2);
		}
		if (counter == 14) {
			toolprof = line.substr(line.find(":") + 2);
		}
		if (counter == 15) {
			armorprof = line.substr(line.find(":") + 2);
		}
		if (counter == 16) {
			weaponprof = line.substr(line.find(":") + 2);
		}
		if (counter == 17) {
			classType = line.substr(line.find(":") + 2);
		}
		if (counter == 18) {
			languages = stoi(line.substr(line.find(":") + 2));
		}
		if (counter == 19) {
			skillList = line.substr(line.find(":") + 2);
		}
		counter++;
	}
	inventory.openFile(n);
	file.close();
}

int Character::getLvl() {
	return lvl;
}
//getters for base stats
int Character::getBstr() {
	return bstr;
}
int Character::getBdex() {
	return bdex;
}
int Character::getBcon() {
	return bcon;
}
int Character::getBintel() {
	return bintel;
}
int Character::getBwis() {
	return bwis;
}
int Character::getBchar() {
	return bchar;
}
//getters for modifiers for stats
int Character::getMstr() {
	return mstr;
}
int Character::getMdex() {
	return mdex;
}
int Character::getMcon() {
	return mcon;
}
int Character::getMintel() {
	return mintel;
}
int Character::getMwis() {
	return mwis;
}
int Character::getMchar() {
	return mchar;
}


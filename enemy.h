#pragma once
#include <iostream>
#include <string>
#include "dice.h"

using namespace std;

class Enemy {
private:
	int Hp, Speed, Level, EnemyType; //Declares variables
	int Str, Dex, Con, Int, Wis, Cha;
	string Name, Environment;

	void setType();					//Declares methods
	void setStats(int rating);

public:
	Enemy(int);
	void enemyStats();
};

Enemy::Enemy(int rating) { //Creates an enemy object
	Level = rating;
	setType();
	setStats(rating);
}

void Enemy::enemyStats() {	//Displays stats for an enemy object
	cout << "Level " << Level << ' ' << Name << endl;
	cout << "Environment: " << Environment << endl;
	cout << "Hp: " << Hp << endl;
	cout << "Speed: " << Speed << " ft" << endl;
	cout << "Str: " << Str << endl;
	cout << "Dex: " << Dex << endl;
	cout << "Con: " << Con << endl;
	cout << "Int: " << Int << endl;
	cout << "Wis: " << Wis << endl;
	cout << "Cha: " << Cha << endl;
}

void Enemy::setType() {	//Allows the user to select an enemy type
	int EnemyType;

	cout << "\nSelect an enemy type" << endl;
	cout << "(1) Giant Eagle" << endl;
	cout << "(2) Goblin" << endl;
	cout << "(3) Harpy" << endl;
	cin >> EnemyType;
	cout << endl;

	while (cin.fail() || EnemyType < 1 || EnemyType > 3) {	//checks for a valid input
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(), '\n');
		cout << "\nInvalid input!" << endl;
		cout << "Please enter 1, 2, or 3" << endl;
		cin >> EnemyType;
	}

	if (EnemyType = 1) {	//generates an enemy for choice 1
		Name = "Giant Eagle";
		Environment = "Temperate Mountains";
		Speed = 50;
		}

	else if (EnemyType = 2) {	//generates an enemy for choice 2
		Name = "Goblin";
		Environment = "Temperate plains";
		Speed = 30;
	}

	else if (EnemyType = 3) {	//generates an enemy for choice 3
		Name = "Harpy";
		Environment = "Temperate marshes";
		Speed = 50;
	}
}

void Enemy::setStats(int rating) {	//sets the stats for an enemy object
	int hp = (rating / 3) * Dice::abilityScore();	//sets intial stats
	int str = Dice::abilityScore();
	int dex = Dice::abilityScore();
	int con = Dice::abilityScore();
	int intel = Dice::abilityScore();
	int wis = Dice::abilityScore();
	int cha = Dice::abilityScore();

	int scale;

	cout << "Select a difficulty" << endl;	//allows user to choose a difficulty for the enemy
	cout << "(1) Easy" << endl;
	cout << "(2) Normal" << endl;
	cout << "(3) Hard" << endl;
	cin >> scale;

	while (cin.fail() || scale < 1 || scale > 3) {	//checks for valid user input
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			cout << "\nInvalid input!" << endl;
			cout << "Please enter 1, 2, or 3" << endl;
			cin >> scale;
	}

	if (scale = 3) {//Scales the stats up for a hard enemy
		Hp = hp + Dice::abilityScore();
		Str = str + Dice::roll(10);
		Dex = dex + Dice::roll(10);
		Con = con + Dice::roll(10);
		Int = intel + Dice::roll(10);
		Wis = wis + Dice::roll(10);
		Cha = cha + Dice::roll(10);
	}

	else if (scale = 1) {//scales the sats down for an easy enemy
		Hp = -1;
		while (Hp < 1) {
			Hp = hp - Dice::roll(10);
		}
		
		Str = -1;
		while (Str < 1) {
			Str = str - Dice::roll(10);
		}

		Dex = -1;
		while (Dex < 1) {
			Dex = dex - Dice::roll(10);
		}

		Con = -1;
		while (Con < 1) {
			Con = con - Dice::roll(10);
		}
		
		Int = -1;
		while (Int < 1) {
			Int = intel - Dice::roll(10);
		}

		Wis = -1;
		while (Wis < 1) {
			Wis = wis - Dice::roll(10);
		}

		Cha = -1;
		while (Cha < 1) {
			Cha = cha - Dice::roll(10);
		}
	}

	else if (scale = 2)	{//does not scale stats for a normal enemy
		Hp = hp;
		Str = str;
		Dex = dex;
		Con = con;
		Int = intel;
		Wis = wis;
		Cha = cha;
	}
}

void generateEncounter(int PartySize, int Level) {	//method for generating an encounter given the party's size and the sum of the party's levels
	int partySize = PartySize;
	int level = Level;
	int avgLevel = level / partySize;
	int numEnemy;
	int enemyLevel;

	cout << "\nHow many enemies would you like to generate? ";	//Allows the user to choose how many enemies to generate
	cin >> numEnemy;
	while (cin.fail() || numEnemy < 1 || numEnemy > 8) {	//Checks for valid user input
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(), '\n');
		cout << "\nInvalid input!" << endl;
		cout << "Please enter a valid number of enemies" << endl;
		cin >> numEnemy;
	}

	enemyLevel = avgLevel / numEnemy; //Calculates the levels of the enemies
	if (enemyLevel = 0) enemyLevel = 1;
	Enemy* enemy[8];	//declares an array of pointers to enemy objects

	for (int i = 0; i < numEnemy; i++) {	//fills the array with enemy objects
		cout << "Creating enemy " << i + 1 << endl;
		enemy[i] = new Enemy(enemyLevel);
	}

	cout << "\nDisplaying enemy stats for this encounter" << endl; //displays the stats for all enemies generated
	for (int i = 0; i < numEnemy; i++) {
		cout << "\nEnemy " << i + 1 << ": ";
		enemy[i]->enemyStats();
	}
}


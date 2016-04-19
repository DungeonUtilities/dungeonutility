#pragma once
#include <iostream>
#include <string>
#include "dice.h"

using namespace std;

class Enemy {
private:
	int Hp, Speed, Level, EnemyType;
	int Str, Dex, Con, Int, Wis, Cha;
	string Name, Environment;

	void setType();
	void setStats(int rating);

public:
	Enemy(int);
	void enemyStats();
};

Enemy::Enemy(int rating) {
	Level = rating;
	setType();
	setStats(rating);
}

void Enemy::enemyStats() {
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

void Enemy::setType() {
	int EnemyType;

	cout << "\nSelect an enemy type" << endl;
	cout << "(1) Giant Eagle" << endl;
	cout << "(2) Goblin" << endl;
	cout << "(3) Harpy" << endl;
	cin >> EnemyType;
	cout << endl;

	while (true) {
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			cout << "\nInvalid input!" << endl;
			cout << "Please enter 1, 2, or 3" << endl;
			cin >> EnemyType;
		}

		if (EnemyType < 1 || EnemyType > 3) {
			cin.clear();
			cout << "\nInvalid choice!" << endl;
			cout << "Please enter 1, 2, or 3" << endl;
			cin >> EnemyType;
		}

		else if (EnemyType = 1) {
			Name = "Giant Eagle";
			Environment = "Temperate Mountains";
			Speed = 50;
			break;
		}

		else if (EnemyType = 2) {
			Name = "Goblin";
			Environment = "Temperate plains";
			Speed = 30;
			break;
		}

		else if (EnemyType = 3) {
			Name = "Harpy";
			Environment = "Temperate marshes";
			Speed = 50;
			break;
		}
	}
}

void Enemy::setStats(int rating) {
	int hp = (rating / 3) * Dice::abilityScore();
	int str = Dice::abilityScore();
	int dex = Dice::abilityScore();
	int con = Dice::abilityScore();
	int intel = Dice::abilityScore();
	int wis = Dice::abilityScore();
	int cha = Dice::abilityScore();

	int scale;

	cout << "Select a difficulty" << endl;
	cout << "(1) Easy" << endl;
	cout << "(2) Normal" << endl;
	cout << "(3) Hard" << endl;
	cin >> scale;

	while (true) {
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			cout << "\nInvalid input!" << endl;
			cout << "Please enter 1, 2, or 3" << endl;
			cin >> scale;
		}

		if (scale < 1 || scale > 3) {
			cin.clear();
			cout << "\nInvalid choice!" << endl;
			cout << "Please enter 1, 2, or 3" << endl;
			cin >> EnemyType;
		}

		if (scale = 3)
		{
			Hp = hp + Dice::abilityScore();
			Str = str + Dice::abilityScore();
			Dex = dex + Dice::abilityScore();
			Con = con + Dice::abilityScore();
			Int = intel + Dice::abilityScore();
			Wis = wis + Dice::abilityScore();
			Cha = cha + Dice::abilityScore();

			break;
		}

		else if (scale = 1)
		{
			Hp = -1;
			while (Hp < 1)
			{
				Hp = hp - Dice::abilityScore();
			}

			Str = -1;
			while (Str < 1)
			{
				Str = str - Dice::abilityScore();
			}

			Dex = -1;
			while (Dex < 1)
			{
				Dex = dex - Dice::abilityScore();
			}

			Con = -1;
			while (Con < 1)
			{
				Con = con - Dice::abilityScore();
			}

			Int = -1;
			while (Int < 1)
			{
				Int = intel - Dice::abilityScore();
			}

			Wis = -1;
			while (Wis < 1)
			{
				Wis = wis - Dice::abilityScore();
			}

			Cha = -1;
			while (Cha < 1)
			{
				Cha = cha - Dice::abilityScore();
			}

			break;
		}

		else if (scale = 2)
		{
			Hp = hp;
			Str = str;
			Dex = dex;
			Con = con;
			Int = intel;
			Wis = wis;
			Cha = cha;

			break;
		}
	}
};

void generateEncounter(int PartySize, int Level) {
	int partySize = PartySize;
	int level = Level;
	int avgLevel = level / partySize;
	int numEnemy;
	int enemyLevel;

	/*cout << "How many members are in your party?" << endl;
	cin >> partySize;

	while (true) {
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			cout << "Invalid input!" << endl;
			cout << "Please enter a valid party size" << endl;
			cin >> partySize;
		}

		if (partySize < 1 || partySize > 5) {
			cin.clear();
			cout << "Invalid choice!" << endl;
			cout << "You can only have up to 5 members in your party" << endl;
			cin >> partySize;
		}

		else {
			cout << "Enter the levels of your party members" << endl;
			for (int i = 0; i < partySize; i++) {
				cout << "Member " << i + 1 << ": ";
				cin >> level;
				while (true) {
					while (cin.fail()) {
						cin.clear();
						cin.ignore(std::numeric_limits<int>::max(), '\n');
						cout << "\nInvalid input!" << endl;
						cout << "Please enter a valid player level" << endl;
						cin >> level;
					}

					if (level < 1 || level > 20) {
						cin.clear();
						cout << "\nInvalid choice!" << endl;
						cout << "Please enter a valid player level" << endl;
						cin >> level;
					}

					else break;
				}

				avgLevel += level;
			}*/

	cout << "\nHow many enemies would you like to generate? ";
	cin >> numEnemy;
	//while (true) {
	while (cin.fail() || numEnemy < 1 || numEnemy > 8) {
		cin.clear();
		cin.ignore(std::numeric_limits<int>::max(), '\n');
		cout << "\nInvalid input!" << endl;
		cout << "Please enter a valid number of enemies" << endl;
		cin >> numEnemy;
	}

				/*if (numEnemy < 1 || numEnemy > 8) {
					cin.clear();
					cin.ignore(std::numeric_limits<int>::max(), '\n');
					cout << "Invalid choice!" << endl;
					cout << "You can only generate up to 8 enemies" << endl;
					cin >> partySize;
				}*/

				
	enemyLevel = avgLevel / numEnemy;
	Enemy* enemy[8];

	for (int i = 0; i < numEnemy; i++) {
		cout << "Creating enemy " << i + 1 << endl;
		enemy[i] = new Enemy(enemyLevel);
	}

	cout << "Displaying enemy stats for this encounter" << endl;
	for (int i = 0; i < numEnemy; i++) {
		cout << "Enemy " << i + 1 << ": ";
		enemy[i]->enemyStats();
	}
}

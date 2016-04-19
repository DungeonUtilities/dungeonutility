#ifndef DICEUTILITY_ITEMS_H
#define DICEUTILITY_ITEMS_H

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Item { //Superclass from which all other items inherit
	int numItems; //all items have a specified number of items
	string itemName; //all items have a name
public:
	Item(int n, string name) {
		numItems = n;
		itemName = name;
	}
	void setNumItems(int n) {
		numItems = n;
	}
	int getNumItems() {
		return numItems;
	}
	string getItemName() {
		return itemName;
	}
	virtual string getValues() = 0; //all items have getValues(), which prints out attributes/attribute description of the item
};

class Coinage : public Item { //class for in-game currency
	int copper, silver, electrum, gold, platinum, sumCoin, valueInCopper; //D&D handbook specifies 5 different denominations of currency
public:
	Coinage(int n, string name, int c, int s, int e, int g, int p) : Item(n, name) {
		copper = c;
		silver = s;
		electrum = e;
		gold = g;
		platinum = p;
		sumCoin = copper + silver + electrum + gold + platinum;
		valueInCopper = copper + silver * 10 + electrum * 50 + gold * 100 + platinum * 1000; //in order to carry out trading, all coins are converted to lowest denomination, copper
	}
	void setValueInCopper() {
		valueInCopper = copper + silver * 10 + electrum * 50 + gold * 100 + platinum * 1000;
	}
	void setCopper(int c) {
		copper = c;
	}
	void setSilver(int s) {
		silver = s;
	}
	void setElectrum(int e) {
		electrum = e;
	}
	void setGold(int g) {
		gold = g;
	}
	void setPlatinum(int p) {
		platinum = p;
	}
	int getValueInCopper() {
		return valueInCopper;
	}
	int getCopper() {
		return copper;
	}
	int getSilver() {
		return silver;
	};
	int getElectrum() {
		return electrum;
	}
	int getGold() {
		return gold;
	}
	int getPlatinum() {
		return platinum;
	}
	string getValues() override {
		stringstream sstr;
		sstr << getNumItems() << " " << getItemName() << "\n" << "Copper: " << copper << "\n" << "Silver: " << silver << "\n" <<
			"Electrum: " << electrum << "\n" << "Gold: " << gold << "\n" <<
			"Platinum: " << platinum << "\n" << "Total value in copper: " << getValueInCopper() << "\n" << endl;
		return sstr.str();
	}
	void convertCopper() {
		if (copper >= 10) {
			if (copper >= 10 && copper < 50) {
				silver += copper / 10;
				copper = copper % 10;
			}
			if (copper >= 50 && copper < 100) {
				electrum += copper / 50;
				copper = copper % 50;
				if (copper >= 10 && copper < 50) {
					silver += copper / 10;
					copper = copper % 10;
				}
			}
			if (copper >= 100 && copper < 1000) {
				gold += copper / 100;
				copper = copper % 100;
				if (copper >= 50 && copper < 100) {
					electrum += copper / 50;
					copper = copper % 50;
				}
				if (copper >= 10 && copper < 50) {
					silver += copper / 10;
					copper = copper % 10;
				}
			}
			if (copper >= 1000) {
				platinum += copper / 1000;
				copper = copper % 1000;
				if (copper >= 100 && copper < 1000) {
					gold += copper / 100;
					copper = copper % 100;
				}
				if (copper >= 50 && copper < 100) {
					electrum += copper / 50;
					copper = copper % 50;
				}
				if (copper >= 10 && copper < 50) {
					silver += copper / 10;
					copper = copper % 10;
				}
			}
			sumCoin = copper + silver + electrum + gold + platinum;
			setNumItems(sumCoin);
		}
		else {
			cout << "Amount too low to convert" << endl;
		}
	}
	void convertSilver() {
		if (silver >= 5) {
			if (silver >= 5 && silver < 10) {
				electrum += silver / 5;
				silver = silver % 5;
			}
			if (silver >= 10 && silver < 100) {
				gold += silver / 10;
				silver = silver % 10;
				if (silver >= 5 && silver < 10) {
					electrum += silver / 5;
					silver = silver % 5;
				}
			}
			if (silver >= 100) {
				platinum += silver / 100;
				silver = silver % 100;
				if (silver >= 10 && silver < 100) {
					gold += silver / 10;
					silver = silver % 10;
				}
				if (silver >= 5 && silver < 10) {
					electrum += silver / 5;
					silver = silver % 5;
				}
			}
			sumCoin = copper + silver + electrum + gold + platinum;
			setNumItems(sumCoin);
		}
		else {
			cout << "Amount too low to convert" << endl;
		}
	}
	void convertElectrum() {
		if (electrum >= 2) {
			if (electrum >= 2 && electrum < 20) {
				gold += electrum / 2;
				electrum = electrum % 2;
			}
			if (electrum >= 20) {
				platinum += electrum / 20;
				electrum = electrum % 20;
				if (electrum >= 2 && electrum < 20) {
					gold += electrum / 2;
					electrum = electrum % 2;
				}
			}
			sumCoin = copper + silver + electrum + gold + platinum;
			setNumItems(sumCoin);
		}
		else {
			cout << "Amount too low to convert" << endl;
		}
	}
	void convertGold() {
		if (gold >= 10) {
			platinum += gold / 10;
			gold = gold % 10;
			sumCoin = copper + silver + electrum + gold + platinum;
			setNumItems(sumCoin);
		}
		else {
			cout << "Amount too low to convert" << endl;
		}
	}
};

class Armor : public Item { //class for character armor, reduces change of dealt damage
	int cost, armorClass; //armorClass is always a constant, and sometimes an added Dexterity modifier. If attack value is greater than armorClass, the attack deals damage
	double weight; //all pieces of armor have weight
	bool stealth; //if armor has disadvantage in stealth (dexterity), value is false
public:
	Armor(int n, string name, int c, int AC, bool s, double w) : Item(n, name) {
		cost = c;
		armorClass = AC;
		stealth = s;
		weight = w;
	}
	int getCost() {
		return cost;
	}
	int getArmorClass() {
		return armorClass;
	}
	bool getStealth() {
		return stealth;
	}
	double getWeight() {
		return weight;
	}
	string getValues() override {
		string truefalse;
		if (stealth) {
			truefalse = "true";
		}
		else {
			truefalse = "false";
		}
		stringstream sstr;
		sstr << getNumItems() << " " << getItemName() << "\n" << "Cost in copper: " << cost << "\n" << "Armor Class: " << armorClass << "\n" <<
			"Stealth: " << truefalse << "\n" << "Weight: " << weight << "\n" << endl;
		return sstr.str();
	}
};

class Weapon : public Item { //items that deal damage
	int cost;
	double weight; //every weapon has a weight, if strength of a character not high enough for specified weight, character cannot wield weapon
	string damage; //weapons deal specified type of damage that is also based on a specified dice roll
	bool isRanged; //if true, the weapon is ranged (thrown/uses ammo), false otherwise
public:
	Weapon(int n, string name, int c, string d, double w, bool r) : Item(n, name) {
		cost = c;
		damage = d;
		weight = w;
		isRanged = r;
	}
	int getCost() {
		return cost;
	}
	string getDamage() {
		return damage;
	}
	double getWeight() {
		return weight;
	}
	bool getRange() {
		return isRanged;
	}
	string getValues() override {
		string truefalse;
		if(isRanged) {
			truefalse = "true";
		} else {
			truefalse = "false";
		}
		stringstream sstr;
		sstr << getNumItems() << " " << getItemName() << "\n" << "Cost in copper: " << cost << "\n" << "Damage description: " << damage << "\n" <<
			"Weight: " << weight << "\n" << "Ranged: " << truefalse << "\n" << endl;
		return sstr.str();
	}
};

class Gear : public Item {
	int cost;
	double weight;
	string description;
public:
	Gear(int n, string name, int c, double w, string d) : Item(n, name) { //class for items that do not fit above categories
		cost = c;
		weight = w;
		description = d; //holds description of item
	}
	void setDescription(string d) {
		description = d;
	}
	int getCost() {
		return cost;
	}
	double getWeight() {
		return weight;
	}
	string getValues() override {
		stringstream sstr;
		sstr << getNumItems() <<" "<< getItemName() << "\n" << "Cost in copper: " << cost << "\n" << "Weight: " << weight << "\n" <<
			"Description: " << description << "\n" << endl;
		return sstr.str();
	}
};

class ItemList { //vector that holds items and allows items to be added or removed. Each character has an ItemList
	vector<Item*> itemList; //vector of Item pointers, to allow subclasses to be put in
public:
	void addItem(Item* i) { //adds items to vector
		itemList.push_back(i);
	}
	void removeItem() { //removes items from vector
		if(itemList.size() != 0) {
			itemList.pop_back();
		} else {
			cout << "There are no items in inventory." << endl;
		}
	}
	int getNumItems() { //gets the number of different items in vector
		return itemList.size();
	}
	void getValues() { //prints out all values of each item in vector
		for (int i = 0; i < itemList.size(); i++) {
			cout << itemList[i]->getValues();
		}
	}
	string getSpecificItem(string n) { //returns values of specified item (by item name) in vector
		string str;
		for (int i = 0; i < itemList.size(); i++) {
			str = itemList[i]->getItemName();
			if(str.compare(n) == 0) {
				return itemList[i]->getValues();
			}
		}
		return "Item not found";
	}
	int getArmorClass() {
		string str, itemStr;
		int n = 0;
		itemStr = itemList[1]->getValues();
		itemStr = itemStr.substr(itemStr.find(":") + 2);
		itemStr = itemStr.substr(itemStr.find(":") + 2, 2);
		if (stoi(itemStr) >= 10 && stoi(itemStr) <= 99) {
			n += stoi(itemStr);
		} else {
			n = 0;
			n += stoi(itemStr.substr(0, 1));
		}
		str = itemList[2]->getItemName();
		if(str.compare("Shield") == 0 || str.compare("Shield") == 0) {
			n += 2;
		}
		return n;
	}
	void removeSpecificItem(string n) { //removes specified item (by item name) from vector
		string str;
		for (int i = 0; i < itemList.size(); i++) {
			str = itemList[i]->getItemName();
			if (str.compare(n) == 0) {
				itemList.erase(itemList.begin()+i);
			}
		}
	}
	void orderList() {
		vector<Item*> newList;
		int counter = 0;
		string str;
		for (int i = 0; i < itemList.size(); i++) {
			str = itemList[i]->getItemName();
			if (str.compare("Coins") == 0) {
				newList.push_back(itemList[i]);
			}
		}
		for (int i = 0; i < itemList.size(); i++) {
			str = itemList[i]->getItemName();
			if (str.compare("Leather armor") == 0 || str.compare("Chain Mail") == 0 || str.compare("Scale Mail") == 0) {
				newList.push_back(itemList[i]);
			}
		}
		for (int i = 0; i < itemList.size(); i++) {
			str = itemList[i]->getItemName();
			if (str.compare("Shield") == 0 || str.compare("Shield") == 0) {
				newList.push_back(itemList[i]);
			}
		}
		for (int i = 0; i < itemList.size(); i++) {
			str = itemList[i]->getItemName();
			if (str.compare("Coins") != 0 && str.compare("Leather armor") != 0 && str.compare("Chain Mail") != 0 && str.compare("Scale Mail") != 0 && str.compare("Shield") != 0 && str.compare("Shield") != 0) {
				newList.push_back(itemList[i]);
			}
		}
		itemList.swap(newList);
	}
	void saveFile(string n) { //saves string of getValues() to text file "DDsave.txt"
		ofstream save(n + "_inventory.txt");
		string str;
		for(int i = 0; i < itemList.size(); i++) {
			str += itemList[i]->getValues();
		}
		save << str;
		save.close();
	}
	void openFile(string n) { //reads "DDsave.txt" and creates specific item objects based off item names in file
		ifstream open(n+"_inventory.txt");
		int counter = 1, numItems=0;
		string string, name, var1 = "", var2 = "", var3 = "", var4 = "", var5 = "", var6 = "";
		bool truefalse = false;
		while(getline(open,string)) {
			if(counter==1) {
				numItems = stoi(string.substr(0, string.find(" ")));
				string = string.substr(string.find(" ") + 1);
				name = string;
			}
			string = string.substr(string.find(":") + 1);
			string = string.substr(string.find(" ") + 1);
			if(counter == 2) {
				var1 = string;
			}
			if (counter == 3) {
				var2 = string;
			}
			if (counter == 4) {
				var3 = string;
			}
			if (counter == 5) {
				var4 = string;
			}
			if (counter == 6) {
				var5 = string;
			}
			if (counter == 7) {
				var6 = string;
			}
			counter++;
			if(string.compare("") == 0) {
				if(!var6.empty()) {
					addItem(new Coinage(numItems, name, stoi(var1), stoi(var2), stoi(var3), stoi(var4), stoi(var5)));
				}
				if(var5.empty() && (!var4.empty())) {
					if(var3.compare("true") == 0 || var3.compare("false") == 0) {
						if(var3.compare("true") == 0) {
							truefalse = true;
						}else {
							truefalse = false;
						}
						addItem(new Armor(numItems, name, stoi(var1), stoi(var2), truefalse, stod(var4)));
					}else {
						if (var4.compare("true") == 0) {
							truefalse = true;
						}
						else {
							truefalse = false;
						}
						addItem(new Weapon(numItems, name, stoi(var1), var2, stod(var3), truefalse));
					}
				}
				if(var4.empty() && var5.empty() && var6.empty()) {
					addItem(new Gear(numItems,name,stoi(var1),stod(var2),var3));
				}
				counter = 1;
				var1 = ""; var2 = ""; var3 = ""; var4 = ""; var5 = ""; var6 = "";
			}
		}
		open.close();
	}
};

#endif
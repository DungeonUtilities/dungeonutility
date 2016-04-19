//
// Created by k on 3/1/16.
//edited by perry 3/4/16
//

#ifndef DUNGEONUTILITY_DICE_H
#define DUNGEONUTILITY_DICE_H

#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Dice{

private:
public:
    static int roll(int sides);     //Generates random number between 1 and 'sides.'
    static int* rollMore(int times, int sides);     //Generates 'times' random numbers between 1 and 'sides.'
    static int abilityScore();      //Generates standard ability scores using 4d6 drop the lowest roll method.
    static int* att(int bonus);       //Attack roll with d20 (alerts if 1 or 20), adds 'bonus' to roll.
    static void parseAndRoll(string s);
    static void typeRoll();
};

int Dice::roll(int sides) {
    int check = rand();
    //std::cout << check << std::endl;
    if(check == 1804289383){srand((unsigned int) time(NULL));} //Checks for default rand() seed and reseeds.
    int result = ((rand() % sides) + 1);
    if (result < 0) {result = result * -1;}
    return result;
}

int* Dice::rollMore(int times, int sides){
    int* results = new int[times];
    for(int i = 0; i < times; i++){
        results[i] = roll(sides);
    }
    return results;
}

int Dice::abilityScore() {
    int* fourD6 = Dice::rollMore(4, 6); //create initial array of 4d6
    int lowest, score;      //track lowest roll, and total score
    lowest = fourD6[0];     //first roll is arbitrary 'lowest'
    score = lowest;     //will skip fourD6[0]
    for(int i = 1; i < 4; i++){
        score = score + fourD6[i];
        if(fourD6[i] < lowest){lowest = fourD6[i];}
    }
    score = score - lowest;
    delete(fourD6);
    return score;
}

int* Dice::att(int bonus) {
    int att[3] = {0,0,0};     //att[0] stores the attack roll, att[1] indicates crit/fumble, att[2] is roll + bonus
    att[0] = roll(20);
    if(att[0] == 1){att[1] = -1;}    //att[1] is -1 if attack roll is a fumble (rolls 1)
    else if (att[0] == 20){att[1] = 1;}    //att[1] is 1 if attack roll is a crit (rolls 20)
    att[2] = att[0] + bonus;      //att[2] is total attack roll -- roll + bonus
    return att;
}

//method to parse a string, validate it, and output dice rolls based on the input.
void Dice::parseAndRoll(string s){
    string instruct = "Enter dice in the format: 1d20+5";
    string digits = "0123456789";
    string operators = "d+-";

    int num, sides, bonus;
    string pnum, psides, pbonus = "";

    //check for improper formatting
    size_t error = s.find_first_not_of(digits + operators);  //check for wrong characters
    if(error != string::npos){cout << instruct << endl; return;}

    size_t dSpot = s.find_first_of("d");  //find the d
    if(dSpot == string::npos){cout << instruct << endl; return;}

    size_t dSpot_error = s.find_first_of("d", dSpot+1);
    if(dSpot_error != string::npos){cout << instruct << endl; return;}

    size_t digitSpot = s.find_first_of(digits); //make sure the start is 0
    if(digitSpot != 0){cout << instruct << endl; return;}
    digitSpot = s.find_first_of(digits, dSpot); //check that digits follow the d
    if(digitSpot == string::npos){cout << instruct << endl; return;}

    size_t bonusSpot = s.find_first_of("+-");
    size_t bonusSpot_error = s.find_first_of("+-", bonusSpot+1); //ensure there is not multiple + or -
    if(bonusSpot_error != string::npos){cout << instruct << endl; return;}
    if(bonusSpot != string::npos && digitSpot > bonusSpot){cout << instruct << endl; return;}

    pnum = s.substr(0, dSpot);

    if(bonusSpot != string::npos){ //if there is a bonus assign values to bonus and sides
        psides = s.substr(dSpot+1, bonusSpot - dSpot - 1);
        pbonus = s.substr(bonusSpot, s.length() - bonusSpot);
    }
    else{psides = s.substr(dSpot+1, s.length() - dSpot+1); pbonus = "0";}

    num = stoi(pnum, nullptr);
    sides = stoi(psides, nullptr);
    bonus = stoi(pbonus, nullptr);

    if(bonus > 9000){
        for(int i = 0; i < 9001; i++){cout << "GOKU" << ends;}
        return;
    }

    cout << num << "d" << sides << ": " << ends; //roll using assigned values and output
    int* roll = Dice::rollMore(num,sides);
    int total = 0;
    for(int i = 0; i < num; i++){total += roll[i]; cout << "[" << roll[i] << "]" << "+" << ends; if((i+1) % 15 == 0){cout << endl;}}
    total += bonus;

    cout << bonus << " = " << total << endl;
}

//menu for parseAndRoll
//Calls parseAndRoll for validation
//formats dice results to display each roll and add bonus on the end
void Dice::typeRoll(){
    string line;
    string instruct = "Roll (eg. 1d6+10). Type 'exit' to end: ";

    cout << "Roll [number of dice]d[number of sides]+/-[bonus] (eg. 1d6+10). Type 'exit' to end: " << ends;
    while(getline(cin, line)){
        if(line.compare("exit") == 0){return;}
        else(Dice::parseAndRoll(line));
        cout << instruct << ends;
    }
}

#endif //DUNGEONUTILITY_DICE_H

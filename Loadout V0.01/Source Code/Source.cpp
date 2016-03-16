// Made by "Tacobandit"
// 02 February 2016

///////////////////////////////////////////////////////////////////
// First attempt at creating a save editing UI for Nuclear Throne//
// This first prototype has a totally text based UI              //
// After proving it can work solidly, a graphical                //
// UI will be created											 //
///////////////////////////////////////////////////////////////////

// Ignore the fruit names, I like naming things after fruit :D

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void editValue(ifstream &reader, string name) {
	cout << "Enter the number of the weapon you wish to replace. Refer to the NT weapon guide." << endl;
	string weapon;
	cin >> weapon;
	ofstream newSave("nuclearthrone.sav", ios::out); // Creates a nuclearthrone save file
	string core;
	string pit = "\"charData_" + name + "\":"; // The character info we want to edit
	string relish = "\"cgld\": "; // 8 length
	getline(reader, core); // core holds the entire save file
	string fruitbasket = core; // fruitbasket will eventually be the new save file
	std::size_t kiwi = core.find(pit); // kiwi is the character location of the start of the character info we are looking for
	std::size_t finder; // This finds the first "cgld" value in the string
	unsigned int position = 0; // This will hold the "cgld" position for the character we want
	while (kiwi > position) {
		finder = core.find(relish);
		if (finder != std::string::npos) {
			if (kiwi > position) {
				if (finder == 0) {
					position += 8;
					core = core.substr(finder+8, core.length() + 1);
				}
				else {
					position += finder;
					core = core.substr(finder, core.length() + 1);
				}
			}
			else {
				position += finder;
			}
		}
	}
	string replacement = relish + weapon + "."; // eg "cgld": 100.
	while (replacement.length() < 17) { // appends extra 0's for simplicity's sake
		replacement += "0";
	}
	replacement += ",";
	fruitbasket.replace(position, 18, replacement);
	newSave << fruitbasket; // new save file created
}

void displayFile(fstream &reader) { // I don't remember where I was going with this
	string output;
	while (!reader.eof()) {
		getline(reader, output);
		cout << output;
	}
}

int main() {
	ifstream reader; // This reads the old save file
	if (reader) {
		string charSelect; // Stores the number that represents the character
		cout << "Hello. What character would you like to edit?\n\n";
		cout << "1 - fish\n2 - crystal\n3 - eyes\n4 - melting\n5 - plant\n6 - YV\n7 - Steroids\n" <<
			"8 - robot\n9 - chicken\n10 - rebel\n11 - horror\n12 - rogue\n";
		cin >> charSelect;
		cin.ignore(); // Ignores the enter key input
		reader.open("oldSave.sav", ios::in);
 		editValue(reader, charSelect);
		reader.close();
		//displayFile(reader);
		return 0;
	}
	else {
		cout << "Error! File not opened successfully!";
		int holdup;
		cin >> holdup;
	}
	return 0;
}

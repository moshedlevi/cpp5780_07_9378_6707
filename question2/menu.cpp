/*
   File: menu.cpp
   Description: this is implement file of enum for menu options
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include<iostream>
#include<iomanip>
#include"menu.h"

using namespace std;

MenuOption operator++(MenuOption& rhs) {
	rhs = MenuOption(int(rhs) + 1);
	return rhs;
}

const char* MenuOptionLine[LAST_MENU_OPTION + 1] {
	"Exit",
	"Add Student to file",
	"Delete Student from file",
	"Print info for student"
	"Check registration for student",
	"Set registration for student",
	"Print list all registered students",
	"Print students list for course",
	"Combine 2 list to new list"
};

istream& operator>>(istream& in, MenuOption& rhs) {
	int value;
	in >> value;
	rhs = MenuOption(value);
	return in;
}

ostream& operator<<(ostream& out, MenuOption rhs) {
	out << setw(4) << int(rhs) << "\t--\t" << MenuOptionLine[rhs];
	return out;
}

MenuOption menu() {
	MenuOption chosen;

	cout << endl << "Menu options:" << endl << endl;

	for (chosen = FIRST_MENU_OPTION; chosen <= LAST_MENU_OPTION; ++chosen)
		cout << chosen << endl;
	cout << endl;

	cout << "Please choose a menu option: ";
	cin >> chosen;
	return chosen;
}
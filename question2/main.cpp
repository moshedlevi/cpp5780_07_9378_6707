/*
   File: main.cpp
   Description: this is main program file for test RoundList class
   Course: 150018 C++ Workshop
   Exercise 6, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include <iostream>
#include "ManageStudents.h"
#include "menu.h"


using namespace std;

int main() {
	ManageStudents ms1;
	MenuOption choice;
	Student s;

	try {
		ms1.setFileName("elul.dat");
	}
	catch (...) {
		cout << "ERROR";
	}

	while ((choice = menu()) != EXIT) {
		int num;
		switch (choice) {
		case ADD:
			{
			uint sid;
			string lastName, firstName;

			cout << "Enter student id: ";
			cin >> sid;
			cout << "Enter student last name: ";
			cin >> lastName;
			cout << "Enter student first name: ";
			cin >> firstName;

			s.setInfo(sid, lastName, firstName);

			try
			{
				ms1.addStudent(s);
			}
			catch (const char* err)
			{
				cout << err;
			}

			if (!(ms1))
				cout << "add student faild!" << endl;
			}
			break;

		case PRINT_ALL_REG:

			ms1.printRegStudents();
			break;

		default:
			cout << "ERROR!" << endl;
		}
	}
	return 0;
}


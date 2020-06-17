/*
   File: main.cpp
   Description: this is main program file for test manage file of students
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include <iostream>
#include "ManageStudents.h"
#include "menu.h"


using namespace std;

int main() {
	ManageStudents ms1, ms2;
	MenuOption choice;

	while ((choice = menu()) != EXIT) {
		switch (choice) {
		case OPEN:
			{
			string filename;

			cout << "enter filename for managment file: ";
			cin >> filename;

			ms1.setFileName(filename);

			if (!(ms1)) {
				char answer;
				cout << "file '" << filename << "' not exist!" << endl <<
					"do you want to create new file with this name? (y\\n) ";
				cin >> answer;

				if ((answer == 'y') || (answer == 'Y')) {
					try {
						createStudentsFile(filename);
						cout << "file '" << filename << "' created succeed!";

						ms1.setFileName(filename);

						if (!ms1)
							cout << "cannot open file '" << filename << "' to manage!" << endl;
						else 
							cout << "file '" << filename << "' is open and ready to manage!" << endl;
					}
					catch (const char* err) {
						cout << "cannot create file '" << filename <<"'!" << endl << err;
					}
					
				}
				
			}
			else {
				cout << "file '" << filename << "' is open and ready to manage!" << endl;
			}
			}
			break;
		case ADD:
			{
			uint sid;
			string lastName, firstName;
			Student s;

			cout << "Enter student id to add: " ;
			cin >> sid;
			cout << "Enter student last name: ";
			cin >> lastName;
			cout << "Enter student first name: ";
			cin >> firstName;

			s.setInfo(sid, lastName, firstName);

			ms1 << s;

			if (!(ms1))
				cout << "add student " << sid << " failed!" << endl;

			}
			break;
		case DELETE:
			{
			uint sid;
			cout << "Enter student id to delete: ";
			cin >> sid;

			ms1.delStudent(sid);

			if (!(ms1))
				cout << "delete student " << sid << " failed!" << endl;

			}
			break;

		case PRINT_INFO:
			{
				uint sid;

				cout << "Enter student id to print information:" ;
				cin >> sid;

				ms1.printStudent(sid);

				if (!(ms1))
					cout << "check information for student " << sid << " failed!" << endl;
			}
			break;

		case CHECK_REG:
			{
			uint sid, courseid;
			bool check;

			cout << "Enter student id to check registeration:";
			cin >> sid;

			cout << "Enter course id:";
			cin >> courseid;

			check = ms1.checkStudent(sid, courseid);

			if (!(ms1))
				cout << "check registeration for student " << sid << " to course " << courseid << " failed!" << endl;
			else
				cout << "student " << sid << " is " << (check ? "" : "NOT ") << "REGISTER to course " << courseid << "!" << endl;

			}
			break;

		case SET_REG:
		case SET_UNREG:
			{
			uint sid, courseid;
			cout << "Enter student id to " << (choice == SET_REG ? "" : "un") << "register:";
			cin >> sid;

			cout << "Enter course id:";
			cin >> courseid;

			ms1.regStudent(sid, courseid, (choice == SET_REG ? true : false));

			if (!(ms1))
				cout << "register student " << sid << " to course " << courseid << " failed!" << endl;

			}

			break;
		case PRINT_REG_COURSE:
			{
				uint courseid;
				cout << "Enter course id to print list" << endl << "(insert 0 to print all reg students)";
				cin >> courseid;

				ms1.printRegStudents(courseid);

				if (!(ms1))
					cout << "print students list for course " << courseid << " failed!" << endl;

			}

			break;
		case PRINT_ALL_REG:

			ms1.printRegStudents();

			if (!(ms1))
				cout << "print all registraion students list failed!" << endl;

			break;

		default:
			cout << "ERROR!" << endl;
		}
	}
	return 0;
}


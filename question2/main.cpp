/*
   File: main.cpp
   Description: this is main program file for test manage file of students
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include <iostream>
#include <iomanip> 
#include "ManageStudents.h"
#include "menu.h"

using namespace std;

int main() {
	ManageStudents ms1, ms2, ms3;
	MenuOption choice;

	// set temp filling char
	char prev;
	prev = cout.fill(static_cast<char>(205));

	// print alert in top of program
	cout << static_cast<char>(201) << setw(54) << "" << static_cast<char>(187) << endl
		<< static_cast<char>(186) << "      you MUST start with option 1 to open file!      " << static_cast<char>(186) << endl
		<< static_cast<char>(200) << setw(54) << "" << static_cast<char>(188) << endl;
	
	// return the default filling char
	cout.fill(prev);

	// loop of menu
	while ((choice =  menu()) != EXIT) {
		switch (choice) {
		// case set file to open
		case OPEN:
			{
			string filename;
			// get filename from user
			cout << "enter filename for managment file: ";
			cin >> filename;

			ms1.setFileName(filename);

			// if error while open file
			if (!(ms1)) {
				// ask for create new file with this name
				char answer;
				cout << "file '" << filename << "' not exist!" << endl <<
					"do you want to create new file with this name? (y\\n) ";
				cin >> answer;

				// if user want to create new file
				if ((answer == 'y') || (answer == 'Y')) {
					try {
						// create template file
						createStudentsFile(filename);
						cout << "file '" << filename << "' created succeed!" << endl;
						
						ms1.setFileName(filename);

						// check if file is open successfully
						if (!ms1)
							cout << "cannot open file '" << filename << "' to manage!" << endl;
						else 
							cout << "file '" << filename << "' is open and ready to manage!" << endl;
					}
					// if error while creating file
					catch (const char* err) {
						cout << "cannot create file '" << filename <<"'!" << endl << err;
					}
				}
			}
			// if succeed set file and open
			else {
				cout << "file '" << filename << "' is open and ready to manage!" << endl;
			}
			}
			break;
		// show filename of current name
		case CURRENT_FILE:
			// check if open file
			if (ms1.getFilename() != "")
				cout << "current file is: '" << ms1.getFilename() << "'" << endl;
			else
				cout << "still file not open." << endl;

			break;
		// add student to current file
		case ADD:
			{
			uint sid;
			string lastName, firstName;
			Student s;

			// collect data from user
			cout << "Enter student id to add: " ;
			cin >> sid;
			cout << "Enter student last name: ";
			cin >> lastName;
			cout << "Enter student first name: ";
			cin >> firstName;

			s.setInfo(sid, lastName, firstName);

			ms1 << s;

			// check if add student to file
			if (!(ms1))
				cout << "add student " << sid << " failed!" << endl;

			}
			break;
		// delete student from file
		case DELETE:
			{
			uint sid;
			cout << "Enter student id to delete: ";
			cin >> sid;

			ms1.delStudent(sid);

			// if delete student failed
			if (!(ms1))
				cout << "delete student " << sid << " failed!" << endl;

			}
			break;
		// print info fpr student
		case PRINT_INFO:
			{
				uint sid;

				cout << "Enter student id to print information: " ;
				cin >> sid;

				ms1.printStudent(sid);

				// check if print info failed
				if (!(ms1))
					cout << "check information for student " << sid << " failed!" << endl;
			}
			break;
		// check registraion of student for course
		case CHECK_REG:
			{
			uint sid, courseid;
			bool check;

			cout << "Enter student id to check registeration: ";
			cin >> sid;

			cout << "Enter course id: ";
			cin >> courseid;

			check = ms1.checkStudent(sid, courseid);

			// return value to user
			if (!(ms1))
				cout << "check registeration for student " << sid << " to course " << courseid << " failed!" << endl;
			else
				cout << "student " << sid << " is " << (check ? "" : "NOT ") << "REGISTER to course " << courseid << "!" << endl;

			}
			break;
		// set register or unregister student for course
		case SET_REG:
		case SET_UNREG:
			{
			uint sid, courseid;
			cout << "Enter student id to " << (choice == SET_REG ? "" : "un") << "register: ";
			cin >> sid;

			cout << "Enter course id: ";
			cin >> courseid;

			ms1.regStudent(sid, courseid, (choice == SET_REG ? true : false));

			// check if registraion failed
			if (!(ms1))
				cout << "register student " << sid << " to course " << courseid << " failed!" << endl;

			}

			break;

		// print list of registered student for course
		case PRINT_REG_COURSE:
			{
				uint courseid;
				cout << "Enter course id to print list" << endl << "(insert 0 to print all reg students): ";
				cin >> courseid;

				ms1.printRegStudents(courseid);

				if (!(ms1))
					cout << "print students list for course " << courseid << " failed!" << endl;

			}

			break;

		// print list of all registered students for all courses
		case PRINT_ALL_REG:

			ms1.printRegStudents();

			if (!(ms1))
				cout << "print all registraion students list failed!" << endl;

			break;
		// combine current file with other given by user
		case COMBINE_FILES:
			{
			string filename;
			// collect other filename from user
			cout << "combine current open file '" << ms1.getFilename() << "' with," << endl << 
				"enter name for second manage file: ";
			cin >> filename;

			// set other file
			ms2.setFileName(filename);
			
			// combine files to new
			ms3 = ms1 + ms2;

			// check if new file is combined ok
			if (!ms3)
				cout << "combine files failed!" << endl;
			else
				cout << "combine succeed. name of the new file '" << ms3.getFilename() << "'!" << endl;
			}
			break;

		default:
			cout << "ERROR!" << endl;
		}
	}
	return 0;
}


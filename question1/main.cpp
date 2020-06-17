/*
   File: main.cpp
   Description: this is the main program to test create and read Students file
   Course: 150018 C++ Workshop
   Exercise 7, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include "Student.h"
#include "File.h"

using namespace std;

int main() {
	string newFileName;

	// get file name from user
	cout << "insert name for new file: ";
	cin >> newFileName;


	try {
		// create new file with given name
		createStudentsFile(newFileName);
		cout << "create file is complete!" << endl;
	}
	catch (const char* err) {
		cout << err << endl;
	}

	try {
		// read from file to check if file is OK
		readStudentsFile(newFileName);
		cout << "Reading from student file is complete!" << endl;
	}
	catch (const char* err) {
		cout << err << endl;
	}	
	
	return 0;
}

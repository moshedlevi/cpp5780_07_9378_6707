/*
   File: Student.cpp
   Description: this is implement file of function for struct Student
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/


#include "Student.h"
using namespace std;

// init static field to empty student
Student const Student::_emptyStudent;

fstream& operator<<(fstream& out,const Student& s)
{
	out.write((char*)&s, sizeof(s));
	return out;
}

ostream& operator<<(ostream& out, const Student& s)
{
	cout << "ID: " << s._id << endl;
	cout << "Last name: " << s._lastName << endl;
	cout << "First name: " << s._firstName << endl;
	cout << "Course 1: " << s._course1 << endl;
	cout << "Course 2: " << s._course2 << endl;
	cout << "Course 3: " << s._course3 << endl;
	cout << "Course 4: " << s._course4 << endl;
	cout << "Course 5: " << s._course5 << endl;

	return out;
}

fstream& operator>>(fstream& in, Student& s)
{
	in.read((char*)&s, sizeof(s));
	return in;
}

void Student::setInfo(const uint id, const std::string lastName, const std::string firstName)
{
	_id = id;
	strcpy(_lastName, lastName.substr(0, 20).c_str());
	strcpy(_firstName, firstName.substr(0, 20).c_str());
}

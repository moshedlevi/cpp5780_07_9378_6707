
#include "Student.h"
using namespace std;

fstream& operator<<(fstream& out,const Student& s)
{
	out.write((char*)&s._id, sizeof(s._id));
	out.write(s._lastName.c_str(),21);
	out.write(s._firstName.c_str(),21);
	out << s._course1;
	out << s._course2;
	out << s._course3;
	out << s._course4;
	out << s._course5;
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
	char* readData = new char[21];
	in.read((char*)&s._id, sizeof(s._id));
	in.read(readData,21);
	s._lastName = readData;
	in.read(readData, 21);
	s._firstName = readData;
	in >> s._course1;
	in >> s._course2;
	in >> s._course3;
	in >> s._course4;
	in >> s._course5;
	return in;
}

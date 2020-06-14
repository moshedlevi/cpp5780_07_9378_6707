

#include "Student.h"
#include "File.h"

using namespace std;

void main() {
	string newFileName;
	cout << "insert name for nre file:" << endl;
	cin >> newFileName;
	try {
		createStudentsFile(newFileName);
	}
	catch (void* err) {
		cout << err;
	}

	cout << "create file is complete!" << endl;

	readStudentsFile(newFileName);

	return;
}



#include "ManageStudents.h"

ManageStudents::ManageStudents(const std::string fileName) {
	_lastOperSucc = false;
	_filePtr = new std::fstream;
	_filePtr->open(fileName, std::ios::in | std::ios::binary);

	if (!(_filePtr)) {
		delete _filePtr;
		_filePtr = nullptr;
		throw "cannot open file!";
	}

	_fileExist = true;
	_filename = fileName;
	_filePtr->read((char*)_maxStudent, sizeof(_maxStudent));

	if (!(_filePtr)) {
		delete _filePtr;
		_filePtr = nullptr;
		throw "cannot read from file!";
	}

	_lastOperSucc = true;
	_filePtr->close();
}

ManageStudents::~ManageStudents() {
	if (_filePtr == nullptr)
		return;

	if (_filePtr->is_open())
		_filePtr->close();

	delete _filePtr;
	_filePtr = nullptr;
}

ManageStudents::ManageStudents(ManageStudents&& other) {
	_filename = other._filename;
	_fileExist = other._fileExist;
	_maxStudent = other._maxStudent;
	_filePtr = other._filePtr;
	_lastOperSucc = true;

	other._filename = nullptr;
	other._filePtr = nullptr;
}

ManageStudents& ManageStudents::operator = (ManageStudents&& other) {
	_filename = other._filename;
	_fileExist = other._fileExist;
	_maxStudent = other._maxStudent;
	_filePtr = other._filePtr;
	_lastOperSucc = true;

	other._filename = nullptr;
	other._filePtr = nullptr;

	return *this;
}

void ManageStudents::setFileName(const std::string fileName){
	_lastOperSucc = false;
	_filePtr = new std::fstream;
	_filePtr->open(fileName, std::ios::in | std::ios::binary);

	if (!(_filePtr)) {
		delete _filePtr;
		_filePtr = nullptr;
		throw "cannot open file!";
	}

	_fileExist = true;
	_filename = fileName;
	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));

	if (!(_filePtr)) {
		throw "cannot read from file!";
	}

	_lastOperSucc = true;
	_filePtr->close();
}

void ManageStudents::addStudent(const Student& s) {
	openFile();

	if (s._id > 999)
		throw "student id overflow!";

	uint i = 0;
	Student tmpS;

	while (_filePtr) {
		*(_filePtr) >> tmpS;
		if (_filePtr) {
			++i;

			if ((i == s._id) && (tmpS._id == 0)) {
				*(_filePtr) << s;

				if (!(_filePtr))
					throw "Can't write to file";
				else
					_lastOperSucc = true;
			}
		}
	}

	if (i < s._id) {
		try {
			for (i; i < s._id - 1; ++i)
				*(_filePtr) << s._emptyStudent;

			*(_filePtr) << s;
			_lastOperSucc = true;

		} catch (void * err) {
			throw "Can't write to file";
		}

	}

	_filePtr->close();
}

void ManageStudents::delStudent(const uint sid) {
}

void ManageStudents::regStudent(const uint sid, const uint courseid) {
}

bool ManageStudents::checkStudent(const uint sid, const uint courseid) {
	return false;
}

void ManageStudents::printStudent(const uint sid) {

}

void ManageStudents::printRegStudents(const uint courseid) {
	if (courseid > 5)
		throw "Course id not valid!";

	openFile();

	Student tmpS;

	while (_filePtr) {
		*(_filePtr) >> tmpS;
		if (_filePtr) {
			if (tmpS._id > 0) {
				switch (courseid) {
				case 0:
					if ((tmpS._course1 == 'Y') || (tmpS._course2 == 'Y') ||
						(tmpS._course3 == 'Y') || (tmpS._course4 == 'Y') ||
						(tmpS._course5 == 'Y'))
						std::cout << tmpS;
					break;
				case 1:
					if (tmpS._course1 == 'Y')
						std::cout << tmpS;
					break;
				case 2:
					if (tmpS._course2 == 'Y')
						std::cout << tmpS;
					break;
				case 3:
					if (tmpS._course3 == 'Y')
						std::cout << tmpS;
					break;
				case 4:
					if (tmpS._course4 == 'Y')
						std::cout << tmpS;
					break;
				case 5:
					if (tmpS._course5 == 'Y')
						std::cout << tmpS;
					break;
				}
			}
		}
	}

	_filePtr->close();

}

bool ManageStudents::operator !() const {
	return _lastOperSucc;
}

ManageStudents ManageStudents::operator +(const ManageStudents&) const {
	ManageStudents ms;
	return ms;
}

void ManageStudents::openFile()
{
	if (!(_fileExist))
		throw "file not exist!";

	_lastOperSucc = false;
	_filePtr->open(_filename, std::ios::in | std::ios::out | std::ios::binary);

	if (!(_filePtr)) {
		throw "cannot open file!";
	}

	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));
	if (!(_filePtr)) {
		throw "cannot read from file!";
	}
}


ManageStudents& operator << (ManageStudents& in, const Student& s) {
	in.addStudent(s);
	return in;
}


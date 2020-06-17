

#include "ManageStudents.h"

ManageStudents::ManageStudents(const std::string fileName) {
	_lastOperFail = true;
	_filePtr = new std::fstream;
	_filePtr->open(fileName, std::ios::in | std::ios::binary);

	if (!*_filePtr) {
		delete _filePtr;
		_filePtr = nullptr;
return;
	}

	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));

	if (!*_filePtr) {
		_filePtr->close();
		delete _filePtr;
		_filePtr = nullptr;
		return;
	}

	_filename = fileName;

	_lastOperFail = false;
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
	_lastOperFail = true;
	_filename = other._filename;
	_maxStudent = other._maxStudent;
	_filePtr = other._filePtr;

	if ((_filename == other._filename) && (_maxStudent == other._maxStudent) && 
		(_filePtr == other._filePtr) && !other._lastOperFail)
		_lastOperFail = false;

	other._filename = "";
	other._filePtr = nullptr;
}

ManageStudents& ManageStudents::operator = (ManageStudents&& other) {
	_lastOperFail = true;
	_filename = other._filename;
	_maxStudent = other._maxStudent;
	_filePtr = other._filePtr;

	if ((_filename == other._filename) && (_maxStudent == other._maxStudent) &&
		(_filePtr == other._filePtr) && !other._lastOperFail)
		_lastOperFail = false;

	other._filename = "";
	other._filePtr = nullptr;

	return *this;
}

void ManageStudents::setFileName(const std::string fileName) {
	_lastOperFail = true;

	if (fileName == _filename) {
		_lastOperFail = false;
		return;
	}

	if (_filePtr != nullptr) {
		_filePtr->close();
		delete _filePtr;
		_filePtr = nullptr;
		_filename = "";
	}

	_filePtr = new std::fstream;
	_filePtr->open(fileName, std::ios::in | std::ios::binary);

	if (!*_filePtr) {
		delete _filePtr;
		_filePtr = nullptr;
		return;
	}

	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));

	if (!*_filePtr) {
		_filename = "";
		_filePtr->close();
		delete _filePtr;
		_filePtr = nullptr;
		return;
	}

	_filename = fileName;

	_lastOperFail = false;
	_filePtr->close();
}

void ManageStudents::addStudent(const Student& s) {

	_lastOperFail = true;

	if ((s._id > 999) || (s._id == 0))
		return;

	if (!(openFile()))
		return;

	if (s._id > _maxStudent) {
		_filePtr->seekg(0,std::ios::end);

		for (uint i = (_maxStudent + 1); (i < s._id); ++i) {
			*(_filePtr) << Student::_emptyStudent;
		}

		if (!*_filePtr)
			goto close_file;

		*(_filePtr) << s;

		_maxStudent = s._id;

		_filePtr->seekg(0);
		_filePtr->write((char*)&_maxStudent, sizeof(_maxStudent));

		if (!*_filePtr)
			goto close_file;

	}
	else {
		Student tmp;
		if (!readStudent(s._id, tmp))
			goto close_file;

		if (tmp._id != 0)
			goto close_file;

		*(_filePtr) << s;

		if (!*_filePtr)
			goto close_file;
	}

	_lastOperFail = false;

close_file:
	_filePtr->close();
}

void ManageStudents::delStudent(const uint sid) {
	_lastOperFail = true;

	if ((sid > _maxStudent) || (sid == 0))
		return;

	if (!openFile())
		return;

	Student tmp;
	if (!readStudent(sid, tmp))
		goto close_file;

	if (sid != tmp._id)
		goto close_file;

	*(_filePtr) << Student::_emptyStudent;

	if (!*_filePtr)
		goto close_file;

	_lastOperFail = false;

close_file:
	_filePtr->close();
}

void ManageStudents::regStudent(const uint sid, const uint courseid, const bool reg) {
	_lastOperFail = true;

	if ((courseid > 5) || (courseid == 0))
		return;

	if ((sid > _maxStudent) || (sid == 0))
		return;

	if (!openFile())
		return;

	char* course = nullptr;
	Student tmp;

	if (!readStudent(sid, tmp))
		goto close_file;

	if (sid != tmp._id)
		goto close_file;

	switch (courseid) {
		case 1:
			course = &(tmp._course1);
			break;
		case 2:
			course = &(tmp._course2);
			break;
		case 3:
			course = &(tmp._course3);
			break;
		case 4:
			course = &(tmp._course4);
			break;
		case 5:
			course = &(tmp._course5);
			break;
	}

	if ((reg && *course == 'Y') || (!reg && *course == 'N'))
		goto close_file;

	*course = (reg ? 'Y' : 'N');

	*(_filePtr) << tmp;

	if (!*_filePtr)
		goto close_file;

	_lastOperFail = false;

close_file:
	_filePtr->close();
}

bool ManageStudents::checkStudent(const uint sid, const uint courseid) {
	_lastOperFail = true;

	if ((courseid > 5) || (courseid == 0))
		return false;

	if ((sid > _maxStudent) || (sid == 0))
		return false;

	if (!openFile())
		return false;

	char* course = nullptr;
	Student tmp;

	if (!readStudent(sid, tmp))
		goto close_file;

	if (sid != tmp._id)
		goto close_file;

	switch (courseid) {
		case 1:
			course = &(tmp._course1);
			break;
		case 2:
			course = &(tmp._course2);
			break;
		case 3:
			course = &(tmp._course3);
			break;
		case 4:
			course = &(tmp._course4);
			break;
		case 5:
			course = &(tmp._course5);
			break;
	}

	_lastOperFail = false;

	_filePtr->close();
	return *course == 'Y';

close_file:
	_filePtr->close();
	return false;
}

void ManageStudents::printStudent(const uint sid) {
	_lastOperFail = true;

	if ((sid > _maxStudent) || (sid == 0))
		return;

	if (!openFile())
		return;

	Student tmp;

	if (!readStudent(sid, tmp))
		goto close_file;

	if (sid != tmp._id)
		goto close_file;

	std::cout << tmp;
	_lastOperFail = false;

close_file:
	_filePtr->close();
}

std::string ManageStudents::getFilename() const {
	return _filename;
}

void ManageStudents::printRegStudents(const uint courseid) {
	_lastOperFail = true;

	if (courseid > 5)
		return;

	if (!openFile())
		return;

	bool reg;
	Student s;
	for (uint i = 1; i <= _maxStudent; ++i) {
		if (!readStudent(i, s))
			goto close_file;

		reg = false;
		switch (courseid) {
			case 0:
				reg = ((s._course1 == 'Y') || (s._course2 == 'Y') || (s._course3 == 'Y') || 
					(s._course4 == 'Y') || (s._course5 == 'Y'));
				break;
			case 1:
				reg = (s._course1 == 'Y');
				break;
			case 2:
				reg = (s._course2 == 'Y');
				break;
			case 3:
				reg = (s._course3 == 'Y');
				break;
			case 4:
				reg = (s._course4 == 'Y');
				break;
			case 5:
				reg = (s._course5 == 'Y');
				break;
		}

		if (reg)
			if (courseid == 0)
				std::cout << s;
			else
				std::cout << "ID: " << s._id << std::endl << "Last name: " << s._lastName
				<< std::endl <<  "First name: " << s._firstName << std::endl;
	}

	_lastOperFail = false;

close_file:
	_filePtr->close();
}

bool ManageStudents::operator !() const {
	return _lastOperFail;
}

ManageStudents ManageStudents::operator +(ManageStudents& rhs) {
	ManageStudents ms;
	uint maxStudent;
	Student s1, s2, s3;
	uint f = 0;
	std::string newFilename = "";

	ms._lastOperFail = true;

	if ((_filePtr == nullptr) || (rhs._filePtr == nullptr))
		goto return_obj;

	if ((!openFile()) || (!rhs.openFile()))
		goto return_obj;

newFilenameGen:
	newFilename = _filename.substr(0, _filename.find_last_of('.', 100));
	newFilename.append("+");
	newFilename.append(rhs._filename.substr(0, rhs._filename.find_last_of('.', 100)));
	newFilename.append((f == 0 ? "" : convert2Cstr(f)));
	newFilename.append(".dat");

	try {
		createStudentsFile(newFilename);
	}
	catch (const char* err) {
		f++;
		goto newFilenameGen;
	}

	ms.setFileName(newFilename);

	maxStudent = (_maxStudent > rhs._maxStudent ? _maxStudent : rhs._maxStudent);

	for (uint i = 1; i < maxStudent; ++i) {

		s3 = Student::_emptyStudent;

		if (readStudent(i, s1))
			_lastOperFail = false;
		else
			_lastOperFail = true;

		if (rhs.readStudent(i, s2))
			rhs._lastOperFail = false;
		else
			rhs._lastOperFail = true;

		// read from 2 files succeed
		if (!(!*this) && !(!rhs) && (s1._id != 0) && (s2._id != 0)) {
			s3 = s1;
			s3._course1 = (((s1._course1 == 'Y') || (s2._course1 == 'Y')) ? 'Y' : 'N');
			s3._course2 = (((s1._course2 == 'Y') || (s2._course2 == 'Y')) ? 'Y' : 'N');
			s3._course3 = (((s1._course3 == 'Y') || (s2._course3 == 'Y')) ? 'Y' : 'N');
			s3._course4 = (((s1._course4 == 'Y') || (s2._course4 == 'Y')) ? 'Y' : 'N');
			s3._course5 = (((s1._course5 == 'Y') || (s2._course5 == 'Y')) ? 'Y' : 'N');

		// if read only from lhs succeed
		} else if (!(!*this) && (s1._id != 0)) {
			s3 = s1;
		}
		// if read only from rhs succeed
		else if (!(!rhs) && (s2._id != 0)) {
			s3 = s2;
		}
		else {
			continue;
		}
		
		ms << s3;
	}

	ms._lastOperFail = false;

return_obj:
	_lastOperFail = false;
	rhs._lastOperFail = false;
	return ms;

}

bool ManageStudents::openFile()
{
	_lastOperFail = true;

	if (_filePtr == nullptr)
		return false;

	_filePtr->open(_filename, std::ios::in | std::ios::out | std::ios::binary);

	if (!*_filePtr)
		return false;

	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));

	if (!*_filePtr) {
		_filePtr->close();
		return false;
	}
	
	return true;
}

bool ManageStudents::readStudent(uint sid, Student &s) {
	if (!(_filePtr->is_open()))
		return false;

	if (sid > _maxStudent)
		return false;

	_filePtr->seekg((sizeof(Student) * (sid - 1))+sizeof(_maxStudent));
	
	if ((!*_filePtr))
		return false;

	_filePtr->read((char*)&s, sizeof(s));

	if ((!*_filePtr))
		return false;

	_filePtr->seekg(-1 * (int)sizeof(s), std::ios::_Seekcur);
	return true;
}


ManageStudents& operator << (ManageStudents& in, const Student& s) {
	in.addStudent(s);
	return in;
}


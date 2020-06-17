/*
   File: ManageStudents.cpp
   Description: this is implement file of class ManageStudents
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include "ManageStudents.h"

// constructor get filename
ManageStudents::ManageStudents(const std::string fileName) {
	_lastOperFail = true;
	_filePtr = new std::fstream;
	_filePtr->open(fileName, std::ios::in | std::ios::binary);

	// if error while open, delete and clean filePtr, and return
	if (!*_filePtr) {
		delete _filePtr;
		_filePtr = nullptr;
		return;
	}

	// read from file the _maxStudent value
	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));

	// if error while reading, close, delete and clean filePtr, and return
	if (!*_filePtr) {
		_filePtr->close();
		delete _filePtr;
		_filePtr = nullptr;
		return;
	}

	// if all success, set the filename in object
	_filename = fileName;

	// set failed flag to false
	_lastOperFail = false;
	_filePtr->close();
}

// destructor (closing file and free filePtr)
ManageStudents::~ManageStudents() {
	// if filePtr already null, return
	if (_filePtr == nullptr)
		return;

	if (_filePtr->is_open())
		_filePtr->close();

	delete _filePtr;
	_filePtr = nullptr;
}

// move constructor
ManageStudents::ManageStudents(ManageStudents&& other) {
	_lastOperFail = true;
	_filename = other._filename;
	_maxStudent = other._maxStudent;
	_filePtr = other._filePtr;

	// check if all data copied *and* the source 'other' NOT FAILED, set failed flag to false
	if ((_filename == other._filename) && (_maxStudent == other._maxStudent) && 
		(_filePtr == other._filePtr) && !other._lastOperFail)
		_lastOperFail = false;

	other._filename = "";
	other._filePtr = nullptr;
}

// move assignment
ManageStudents& ManageStudents::operator = (ManageStudents&& other) {
	_lastOperFail = true;
	_filename = other._filename;
	_maxStudent = other._maxStudent;
	_filePtr = other._filePtr;

	// check if all data copied *and* the source 'other' NOT FAILED, set failed flag to false
	if ((_filename == other._filename) && (_maxStudent == other._maxStudent) &&
		(_filePtr == other._filePtr) && !other._lastOperFail)
		_lastOperFail = false;

	other._filename = "";
	other._filePtr = nullptr;

	return *this;
}

// set filename and set fstream object
// only if file is exist in filesystem
// get filename
void ManageStudents::setFileName(const std::string fileName) {
	// set failed flag to true
	_lastOperFail = true;

	// if new filename == current filename, do nothing
	if (fileName == _filename) {
		_lastOperFail = false;
		return;
	}

	// if current filePtr exist, close, delete and clear data
	if (_filePtr != nullptr) {
		_filePtr->close();
		delete _filePtr;
		_filePtr = nullptr;
		_filename = "";
	}

	// set new fstream object and open file to read
	_filePtr = new std::fstream;
	_filePtr->open(fileName, std::ios::in | std::ios::binary);

	// if open file failed, claen and return
	if (!*_filePtr) {
		delete _filePtr;
		_filePtr = nullptr;
		return;
	}

	// read _maxStudent value from file
	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));

	// if reading from file failed, clean and return
	if (!*_filePtr) {
		_filename = "";
		_filePtr->close();
		delete _filePtr;
		_filePtr = nullptr;
		return;
	}

	// set class filename to new filename
	_filename = fileName;

	// set failed flag to false
	_lastOperFail = false;
	_filePtr->close();
}

// add student to file
// get Student Object
// if error, set the _lastOperFail flag
void ManageStudents::addStudent(const Student& s) {
	// set failed flag to true
	_lastOperFail = true;

	// if sid not leagal, return
	if ((s._id > 999) || (s._id == 0))
		return;

	// if openfile failed, return
	if (!(openFile()))
		return;

	// if sid grather than current records, add empty records until sid
	if (s._id > _maxStudent) {
		// go to end of file
		_filePtr->seekg(0,std::ios::end);

		// loop for add empty students
		for (uint i = (_maxStudent + 1); (i < s._id); ++i) {
			// write empty student obj
			*(_filePtr) << Student::_emptyStudent;
		}

		// if error while writing, goto close label
		if (!*_filePtr)
			goto close_file;

		// write the new student
		*(_filePtr) << s;

		// set new value for _maxStudent
		_maxStudent = s._id;

		// go to begining of file
		_filePtr->seekg(0);
		// write the new _maxStudent
		_filePtr->write((char*)&_maxStudent, sizeof(_maxStudent));

		// if error while writing, goto close label
		if (!*_filePtr)
			goto close_file;
	}
	// if sid smaller than current records in file, go to specific record
	else {
		Student tmp;

		// if error while reading this Student from file to tmp student, go to close label
		if (!readStudent(s._id, tmp))
			goto close_file;

		// if this student in file no empty (sid != 0), go to close lable
		if (tmp._id != 0)
			goto close_file;

		// write the new student over current empty student
		*(_filePtr) << s;

		// if error while writing, goto close label
		if (!*_filePtr)
			goto close_file;
	}

	// set failed flag to false
	_lastOperFail = false;

close_file:
	_filePtr->close();
}

// del student from file
// (reset all data of this record)
// get Student ID
// if error, set the _lastOperFail flag
void ManageStudents::delStudent(const uint sid) {
	// set failed flag to true
	_lastOperFail = true;

	// if sid not leagal, return
	if ((sid > _maxStudent) || (sid == 0))
		return;

	// if openfile failed, return
	if (!openFile())
		return;

	Student tmp;

	// if error while reading this Student from file to tmp student, go to close label
	if (!readStudent(sid, tmp))
		goto close_file;

	// if current sid not equal to tmp id, go to close label
	if (sid != tmp._id)
		goto close_file;

	// write emptyStudent over current student
	*(_filePtr) << Student::_emptyStudent;

	// if error while writing, goto close label
	if (!*_filePtr)
		goto close_file;

	// set failed flag to false
	_lastOperFail = false;

close_file:
	_filePtr->close();
}

// set registration of student for course
// get Student ID and course id (1-5) and
// bool param to REG / UNREG
// if error or already register/unregister, set the _lastOperFail flag
void ManageStudents::regStudent(const uint sid, const uint courseid, const bool reg) {
	// set failed flag to true
	_lastOperFail = true;

	// if courseid not leagal, return
	if ((courseid > 5) || (courseid == 0))
		return;

	// if sid not leagal, return
	if ((sid > _maxStudent) || (sid == 0))
		return;

	// if openfile failed, return
	if (!openFile())
		return;

	// init ptr to course field
	char* course = nullptr;
	Student tmp;

	// if error while reading this Student from file to tmp student, go to close label
	if (!readStudent(sid, tmp))
		goto close_file;

	// if current sid not equal to tmp id, go to close label
	if (sid != tmp._id)
		goto close_file;

	// set course ptr to specific course field
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

	// check if ask to reg/unreg and student already reg/unreg
	if (reg == (*course == 'Y'))
		goto close_file;

	// set new value for registraion in course
	*course = (reg ? 'Y' : 'N');

	// write the new object to file
	*(_filePtr) << tmp;

	// if error while writing, goto close label
	if (!*_filePtr)
		goto close_file;

	// set failed flag to false
	_lastOperFail = false;

close_file:
	_filePtr->close();
}

// check registration of student for course
// get Student ID and course id (1-5) and
// return true if register, false any else
// if error like student not exist etc., set the _lastOperFail flag
bool ManageStudents::checkStudent(const uint sid, const uint courseid) {
	// set failed flag to true
	_lastOperFail = true;

	// if course id not leagal, return
	if ((courseid > 5) || (courseid == 0))
		return false;

	// if student id not leagal, return
	if ((sid > _maxStudent) || (sid == 0))
		return false;

	// if openfile failed, return
	if (!openFile())
		return false;

	// init ptr to course field
	char* course = nullptr;
	Student tmp;

	// if error while reading this Student from file to tmp student, go to close label
	if (!readStudent(sid, tmp))
		goto close_file;

	// if current sid not equal to tmp id, go to close label
	if (sid != tmp._id)
		goto close_file;

	// set course ptr to specific course field
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

	// set failed flag to false
	_lastOperFail = false;

	_filePtr->close();

	// return value of register
	return *course == 'Y';

close_file:
	_filePtr->close();
	return false;
}

// print all information of student
// get Student ID
// if error like student not exist etc., set the _lastOperFail flag
void ManageStudents::printStudent(const uint sid) {
	// set failed flag to true
	_lastOperFail = true;

	// if student id not leagal, return
	if ((sid > _maxStudent) || (sid == 0))
		return;

	// if openfile failed, return
	if (!openFile())
		return;

	Student tmp;

	// if error while reading this Student from file to tmp student, go to close label
	if (!readStudent(sid, tmp))
		goto close_file;

	// if current sid not equal to tmp id, go to close label
	if (sid != tmp._id)
		goto close_file;

	// print out student object
	std::cout << tmp;

	// set failed flag to false
	_lastOperFail = false;

close_file:
	_filePtr->close();
}

// print list of students registered for specific course
// get course id
// if not course id or is 0, print list of all *registered* students
// if error set the _lastOperFail flag
void ManageStudents::printRegStudents(const uint courseid) {
	// set failed flag to true
	_lastOperFail = true;

	// if course id not leagal, return
	if (courseid > 5)
		return;

	// if openfile failed, return
	if (!openFile())
		return;

	bool reg;
	Student s;
	// loop for read all student into tmp
	for (uint i = 1; i <= _maxStudent; ++i) {

		// if error while reading this Student from file to tmp student, go to close label
		if (!readStudent(i, s))
			goto close_file;

		reg = false;
		// check reg for specific course
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
			// if ask all course, print all info about the student
			if (courseid == 0)
				std::cout << s;
			// if ask for specific course, print only id and name
			else
				std::cout << "ID: " << s._id << std::endl << "Last name: " << s._lastName
				<< std::endl <<  "First name: " << s._firstName << std::endl;
	}

	// set failed flag to false
	_lastOperFail = false;

close_file:
	_filePtr->close();
}

// get filename
std::string ManageStudents::getFilename() const {
	return _filename;
}

// bool ! operator, return flag _lastOperFail
// true if last operation failed
bool ManageStudents::operator !() const {
	return _lastOperFail;
}

// operator +, combine lhs file with rhs file
// create new file with all student, and union
// registered info from 2 files
ManageStudents ManageStudents::operator +(ManageStudents& rhs) {
	ManageStudents ms;
	uint maxStudent;
	Student s1, s2, s3;
	uint f = 0;
	bool readS1 = false, readS2 = false;
	std::string newFilename = "";

	// set failed flag of new object as true
	ms._lastOperFail = true;

	// if one from sides has no filePtr, go to return
	if ((_filePtr == nullptr) || (rhs._filePtr == nullptr))
		goto return_obj;

	// if error while open one from sides file, go to return
	if ((!openFile()) || (!rhs.openFile()))
		goto return_obj;

newFilenameGen:
	// generator to new filename, based on left file and right file, without extension and add '.dat' extension
	// if file already exist, add f counter before extension. (lsource+rsource.dat / lsource+rsource1.dat)
	
	// get left filename without extension
	newFilename = _filename.substr(0, _filename.find_last_of('.', 100));
	// add '+' sign to end of new filename
	newFilename.append("+");
	// add right filename without extension
	newFilename.append(rhs._filename.substr(0, rhs._filename.find_last_of('.', 100)));
	// if f grather than 0, add f to end of filename
	newFilename.append((f == 0 ? "" : convert2Cstr(f)));
	// add '.dat' to end of filename
	newFilename.append(".dat");

	try {
		// call to function create file
		createStudentsFile(newFilename);
	}
	catch (const char* err) {
		// if file already exist, go back to filename generator with advance f
		if (err == "file already exist!") {
			f++;
			goto newFilenameGen;
		}
		// if error while create file, goto return obj
		else {
			goto return_obj;
		}
	}

	// set newfilename to new ms
	ms.setFileName(newFilename);

	// get the max from 2 _maxStudent values
	maxStudent = (_maxStudent > rhs._maxStudent ? _maxStudent : rhs._maxStudent);

	// loop for all records in 2 files
	for (uint i = 1; i <= maxStudent; ++i) {

		// set s3 as emptyStudent
		s3 = Student::_emptyStudent;

		// set flags of read students from files
		readS1 = readStudent(i, s1);
		readS2 = rhs.readStudent(i, s2);

		// if error reading from 2 files, goto return obj
		if (!readS1 && !readS2)
			goto return_obj;

		// if read from 2 files and have 2 real student info
		if (readS1 && readS2 && (s1._id == i) && (s2._id == i)) {
			s3 = s1;
			s3._course1 = (((s1._course1 == 'Y') || (s2._course1 == 'Y')) ? 'Y' : 'N');
			s3._course2 = (((s1._course2 == 'Y') || (s2._course2 == 'Y')) ? 'Y' : 'N');
			s3._course3 = (((s1._course3 == 'Y') || (s2._course3 == 'Y')) ? 'Y' : 'N');
			s3._course4 = (((s1._course4 == 'Y') || (s2._course4 == 'Y')) ? 'Y' : 'N');
			s3._course5 = (((s1._course5 == 'Y') || (s2._course5 == 'Y')) ? 'Y' : 'N');

		// if read only from lhs succeed
		} else if (readS1 && (s1._id == i)) {
			s3 = s1;
		}
		// if read only from rhs succeed
		else if (readS2 && (s2._id == i)) {
			s3 = s2;
		}
		// if no one from student is with real values, go to next iteration
		else{
			continue;
		}
		
		// write new student to file
		ms << s3;
	}

	// set new ms failed flag to false
	ms._lastOperFail = false;

return_obj:
	// if lhs file is open, close
	if ((_filePtr != nullptr) && (_filePtr->is_open()))
		_filePtr->close();

	// reset failed flag for lhs
	_lastOperFail = false;

	// if rhs file is open, close
	if ((rhs._filePtr != nullptr) && (rhs._filePtr->is_open()))
		rhs._filePtr->close();

	// reset failed flag for rhs
	rhs._lastOperFail = false;

	// return new ManageStudent obj
	return ms;
}

// service function to open file with check errors
// return true if open is succeed
bool ManageStudents::openFile(){
	// set failed flag to true
	_lastOperFail = true;

	// if no filePtr, return false
	if (_filePtr == nullptr)
		return false;

	_filePtr->open(_filename, std::ios::in | std::ios::out | std::ios::binary);

	// if error while open file, return false
	if (!*_filePtr)
		return false;
	
	// read value of _maxStudent
	_filePtr->read((char*)&_maxStudent, sizeof(_maxStudent));

	// if error while reading close and return false
	if (!*_filePtr) {
		_filePtr->close();
		return false;
	}
	
	return true;
}

// read student from file, based on student id, get Student object to return into
// return true if read to object succeed
// move the marker in file, to begin of this Student to rewrite or reread
bool ManageStudents::readStudent(uint sid, Student &s) {
	// if file is not open yet
	if (!(_filePtr->is_open()))
		return false;

	// if sid not leagal
	if (sid > _maxStudent)
		return false;

	// go to begining of specific Student object
	_filePtr->seekg((sizeof(Student) * (sid - 1))+sizeof(_maxStudent));
	
	// if failed return false
	if ((!*_filePtr))
		return false;

	// read the current student to given s object
	_filePtr->read((char*)&s, sizeof(s));

	// if failed to read return false
	if ((!*_filePtr))
		return false;

	// go back to begining of current student to rewrite
	_filePtr->seekg(-1 * (int)sizeof(s), std::ios::_Seekcur);
	return true;
}

// insertion operator to add student to file
// using file << Student obj
// if error, set the _lastOperFail flag
ManageStudents& operator << (ManageStudents& in, const Student& s) {
	in.addStudent(s);
	return in;
}


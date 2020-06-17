/*
   File: ManageStudents.h
   Description: this is header file to declare function of manage files
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __MANAGESTUDENTS_H_
#define __MANAGESTUDENTS_H_

#include "Student.h"
#include "File.h"

class ManageStudents {
private:
    std::string _filename = "";
    std::fstream* _filePtr = nullptr;
    bool _lastOperFail = false; // flag to store status of last operation
    uint _maxStudent = 0;

    // priavte functions:

    // service function to open file with check errors
    // return true if open is succeed
    bool openFile();

    // read student from file, based on student id, get Student object to return into
    // return true if read to object succeed
    // move the marker in file, to begin of this Student to rewrite or reread
    bool readStudent(uint sid, Student& s);

public:
    // constructors:

    // default constuctor
    ManageStudents() = default;

    // constructor get filename
    ManageStudents(const std::string fileName);

    // destructor (closing file and free filePtr)
    ~ManageStudents();

    // move constructor
    ManageStudents(ManageStudents&&);

    // move assignment
    ManageStudents& operator = (ManageStudents&&);

    // copy constructor and copy assignment are disabled
    ManageStudents(const ManageStudents&) = delete;
    void operator = (const ManageStudents&) = delete;

    // public functions:

    // set filename and set fstream object
    // only if file is exist in filesystem
    // get filename
    void setFileName(const std::string fileName);

    // add student to file
    // get Student Object
    // if error, set the _lastOperFail flag
    void addStudent(const Student& s);

    // del student from file
    // (reset all data of this record)
    // get Student ID
    // if error, set the _lastOperFail flag
    void delStudent(const uint sid);

    // set registration of student for course
    // get Student ID and course id (1-5) and
    // bool param to REG / UNREG
    // if error or already register/unregister, set the _lastOperFail flag
    void regStudent(const uint sid, const uint courseid, const bool reg);

    // check registration of student for course
    // get Student ID and course id (1-5) and
    // return true if register, false any else
    // if error like student not exist etc., set the _lastOperFail flag
    bool checkStudent(const uint sid, const uint courseid);

    // print all information of student
    // get Student ID
    // if error like student not exist etc., set the _lastOperFail flag
    void printStudent(const uint sid);
 
    // print list of students registered for specific course
    // get course id
    // if not course id or is 0, print list of all *registered* students
    // if error set the _lastOperFail flag
    void printRegStudents(const uint courseid = 0);

    // get filename
    std::string getFilename() const;

    // bool ! operator, return flag _lastOperFail
    // true if last operation failed
    bool operator !() const;

    // operator +, combine lhs file with rhs file
    // create new file with all student, and union
    // registered info from 2 files
    ManageStudents operator +(ManageStudents&);

};

// insertion operator to add student to file
// using file << Student obj
// if error, set the _lastOperFail flag
ManageStudents& operator << (ManageStudents& in, const Student& s);

#endif __MANAGESTUDENTS_H_


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
    bool _lastOperFail = false;
    uint _maxStudent = 0;

    bool openFile();
    bool readStudent(uint sid, Student& s);

public:
    ManageStudents() = default;

    ManageStudents(const std::string fileName);

    ~ManageStudents();

    ManageStudents(ManageStudents&&);

    ManageStudents& operator = (ManageStudents&&);

    // copy constructor and copy assigment are disabled
    ManageStudents(const ManageStudents&) = delete;
    void operator = (const ManageStudents&) = delete;

    void setFileName(const std::string fileName);

    void addStudent(const Student& s);

    void delStudent(const uint sid);

    void regStudent(const uint sid, const uint courseid, const bool reg);

    bool checkStudent(const uint sid, const uint courseid);

    void printStudent(const uint sid);
 
    void printRegStudents(const uint courseid = 0);

    std::string getFilename() const;

    bool operator !() const;

    ManageStudents operator +(ManageStudents&);
};

ManageStudents& operator << (ManageStudents& in, const Student&);

#endif __MANAGESTUDENTS_H_


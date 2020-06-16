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
    bool _fileExist = false;
    bool _lastOperSucc = true;
    uint _maxStudent = 0;

    void openFile();

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

    void regStudent(const uint sid, const uint courseid);

    bool checkStudent(const uint sid, const uint courseid);

    void printStudent(const uint sid);
 
    void printRegStudents(const uint courseid = 0);

    bool operator !() const;

    ManageStudents operator +(const ManageStudents&) const;
};

ManageStudents& operator << (ManageStudents& in, const Student&);

#endif __MANAGESTUDENTS_H_


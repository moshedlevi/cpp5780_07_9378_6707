/*
   File: Student.h
   Description: this is header file of struct Student
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/
#pragma warning (disable:4996)

#ifndef __STUDENT_H_
#define __STUDENT_H_

#include "mytypes.h"
#include <iostream>
#include <fstream>
#include <string>

struct Student {
private:
    uint _id = 0;
    char _lastName[21] = "";
    char _firstName[21] = "";
    char _course1 = 'N';  // get Y or N, to set register info for course
    char _course2 = 'N';
    char _course3 = 'N';
    char _course4 = 'N';
    char _course5 = 'N';

public:
    // static field to hold empty student
    static const Student _emptyStudent;

    // constructors:

    // default constructor
    Student() = default;

    // constructor get id, last name and first name
    Student(const uint id, const std::string lastName, const std::string firstName) :
        _id(id) {
        strcpy(_lastName, lastName.substr(0, 20).c_str());
        strcpy(_firstName, firstName.substr(0, 20).c_str());
    };

    // set function:

    // set info in student object, get id, last name and first name
    void setInfo(const uint id, const std::string lastName, const std::string firstName);

    // operators:

    // friend operator ostream extraction (with titles)
    friend std::ostream& operator << (std::ostream& out, const Student& s);

    // friend operator file stream extraction - write to file (binary)
    friend std::fstream& operator << (std::fstream& out, const Student& s);

    // friend operator file stram insertion - read from file (binary)
    friend std::fstream& operator >> (std::fstream& in, Student& s);

    // friend class ManageStudents
    friend extern class ManageStudents;
};

// operator cout stream extraction from student (with titles)
std::ostream& operator << (std::ostream& out, const Student& s);

// operator file stream extraction from student - write to file (binary)
std::fstream& operator << (std::fstream& out, const Student& s);

// operator file stram insertion to student - read from file (binary)
std::fstream& operator >> (std::fstream& in, Student& s);

#endif __STUDENT_H_

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
//#include "ManageStudents.h"
#include <iostream>
#include <fstream>
#include <string>

struct Student {
private:
    uint _id = 0;
    char _lastName[21] = "";
    char _firstName[21] = "";
    char _course1 = 'N';
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
        strcpy(_firstName, firstName.substr(0,20).c_str());
    };

    void setInfo(const uint id, const std::string lastName, const std::string firstName);

    // operators:

    // friend operator ostream extraction
    friend std::ostream& operator << (std::ostream& out,const Student& s);

    // friend operator file stream extraction
    friend std::fstream& operator << (std::fstream& out,const Student& s);

    // friend operator file stram insertion
    friend std::fstream& operator >> (std::fstream& in, Student& s);

    friend extern class ManageStudents;
};

// operator cout stream extraction from student
std::ostream& operator << (std::ostream& out, const Student& s);

// operator file stream extraction from student
std::fstream& operator << (std::fstream& out, const Student& s);

// operator file stram insertion to student
std::fstream& operator >> (std::fstream& in, Student& s);

#endif __STUDENT_H_

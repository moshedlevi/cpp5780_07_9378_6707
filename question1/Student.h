/*
   File: Student.h
   Description: this is file include some help functions, mainly binarySearch for different types
   Course: 150018 C++ Workshop
   Exercise 7, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __STUDENT_H_
#define __STUDENT_H_

#include "mytypes.h"
#include <iostream>
#include <fstream>
#include <string>

struct Student {
private:
    uint _id = 0;
    std::string _lastName = "";
    std::string _firstName = "";
    char _course1 = 'N';
    char _course2 = 'N';
    char _course3 = 'N';
    char _course4 = 'N';
    char _course5 = 'N';
public:
    Student() = default;
    Student(const uint id, const std::string lastName, const std::string firstName) : _id(id), _lastName(lastName), _firstName(firstName) {};

    void id(uint id) { _id = id; };

    friend std::ostream& operator << (std::ostream& out,const Student& s);
    friend std::fstream& operator << (std::fstream& out,const Student& s);
    friend std::fstream& operator >> (std::fstream& in, Student& s);
};

std::fstream& operator << (std::fstream& out, const Student& s);

std::ostream& operator << (std::ostream& out, const Student& s);

std::fstream& operator >> (std::fstream& in, Student& s);

#endif __STUDENT_H_

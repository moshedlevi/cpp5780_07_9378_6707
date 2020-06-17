/*
   File: File.h
   Description: this is header file to declare function of manage files
   Course: 150018 C++ Workshop
   Exercise 7, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/


#ifndef __FILE_H_
#define __FILE_H_

#include <iostream>
#include <fstream>
#include <string>

// create new file with 10 records of empty students, get filename to create
std::fstream& createStudentsFile(const std::string fileName);

// read students records from file, get filename to read
std::fstream& readStudentsFile(const std::string fileName);

#endif __FILE_H_
/*
   File: File.h
   Description: this is header file to declare function of manage files
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/


#ifndef __FILE_H_
#define __FILE_H_

#include <iostream>
#include <fstream>
#include <string>

std::fstream& createStudentsFile(const std::string fileName);

std::fstream& readStudentsFile(const std::string fileName);

bool fileExist(const std::string fileName);

#endif __FILE_H_
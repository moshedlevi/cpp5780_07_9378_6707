
/*
   File: File.cpp
   Description: this is file include some help functions, mainly binarySearch for different types
   Course: 150018 C++ Workshop
   Exercise 7, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include "File.h"
#include "Student.h"

using namespace std;

std::fstream& createStudentsFile(const std::string fileName)
{
    std::fstream newFile;

    try {
        newFile.open(fileName,ios::out | ios::binary);

        if (!newFile) {
            throw "error opening file!";
        }

        Student s;
        uint startID = 0;

        newFile.write((char*)&startID, sizeof(startID));

        for (int i = 1; i <= 10; ++i) {
            newFile << s;
        }
    }
    catch (void * err) {
        cout << err;
    }

    newFile.close();

    return newFile;
}

std::fstream& readStudentsFile(const std::string fileName)
{
    std::fstream existFile;

    try {
        existFile.open(fileName, ios::in | ios::binary);

        if (!existFile) {
            throw "error opening file!";
        }

        Student s;
        uint startID = 0;

        existFile.read((char*)&startID, sizeof(startID));

        cout << startID << endl;

        existFile >> s;

        while (existFile) {
            cout << s;
            existFile >> s;
        }
    }
    catch (void* err) {
        cout << err;
    }

    existFile.close();

    return existFile;
}

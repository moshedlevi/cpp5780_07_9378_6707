/*
   File: File.cpp
   Description: this is implement file of function to manage Students files
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include "File.h"
#include "Student.h"

using namespace std;

std::fstream& createStudentsFile(const std::string fileName)
{
    std::fstream newFile;

    // try to open file to check if already exist
    newFile.open(fileName, ios::in | ios::binary);

    // if open file to read success = file already exist
    if (newFile) {
        newFile.close();
        throw "file already exist!";
    }

    newFile.open(fileName,ios::out | ios::binary);

    // if open file to write failed
    if (!newFile) {
        throw "error opening file!";
    }

    uint startID = 10;
        
    // write to file the max number of current students
    newFile.write((char*)&startID, sizeof(startID));

    // init file with 10 empty students
    for (int i = 1; i <= 10; ++i) {
        newFile << Student::_emptyStudent;
    }

    newFile.close();

    return newFile;
}

std::fstream& readStudentsFile(const std::string fileName)
{
    std::fstream existFile;

    existFile.open(fileName, ios::in | ios::binary);

    if (!existFile) {
        throw "error opening file!";
    }

    Student s;
    uint lastID = 0;
    int i = 0;

    // read from file begin the max number of student
    existFile.read((char*)&lastID, sizeof(lastID));

    // print out lastID
    cout << lastID << endl;

    // read first Student from the file
    existFile >> s;

    // loop until error reading from file
    while (existFile) {
        // print out student
        cout << s;

        if (!existFile.eof())
            // read next student
            existFile >> s;
    }

    existFile.close();

    return existFile;
}

bool fileExist(const std::string fileName) {
    std::ifstream file(fileName);

    if (file) {
        file.close();
        return true;
    }
    else {
        return false;
    }
}

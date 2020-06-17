
/*
   File: File.cpp
   Description: this is implement file of function to manage Students files
   Course: 150018 C++ Workshop
   Exercise 7, Question 1
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#include "File.h"
#include "Student.h"

using namespace std;

// create new file with 10 records of empty students, get filename to create
std::fstream& createStudentsFile(const std::string fileName)
{
    std::fstream newFile;

    // open file to write
    newFile.open(fileName,ios::out | ios::binary);

    // check if error while opening
    if (!newFile) {
        throw "error opening file!";
    }

    // init first field to store current count of records
    uint lastID = 10;
        
    // write to file the current count of records
    newFile.write((char*)&lastID, sizeof(lastID));

    // init file with 10 empty students
    for (int i = 1; i <= 10; ++i) {
        newFile << Student::_emptyStudent;
    }

    newFile.close();

    return newFile;
}

// read students records from file, get filename to read
std::fstream& readStudentsFile(const std::string fileName)
{
    std::fstream existFile;

    // open file to read
    existFile.open(fileName, ios::in | ios::binary);

    // check if error while opening
    if (!existFile) {
        throw "error opening file!";
    }

    Student s;
    uint lastID = 0;

    // read from file begin the max number of student
    existFile.read((char*)&lastID, sizeof(lastID));

    // print out lastID
    cout << "current records in file: " << lastID << endl;

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

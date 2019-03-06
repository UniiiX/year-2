#ifndef MYDATA_H
#define MYDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cmath>

#include "PrimeNumbersGenerator.h"

class Student
{
private:
    std::string firstName;
    std::string lastName;
    double gradePointAverage;

int hashFunction(const std::string & target, const int initialValue, const int multiplier);

public:
    // max number of students that can possibly be in one group
    static const int maxCount = 40;
    static const int memoryCostMultiplier = 8;

    Student(const std::string & firstName, const std::string & lastName);

    const double getGradePointAverage() const;
    const std::string getLastName() const;

    void setGradePointAverage(const double gradePointAverage);

    int hashFunction(const int initialValue, const int multiplier);

    void print();

    bool operator<(const Student & other) const;
    bool operator>(const Student & other) const;
    bool operator==(const Student & other) const;
};

class Group
{
private:
    std::list<Student*> students;

public:
    // max number of groups that can possibly be in the university
    static const int maxCount = 200;
    static const int memoryCostMultiplier = 8;

    Group(const std::string & filename);
    ~Group();

    std::list<Student*> & getStudents();

    int hashFunction(const int initialValue, const int multiplier);

    void print();
};

#endif // MYDATA_H

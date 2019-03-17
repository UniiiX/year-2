#include "MyData.h"

Student::Student(const std::string & firstName, const std::string & lastName)
{
    this->firstName = firstName;
    this->lastName = lastName;
}

const double Student::getGradePointAverage() const
{
    return gradePointAverage;
}

const std::string Student::getLastName() const
{
    return lastName;
}

void Student::setGradePointAverage(const double gradePointAverage)
{
    this->gradePointAverage = gradePointAverage;
}

int Student::hashFunction(const std::string & target, const int initialValue, const int multiplier)
{
    if (target.size() == 0)
    {
        return initialValue;
    }
    int divider = PrimeNumbersGenerator::minPrimeNumberGreaterThan(maxCount * memoryCostMultiplier);

    return static_cast<int>(std::abs(hashFunction(target.substr(0, target.size() - 1), initialValue, multiplier + 1) +
                                     target.at(target.size() - 1) * multiplier)) % divider;
}

int Student::hashFunction(const int initialValue, const int multiplier)
{
    const std::string fullName = firstName + lastName;
    return hashFunction(fullName, initialValue, multiplier);
}

void Student::print()
{
    std::cout << firstName << " " << lastName << " - " << gradePointAverage << std::endl;
}

bool Student::operator<(const Student & other) const
{
    return (this->gradePointAverage < other.getGradePointAverage());
}

bool Student::operator>(const Student & other) const
{
    return (this->gradePointAverage > other.getGradePointAverage());
}

bool Student::operator==(const Student & other) const
{
    return (this->gradePointAverage == other.getGradePointAverage());
}

//------------------------------------------------------------------------------------------------

Group::Group(const std::string & filename)
{
    std::string firstName;
    std::string lastName;
    std::ifstream fin(filename);

    while (fin >> lastName && fin >> firstName)
    {
        students.insert(students.end(), new Student(firstName, lastName));
    }
    fin.close();
}

Group::~Group()
{
    for (auto student : students)
    {
        delete student;
    }
}

std::list<Student*> & Group::getStudents()
{
    return students;
}

int Group::hashFunction(const int initialValue, const int multiplier)
{
    int result = 0;
    for (auto student : students)
    {
        result += student->hashFunction(initialValue, multiplier);
    }
    int divider = PrimeNumbersGenerator::minPrimeNumberGreaterThan(maxCount * memoryCostMultiplier);
    result %= divider;
    return result;
}

void Group::print()
{
    // is used for enumeration of students as we print their names
    int index = 1;
    for (auto student : students)
    {
        std::cout << index << ". ";
        student->print();
        index++;
    }
}

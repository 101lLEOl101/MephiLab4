//
// Created by Lenya on 02.07.2024.
//
#include <string>

class Person{
protected:
std::string first_name;
std::string last_name;
public:
    Person(std::string first, std::string last) : first_name(first), last_name(last){}
};

class Student : public Person{
private:
    size_t number_group;
    size_t Course;
public:
    Student(std::string first, std::string last, size_t NumberGroup, size_t course) : Person(first, last), number_group(NumberGroup), Course(course){}
};

class Teacher : public Person{
private:
    std::string subject;
public:
};
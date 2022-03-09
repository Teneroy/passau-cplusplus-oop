//
// Created by studone on 3/6/22.
//

#ifndef PASSAU_CPLUSPLUS_OOP_STUDENT_H
#define PASSAU_CPLUSPLUS_OOP_STUDENT_H

#include "Course.h"
#include <iostream>
#include <string>
#include <vector>

class Course;

class Student
{
private:
    std::string firstName, lastName;
    int studID;
    std::vector<Course*> courses;

public:
    Student() = default;
    Student(std::string firstName, std::string lastName, int id);
    ~Student();
    std::string getName() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getStudID() const;
    std::vector<Course*>  getCourses();
    void add_course(Course* course);
    void remove_course(Course* course);
};

#endif //PASSAU_CPLUSPLUS_OOP_STUDENT_H

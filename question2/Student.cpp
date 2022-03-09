#include "Student.h"

#include <utility>

std::string Student::getName() const {
    return this -> lastName + " " + this -> firstName;
}

std::string Student::getStudID() const {
    return std::to_string(this -> studID);
}

std::vector<Course*> Student::getCourses() {
    return {};
}

Student::Student(std::string firstName, std::string lastName, int id) : firstName(std::move(firstName)), lastName(std::move(lastName)), studID(id) {}

void Student::add_course(Course* course) {
    courses.push_back(course);
}

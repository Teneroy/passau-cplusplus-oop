#include "Student.h"

#include <utility>

std::string Student::getName() const {
    return ((this -> lastName) + " " + (this -> firstName));
}

std::string Student::getStudID() const {
    return std::to_string(this -> studID);
}

std::vector<Course*> Student::getCourses() {
    return courses;
}

Student::Student(std::string firstName, std::string lastName, int id) : firstName(std::move(firstName)), lastName(std::move(lastName)), studID(id) {}

void Student::add_course(Course* course) {
    courses.push_back(course);
}

void Student::remove_course(Course* course) {
    std::remove(courses.begin(), courses.end(), course);
}

Student::~Student() {
    for (const auto &item : courses) {
        item ->remove_student(this);
        Course::remove_student_from_all(this);
    }
}

std::string Student::getFirstName() const {
    return firstName;
}

std::string Student::getLastName() const {
    return lastName;
}

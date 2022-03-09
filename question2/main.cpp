#include <string>
#include "Course.h"
#include "Student.h"
#include <iostream>
#include<fstream>
#include <sstream>

void readCourses(const std::string& filename, std::vector<Course*>& courses)
{
    std::ifstream filestream(filename);
    if(!filestream) {
        throw std::ifstream::failure("Can't open a file!");
    }

    std::string line;
    int str_number = 0;
    while(std::getline(filestream, line)) {
        if (str_number == 0) {
            str_number++;
            continue;
        }
        std::istringstream s(line);
        std::string field;
        std::vector<std::string> tokens;
        while (getline(s, field,',')) {
            tokens.push_back(field);
        }
        if(tokens[3] == "p") {
            courses.push_back(new ProjectCourse(tokens[1], tokens[0], std::stoi(tokens[2])));
        } else if(tokens[3] == "w") {
            courses.push_back(new WrittenCourse(tokens[1], tokens[0], std::stoi(tokens[2])));
        } else {
            courses.push_back(new HybridCourse(tokens[1], tokens[0], std::stoi(tokens[2])));
        }
        str_number++;
    }
}

void readStudents(const std::string& filename)
{
    std::ifstream filestream(filename);
    if(!filestream) {
        throw std::ifstream::failure("Can't open a file!");
    }

    std::string line;
    int str_number = 0;
    while(std::getline(filestream, line)) {
        if (str_number == 0) {
            str_number++;
            continue;
        }
        std::istringstream s(line);
        std::string field;
        std::vector<std::string> tokens;
        while (getline(s, field,',')) {
            tokens.push_back(field);
        }
        std::string lastName = tokens[2];
        lastName.erase(std::remove(lastName.begin(), lastName.end(), '\r'),
                       lastName.end());
        Course::add_student_to_student_list(new Student(tokens[1], lastName, std::stoi(tokens[0])));
        str_number++;
    }
}

void writeCourseGrades(Course * course) {
    std::ofstream filestream("/home/studone/PassauOOP/passau-cplusplus-oop/question2/csv/" + course -> getID() + "-grade.csv");
    if(!filestream) {
        throw std::ifstream::failure("Can't open a file!");
    }
    filestream << "First Name,Last Name,Matriculation,ID,Final Result,Grade\n";
    for (const auto &student : course->getStudents()) {
        filestream <<  student->getFirstName() + "," + student->getLastName() + "," + student->getStudID() + "," + course->getID() + "," +
                std::to_string(course->finalResult(student)) + "," + course->grade(student) + "\n";
    }
}

int main() {
    std::vector<Course*> courses;
    readCourses("/home/studone/PassauOOP/passau-cplusplus-oop/question2/csv/courses.csv", courses);
    for (const auto &item : courses) {
        std::cout << item->getID() << std::endl;
    }

    readStudents("/home/studone/PassauOOP/passau-cplusplus-oop/question2/csv/students.csv");

    for (const auto &item : courses) {
        item->exportCSV("/home/studone/PassauOOP/passau-cplusplus-oop/question2/csv/" + item->getID() + "-scores.csv");
    }

    for (const auto &item : courses) {
        writeCourseGrades(item);
    }

    return 0;
}

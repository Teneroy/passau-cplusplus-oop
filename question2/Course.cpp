#include "Course.h"
#include "Grade.h"
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>

Course::Course(std::string name, std::string id, int credit) : courseName(std::move(name)), courseID(std::move(id)), credit(credit) {}

std::vector<Student*> Course::all_students;

std::map<int, char> ProjectCourse::gradeMap;
std::map<int, char> HybridCourse::gradeMap;
std::map<int, char> WrittenCourse::gradeMap;


std::string Course::getID() const {
    return courseID;
}

std::string Course::getName() {
    return courseName;
}

void Course::add_student_to_student_list(Student * student) {
    all_students.push_back(student);
}

Student *Course::find_student_by_id(const std::string &id) {
    auto it = std::find_if(
            all_students.begin(), all_students.end(),
            [&id](const Student * x) { return x->getStudID() == id;});
    if (it != all_students.end())
    {
        auto index = std::distance(all_students.begin(), it);
        return all_students[index];
    }
    throw std::logic_error("Impossible to find a student!");
}

void Course::readCsvFile(const std::string& filename, const std::function<void(std::vector<std::string>& tokens)>& func) {
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

        func(tokens);

        str_number++;
    }
}

std::vector<Student *> Course::getAllStudents() {
    return all_students;
}

std::vector<Student *> Course::getStudents() {
    return students;
}

Course::~Course() {
    for (const auto &item : students) {
        item->remove_course(this);
    }
}

void Course::remove_student(Student *student) {
    std::remove(students.begin(), students.end(), student);
    remove_from_student_map(student);
}

void Course::remove_student_from_all(Student *student) {
    std::remove(all_students.begin(), all_students.end(), student);
}

template<typename T>
T findStudentInMap(Student * student, std::map<Student*, T, comp>& studMap) {
    for (const auto &item : studMap) {
        auto z = item;
        if (z.first == student) {
            return z.second;
        }
    }
    throw std::runtime_error("Can't find this student!");
}

WrittenCourse::WrittenCourse(std::string name, std::string id, int credit) : Course(name, id, credit) {
    precomputeGradeMapWritten(gradeMap);
}

float WrittenCourse::finalResult(Student* student) {
    auto gradesTuple = findStudentInMap<std::tuple<float, float>>(student, studentsMap);
    std::tuple<float, float> b = std::make_tuple(std::get<0>(gradesTuple), std::get<1>(gradesTuple));
    return calculateWritten(b);
}

std::string WrittenCourse::grade(Student* student) {
    int res = finalResult(student);
    char grade = gradeMap.find(res)->second;
    std::string grade_str(1, grade);
    return grade_str;
}

void WrittenCourse::exportCSV(std::string filename) {
    std::vector<Student*> * f_students = &this->students;
    std::map<Student*, std::tuple<float, float>, comp> * f_studentsMap = &this->studentsMap;
    Course * course = this;
    readCsvFile(filename, [f_students, f_studentsMap, &course](std::vector<std::string>& tokens) {
        Student * line_student = find_student_by_id(tokens[0]);
        line_student->add_course(course);
        f_students->push_back(line_student);
        float midExam = std::stof(tokens[3]);
        float finalExam = std::stof(tokens[4]);
        f_studentsMap->insert(std::make_pair(line_student, std::make_tuple(midExam,  finalExam)));
    });
}

void WrittenCourse::remove_from_student_map(Student *student) {
    studentsMap.erase(student);
}

float ProjectCourse::finalResult(Student* student) {
    auto gradesTuple = findStudentInMap<std::tuple<float, float, float, float>>(student, studentsMap);
    std::tuple<float, float, float, float> c = std::make_tuple(std::get<0>(gradesTuple), std::get<1>(gradesTuple), std::get<2>(gradesTuple), std::get<3>(gradesTuple));
    return calculateProject(c);
}

std::string ProjectCourse::grade(Student* student) {
    int res = finalResult(student);
    char grade = gradeMap.find(res)->second;
    std::string grade_str(1, grade);
    return grade_str;
}

void ProjectCourse::exportCSV(std::string filename) {
    std::vector<Student*> * f_students = &this->students;
    std::map<Student*, std::tuple<float, float, float, float>, comp> * f_studentsMap = &this->studentsMap;
    Course * course = this;
    readCsvFile(filename, [f_students, f_studentsMap, &course](std::vector<std::string>& tokens) {
        if(tokens.size() <= 3)
            throw std::runtime_error("CSV file with scores is malformed");
        Student * line_student = find_student_by_id(tokens[0]);
        line_student->add_course(course);
        f_students->push_back(line_student);
        float project1 = std::stof(tokens[3]);
        float project2 = std::stof(tokens[4]);
        float project3 = std::stof(tokens[5]);
        float project4 = std::stof(tokens[6]);
        f_studentsMap->insert(std::make_pair(line_student, std::make_tuple(project1, project2, project3, project4)));
    });
}

ProjectCourse::ProjectCourse(std::string name, std::string id, int credit) : Course(name, id, credit) {
    precomputeGradeMap(gradeMap);
}

void ProjectCourse::remove_from_student_map(Student *student) {
    studentsMap.erase(student);
}

float HybridCourse::finalResult(Student* student) {
    auto gradesTuple = findStudentInMap<std::tuple<float, float, float, float>>(student, studentsMap);
    std::tuple<float, float, float, float> b = std::make_tuple(std::get<0>(gradesTuple), std::get<1>(gradesTuple), std::get<2>(gradesTuple), std::get<3>(gradesTuple));
    return calculateHybrid(b);
}

std::string HybridCourse::grade(Student* student) {
    int res = finalResult(student);
    char grade = gradeMap.find(res)->second;
    std::string grade_str(1, grade);
    return grade_str;
}

void HybridCourse::exportCSV(std::string filename) {
    std::vector<Student*> * f_students = &this->students;
    std::map<Student*, std::tuple<float, float, float, float>, comp> * f_studentsMap = &this->studentsMap;
    Course * course = this;
    readCsvFile(filename, [f_students, f_studentsMap, &course](std::vector<std::string>& tokens) {
        Student * line_student = find_student_by_id(tokens[0]);
        line_student->add_course(course);
        f_students->push_back(line_student);
        float project1 = std::stof(tokens[3]);
        float project2 = std::stof(tokens[4]);
        float project3 = std::stof(tokens[5]);
        float exam = std::stof(tokens[6]);
        f_studentsMap -> insert(std::make_pair(line_student, std::make_tuple(project1, project2, project3, exam)));
    });
}

HybridCourse::HybridCourse(std::string name, std::string id, int credit) : Course(name, id, credit) {
    precomputeGradeMap(gradeMap);
}

void HybridCourse::remove_from_student_map(Student *student) {
    studentsMap.erase(student);
}

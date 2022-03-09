#ifndef PASSAU_CPLUSPLUS_OOP_COURSE_H
#define PASSAU_CPLUSPLUS_OOP_COURSE_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Student.h"

class Student;

struct comp
{
    template<typename T>
    bool operator()(const T * lhs, const T * rhs) const
    {
        return lhs -> getStudID() != rhs -> getStudID();
    }
};

class Course
{
private:
	std::string courseName, courseID;
    int credit;
    static std::vector<Student*> all_students;
protected:
    std::vector<Student*> students;
    void readCsvFile(const std::string& filename, const std::function<void(std::vector<std::string>& tokens)>& func);
public:
		Course() = default;
		~Course() = default;
		Course(std::string name, std::string id, int credit);
		std::string getID() const;
		std::string getName();
		virtual float finalResult(Student*)=0;
		virtual std::string grade(Student*)=0;
		virtual void exportCSV(std::string)=0;
        static void add_student_to_student_list(Student * student);
        static Student* find_student_by_id(const std::string &id);
        static std::vector<Student*> getAllStudents();
};

class WrittenCourse : public Course {
private:
    std::map<Student*, std::tuple<float, float>, comp> studentsMap;
public:
    WrittenCourse(std::string name, std::string id, int credit) : Course(name, id, credit) {}
    float finalResult(Student*) override;
    std::string grade(Student*) override;
    void exportCSV(std::string) override;
};

class ProjectCourse : public Course {
private:
    std::map<Student*, std::tuple<float, float, float, float>, comp> studentsMap;
public:
    ProjectCourse(std::string name, std::string id, int credit) : Course(name, id, credit) {}
    float finalResult(Student*) override;
    std::string grade(Student*) override;
    void exportCSV(std::string) override;
};

class HybridCourse : public Course {
private:
    std::map<Student*, std::tuple<float, float, float, float>, comp> studentsMap;
public:
    HybridCourse(std::string name, std::string id, int credit) : Course(name, id, credit) {}
    float finalResult(Student*) override;
    std::string grade(Student*) override;
    void exportCSV(std::string) override;
};

#endif //PASSAU_CPLUSPLUS_OOP_COURSE_H

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
    virtual void remove_from_student_map(Student* student)=0;
public:
		Course() = default;
		virtual ~Course();
		Course(std::string name, std::string id, int credit);
		std::string getID() const;
		std::string getName();
		virtual float finalResult(Student*)=0;
		virtual std::string grade(Student*)=0;
		virtual void exportCSV(std::string)=0;
        static void add_student_to_student_list(Student * student);
        static Student* find_student_by_id(const std::string &id);
        static std::vector<Student*> getAllStudents();
        std::vector<Student*> getStudents();
        void remove_student(Student* student);
        static void remove_student_from_all(Student* student);
};

class WrittenCourse : public Course {
private:
    std::map<Student*, std::tuple<float, float>, comp> studentsMap;
    static std::map<int, char> gradeMap;
protected:
    void remove_from_student_map(Student* student) override;
public:
    WrittenCourse(std::string name, std::string id, int credit);
    float finalResult(Student*) override;
    std::string grade(Student*) override;
    void exportCSV(std::string) override;
};

class ProjectCourse : public Course {
private:
    std::map<Student*, std::tuple<float, float, float, float>, comp> studentsMap;
    static std::map<int, char> gradeMap;
protected:
    void remove_from_student_map(Student* student) override;
public:
    float finalResult(Student*) override;
    std::string grade(Student*) override;
    void exportCSV(std::string) override;

    ProjectCourse(std::string name, std::string id, int credit);
};

class HybridCourse : public Course {
private:
    std::map<Student*, std::tuple<float, float, float, float>, comp> studentsMap;
    static std::map<int, char> gradeMap;
protected:
    void remove_from_student_map(Student* student) override;
public:
    float finalResult(Student*) override;
    std::string grade(Student*) override;
    void exportCSV(std::string) override;

    HybridCourse(std::string name, std::string id, int credit);
};

#endif //PASSAU_CPLUSPLUS_OOP_COURSE_H

#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <limits>
using namespace std;
class catalog;
class course;
class section;


//----------------------PROFESSOR CLASS--------------------------------------
class professor
{
public:
	string name;
	string id;
	professor();
};


//----------------------STUDENT CLASS--------------------------------------
class student
{
public:
	string name;
	string id;
	float gpa;
	student();
};


//----------------------UNIVERSITY CLASS--------------------------------------
class university {
	catalog* uniCatalog;
public:
	vector <professor*> professors_list;
	vector <student*> students_list;
	university(catalog* Tcatalog);
	bool add_professor(string profID);
	bool delete_professor(string profID);
	void list_professors();
	int check_professor(string profID);
	bool add_student(string studID);
	bool delete_student(string studID);
	void list_students();
	int check_student(string studentID);
	~university();
};
bool ADD_PROFESSOR(university* Tuniversity);
bool DELETE_PROFESSOR(university* Tuniversity);
bool ADD_STUDENT(university* Tuniversity);
bool DELETE_STUDENT(university* Tuniversity);


//----------------------CATALOG CLASS--------------------------------------
class catalog
{
public:
	string academic_year;
	university* c_university;
	vector <course*> courses_list;
	catalog();
	catalog(string year, university* newUniversity);
	void list_courses();
	bool add_course(course* newCourse); //return true if entered successfully
	bool add_course();
	int check_course(string course_number);
	bool modify_course();
	void delete_course();
	void load_courses(string text_file);
	~catalog();
};


//----------------------COURSE CLASS--------------------------------------
class course
{
	vector <course*> preq;
public:
	catalog* Unicatalog;
	vector <section*> sections;
	string number;
	string name;
	int c_hours;
	string descrip;
	course();
	course(string Tnumber, string Tname, int Tc_hours, string Tdescrip);
	void list_sections();
	bool modify_section(catalog* uniCatalog);
	bool add_section(section* newSection);
	bool delete_section(int Tnumber);
	bool add_preq(string CourseNumber, catalog* Tcatalog);
	int check_section(int Tnumber);
	~course();
};
bool ADD_SECTION(catalog* uniCatalog);
bool MODIFY_SECTION(catalog* uniCatalog);
bool LIST_SECTIONS(catalog* Unicatalog);
bool DELETE_SECTION(catalog* UniCatalog);

//----------------------SECTION CLASS--------------------------------------
class section
{
	const float duration = 1.25;
public:
	vector<student*> student_list;
	university* s_university;
	course* s_course;
	int number;
	string offering_days;
	professor* s_professor;
	float start_time;
	section();
	section(university* Tuniversity, course* Tcourse, int Tnumber,
		string Tofferings, professor* Tprofessor, float Tstart);
	bool register_student(string studentID);
	int check_student(string studentID);
	bool unregister_student(string studentID);
	bool list_students();
	~section();
};
bool REGISTER_STUDENT(catalog* UniCatalog);
bool UNREGISTER_STUDENT(catalog* UniCatalog);
bool LIST_STUDENTS(catalog* UniCatalog);

//----------------------ADDITIONAL FUNCTIONS--------------------------------------
void welcome();
void CourseMenu();
void SectionMenu();
void ProfessorMenu();
void StudentMenu();
void modify_course_display(course* Tcourse);
void modify_section_display(section* Tsection);
int menu_input(int lower, int upper);
bool return_menu();
#include "common.h"



//                                   ___________________
//-----------------------------------|                  |----------------------------------------
//-----------------------------------| UNIVERSITY CLASS |----------------------------------------
//-----------------------------------|__________________|----------------------------------------

university::university(catalog* Tcatalog)
{
	uniCatalog = Tcatalog;
}
//----------------------------------------------------

int university::check_professor(string profID) {
	int size = professors_list.size();
	for (int i = 0; i < size; i++) {
		if (profID == professors_list[i]->id) return i;
	}
	return -1;
}
//----------------------------------------------------

bool university::add_professor(string profID) {
	int index = check_professor(profID);
	if (index > 0) { cout << "Professor is already registered in the university\n"; return true; }
	professor* newProfessor = new professor;
	newProfessor->id = profID;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Professor Name: "; getline(cin, newProfessor->name);
	professors_list.push_back(newProfessor);
	cout << "Professor registered successfullly\n";
	return true;
}
//----------------------------------------------------

bool ADD_PROFESSOR(university* Tuniversity) {
	system("CLS");
	string profID;
	cout << "Creating New Professor Profile ...\n";
	cout << "Professor ID:"; cin >> profID;
	return Tuniversity->add_professor(profID);
}
//----------------------------------------------------

bool university::delete_professor(string profID)
{
	int index = check_professor(profID);
	if (index < 0) { cout << "Professor is already not registered in the university\n"; return true; }
	delete(professors_list[index]);
	professors_list.erase(professors_list.begin() + index);
	cout << "Professor deleted successfullly\n";
	return true;
}
//----------------------------------------------------

bool DELETE_PROFESSOR(university* Tuniversity) {
	system("CLS");
	string profID;
	cout << "Deleting Existing Professor Profile ...\n";
	cout << "Professor ID:"; cin >> profID;
	return Tuniversity->delete_professor(profID);
}
//----------------------------------------------------

void university::list_professors() {
	int size = professors_list.size();
	for (int i = 0; i < size; i++) {
		cout << professors_list[i]->id << "   " << professors_list[i]->name << endl;
	}
}
//----------------------------------------------------

int university::check_student(string studentID) {
	int size = this->students_list.size();
	for (int i = 0; i < size; i++) {
		if (studentID == students_list[i]->id) return i;
	}
	return -1;
}
//----------------------------------------------------

bool university::add_student(string studID) {
	int index = check_student(studID);
	if (index >= 0) { cout << "Student is already registered in the university\n"; return true; }
	student* newStudent = new student;
	newStudent->id = studID;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Student Name: "; getline(cin, newStudent->name);
	cout << "Student GPA: "; cin >> newStudent->gpa;
	students_list.push_back(newStudent);
	cout << "Student registered Successfully\n";
	return true;
}
//----------------------------------------------------

bool ADD_STUDENT(university* Tuniversity) {
	string studID;
	system("CLS");
	cout << "Creating New Student Profile ...\n";
	cout << "Student ID:"; cin >> studID;
	return Tuniversity->add_student(studID);
}
//----------------------------------------------------

bool university::delete_student(string studID) {
	int index = check_student(studID);
	if (index < 0) { cout << "Student is already not registered in the university\n"; return true; }
	delete(students_list[index]);
	students_list.erase(students_list.begin() + index);
	cout << "Student deleted successfully\n";
	return true;

}
//----------------------------------------------------

bool DELETE_STUDENT(university* Tuniversity) {
	system("CLS");
	string studID;
	cout << "Deleting Existing Student Profile ...\n";
	cout << "Student ID:"; cin >> studID;
	return Tuniversity->delete_student(studID);
}
//----------------------------------------------------

void university::list_students() {
	int size = students_list.size();
	for (int i = 0; i < size; i++) {
		cout << students_list[i]->id << "   " << students_list[i]->name << endl;
	}
}
//----------------------------------------------------

university::~university() {
	//remove list of professors
	int prof_size = professors_list.size();
	for (int i = 0; i < prof_size; i++) {
		delete(professors_list[i]);
	}
	professors_list.clear();
	cout << "Professors list removed successfully\n";
	//remove list of students
	int stud_size = students_list.size();
	for (int i = 0; i < stud_size; i++) {
		delete(students_list[i]);
	}
	students_list.clear();
	cout << "Students list removed successfully\n";
}



//                                      ________________
//------------------------------------ /_______________/|----------------------------------------
//------------------------------------|               | |----------------------------------------
//------------------------------------| CATALOG CLASS | |----------------------------------------
//------------------------------------|_______________|/----------------------------------------
catalog::catalog()
{
	academic_year = "None";
}
//----------------------------------------------------

catalog::catalog(string year, university* newUniversity)
{
	academic_year = year;
	c_university = newUniversity;
}
//----------------------------------------------------

void catalog::list_courses()
{
	int size = courses_list.size();
	for (int i = 0; i < size; i++) {
		printf("%d. %s\t%s\n", i + 1, courses_list[i]->number.c_str(), courses_list[i]->name.c_str());
	}
}
//----------------------------------------------------

int catalog::check_course(string course_number) {
	int size = courses_list.size();
	for (int i = 0; i < size; i++) {
		if (strcmp(courses_list[i]->number.c_str(), course_number.c_str()) == 0) return i;
	}
	return -1;
}
//----------------------------------------------------

bool catalog::add_course(course* newCourse) {
	if (check_course(newCourse->name) < 0) return false;
	courses_list.push_back(newCourse);
	return true;
}
//----------------------------------------------------

bool catalog::add_course() {
	course* newCourse = new course;
	system("CLS");
	cout << "Creating course...\n";
	cout << "Course Number: "; cin>>newCourse->number;
	if (check_course(newCourse->number) >= 0) { cout << "Course is already in the calatog" << endl; return false; }
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Course Name: "; getline(cin, newCourse->name);
	cout << "Number of credit hours: "; cin >> newCourse->c_hours;
	string prereq;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Prerequisites numbers (if there is no, enter no): "; getline(cin, prereq);
	istringstream iss;
	iss.str(prereq); string course_num;
	int i = 0;
	while (iss >> course_num) { 
		int index = check_course(course_num);
		if (index < 0) { cout << "Course Number (" << course_num << ") Not Found\n"; }
		else newCourse->add_preq(courses_list[index]->number, this);  
	};
	char c;
	do {
		cout << "Do you want to add some description? (Y/N): "; cin >> c;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	cin.clear();
	cin.ignore(10000, '\n');
	if (c == 'y' || c == 'Y') { cout << "Description: "; getline(cin, newCourse->descrip); }
	courses_list.push_back(newCourse);
	cout << "Succesfull Addition of " << newCourse->name << " Course" << endl;
	return true;
}
//----------------------------------------------------

bool catalog::modify_course() {
	string course_number;
	cout << "Enter Course Number: "; cin >> course_number;
	int index = check_course(course_number);
	if (index < 0) { cout << "Course Not Found\n"; return false; }
	course* Tcourse = courses_list[check_course(course_number)];
	int input;
	bool go_back;
	do {
		modify_course_display(Tcourse); //1(number), 2(name), 3(credit hours), 4(description), 5(back)
		input = menu_input(1, 5);
		if (input == 5) return true; //true to get back
		switch (input)
		{
		case(1):
			cout << "Change number from " << Tcourse->number << " to: ";
			{
				string temp;
				cin >> temp;
				if (check_course(temp) > 0) { cout << "Course Number is already added\n"; }
				else { Tcourse->number = temp; cout << "Number changed successfully\n"; }
			}
			break;

		case (2):
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Change name from " << Tcourse->name << " to: ";
			getline(cin, Tcourse->name);
			cout << "Name changed successfully\n";
			break;

		case (3):
			cout << "Change number of credit hours from " << Tcourse->c_hours << " to: ";
			cin >> Tcourse->c_hours;
			cout << "Number of credit hours changed successfully\n";
			break;

		case(4):
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Change description from" << endl << "\"" << Tcourse->descrip << "\"" << endl
				<< "to: "; getline(cin, Tcourse->descrip);
			cout << "Description changed successfully\n";
			break;
		}
		go_back = return_menu();
	} while (go_back);
	return true; //false to exit the program
}
//----------------------------------------------------

void catalog::delete_course() {
	string course_number;
	cout << "Enter Course Number: "; cin >> course_number;
	int index = check_course(course_number);
	if (index < 0) cout << "Course Not Found in the catalog\n";
	else {
		delete(courses_list[index]);

		courses_list.erase(courses_list.begin() + index);
		cout << "Course Deleted Successfully\n";
	}
}
//----------------------------------------------------

catalog::~catalog()
{
	int size = courses_list.size();
	for (int i = 0; i < size; i++) delete(courses_list[i]);
	courses_list.clear();
}




//-----------------------------------_________________----------------------------------------
//-----------------------------------|               |----------------------------------------
//-----------------------------------| COURSE CLASS  |----------------------------------------
//-----------------------------------|_______________|----------------------------------------

course::course(){}
//----------------------------------------------------

course::course(string Tnumber, string Tname, int Tc_hours, string Tdescrip) {
	number = Tnumber;
	name = Tname;
	c_hours = Tc_hours;
	descrip = Tdescrip;
}
//----------------------------------------------------

bool course::modify_section(catalog* uniCatalog) {
	int section_number;
	cout << "Enter Section Number: "; cin >> section_number;
	int section_index = check_section(section_number);
	if (section_index < 0) { cout << "Section Not Found\n"; return true; }
	section* Tsection = sections[section_index];
	int input;
	bool go_back;
	do {
		modify_section_display(Tsection); //1(number), 2(offerings), 3(professors), 4(start time), 5(back)
		input = menu_input(1, 5);
		if (input == 5) return true; //true to get back
		switch (input)
		{
		case(1): //number
			cout << "Change number from " << Tsection->number << " to: ";
			{
				int temp;
				cin >> temp;
				if (check_section(temp) > 0) { cout << "Section Number is already added\n"; }
				else { Tsection->number = temp; cout << "Number changed successfully\n"; }
			}
			break;

		case (2)://offerings
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Change offerings from " << Tsection->offering_days << " to: ";
			getline(cin, Tsection->offering_days);
			cout << "Offering days changed successfully\n";
			break;

		case (3)://professors
			cout << "Change Professor " << Tsection->s_professor->name << ": New professor ID: ";
			{
				string profid;
				cin >> profid;
				int prof_index = uniCatalog->c_university->check_professor(profid);
				if (prof_index < 0) { cout << "Professor ID is not recorded before in the university\n"; return true; }
				Tsection->s_professor = uniCatalog->c_university->professors_list[prof_index];
				cout << "Professor updated successfully\n"; 
			}
			break;

		case(4): //start time
			cout << "Change Start time from" << Tsection->start_time << endl
				<< "to: "; cin>> Tsection->start_time;
			cout << "Start time changed successfully\n";
			break;
		}
		go_back = return_menu();
	} while (go_back);
	return false; //false to exit the program
}
//----------------------------------------------------

bool MODIFY_SECTION(catalog* uniCatalog) {
	string course_number;
	cout << "Enter Course Number: "; cin >> course_number;
	int course_index = uniCatalog->check_course(course_number);
	if (course_index < 0) { cout << "Course Not Found\n"; return true; }
	course* Tcourse = uniCatalog->courses_list[course_index];
	return Tcourse->modify_section(uniCatalog);
}
//----------------------------------------------------

int course::check_section(int Tnumber)
{
	int size = sections.size();
	for (int i = 0; i < size; i++) {
		if (Tnumber == sections[i]->number) return i;
	}
	return -1;
}
//----------------------------------------------------

void course::list_sections() {
	int size = sections.size();
	for (int i = 0; i < size; i++) {
		cout << sections[i]->number << "   " << sections[i]->offering_days << "   " << sections[i]->start_time << endl;
	}
}
//----------------------------------------------------

bool LIST_SECTIONS(catalog* Unicatalog) {
	string course_number;
	cout << "Enter Course Number: "; cin >> course_number;
	int index = Unicatalog->check_course(course_number);
	if (index < 0) { cout << "Course Not Found\n"; return true; }
	course* Tcourse = Unicatalog->courses_list[index];
	Tcourse->list_sections();
	return true;
}
//----------------------------------------------------

bool course::add_section(section* newSection)
{
	if (check_section(newSection->number) >= 0) {
		cout << "Section is already registered in the course\n"; return true;
	}
	cout << "Section added successfully\n";
	sections.push_back(newSection);
	return true;
}
//----------------------------------------------------

bool ADD_SECTION(catalog* uniCatalog) {
	section* newSection = new section(uniCatalog->c_university);
	system("CLS");
	cout << "Creating section...\n";
	string courseNumber;
	cout << "Course Number: "; cin >> courseNumber;
	int index = uniCatalog->check_course(courseNumber);
	if (index < 0) { cout << "Course Number Not Found in the catalog\n"; return true; }
	course* s_course = uniCatalog->courses_list[index];
	newSection->s_course = s_course;
	cout << "Section Number: "; cin >> newSection->number;
	if (newSection->s_course->check_section(newSection->number) >= 0) { cout << "The Course already has the same section number\n" << endl; return true; }
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Offering days: "; getline(cin, newSection->offering_days);
	cout << "Start time (as a float number): "; cin >> newSection->start_time;
	cin.clear();
	cin.ignore(10000, '\n');
	string profid;
	cout << "Professor ID: "; getline(cin, profid);
	index = uniCatalog->c_university->check_professor(profid);
	if (index < 0) { cout << "Professor ID Not Found in the university\n"; return true; }
	newSection->s_professor = uniCatalog->c_university->professors_list[index];
	istringstream iss;
	string studentids;
	cin.clear();
	cout << "List students IDs: "; getline(cin, studentids);
	iss.str(studentids); string studentid;
	int i = 0;
	while (iss >> studentid) {
		int index = uniCatalog->c_university->check_student(studentid);
		if (index < 0) { cout << "Student ID (" << studentid << ") Not Found\n"; }
		else { 
			newSection->student_list.push_back(uniCatalog->c_university->students_list[index]);
			cout << "Student whose ID (" << studentid << ") is added successfully\n";
		}
	};
	s_course->add_section(newSection);
	cout << "Succesfull Addition of Section no. " << newSection->number << endl;
	return true;
}
//----------------------------------------------------

bool course::delete_section(int Tnumber) {
	int index = check_section(Tnumber);
	if (index < 0) { cout << "Section is already not added\n";  return true; }
	sections.erase(sections.begin() + index);
	return true;
}
//----------------------------------------------------

bool DELETE_SECTION(catalog* UniCatalog) {
	system("CLS");
	cout << "Deleting Existing Section\n";
	string courseNumber;
	cout << "Course Number: "; cin >> courseNumber;
	int index = UniCatalog->check_course(courseNumber);
	if (index < 0) { cout << "Course Number Not Found in the catalog\n"; return true; }
	course* s_course = UniCatalog->courses_list[index];
	int number;
	cout << "Section Number: "; cin >> number;
	return s_course->delete_section(number);
}
//----------------------------------------------------

bool course::add_preq(string CourseNumber, catalog* Tcatalog) {
	int index = Tcatalog->check_course(CourseNumber);
	if (index < 0) { cout << "Course Not Found in Catalog\n"; return true; }
	preq.push_back(Tcatalog->courses_list[index]);
	return true;
}
//----------------------------------------------------

course::~course() {
	preq.clear();
	int size = sections.size();
	for (int i = 0; i < size; i++) {
		delete(sections[i]);
	}
	sections.clear();
}



//-----------------------------------_________________----------------------------------------
//-----------------------------------|               |----------------------------------------
//-----------------------------------| SECTION CLASS |----------------------------------------
//-----------------------------------|_______________|----------------------------------------

section::section(university* Tuniversity)
{
	number = 0;
	offering_days = "AA";
	start_time = 0.0;
	s_university = Tuniversity;
}
//----------------------------------------------------

section::section(university* Tuniversity, course* Tcourse, int Tnumber, string Tofferings, professor* Tprofessor, float Tstart)
{
	s_course = Tcourse; number = Tnumber; offering_days = Tofferings;
	s_professor = Tprofessor; start_time = Tstart;
	s_university = Tuniversity;
}
//----------------------------------------------------

bool section::register_student(string studentID) {
	int index0 = s_university->check_student(studentID);
	if (index0 < 0) { cout << "Student is not registered in the university\n"; return true; }
	int index1 = check_student(studentID);
	if (index1 >= 0) { cout << "Student is already registered in the section\n";  return true; }
	student_list.push_back(s_university->students_list[index0]);
	return true;
}
//----------------------------------------------------

bool REGISTER_STUDENT(catalog* UniCatalog) {
	system("CLS");
	cout << "Registering a student\n";
	string courseNumber;
	cout << "Course Number: "; cin >> courseNumber;
	int course_index = UniCatalog->check_course(courseNumber);
	if (course_index < 0) { cout << "Course Number Not Found in the catalog\n"; return true; }
	course* s_course = UniCatalog->courses_list[course_index];
	int number;
	cout << "Section Number: "; cin >> number;
	int section_index = s_course->check_section(number);
	if (section_index < 0) { cout << "Section Number Not Found\n";  return true; }
	section* s_section = s_course->sections[section_index];
	cout << "Student ID: "; string student_id; cin >> student_id;
	return s_section->register_student(student_id);
}
//----------------------------------------------------

bool section::unregister_student(string studentID) {
	int index = check_student(studentID);
	if (index < 0) { cout << "Student is already not registered in the section\n";  return true; }
	student_list.erase(student_list.begin() + index);
	return true;
}
//----------------------------------------------------

bool UNREGISTER_STUDENT(catalog* UniCatalog) {
	system("CLS");
	cout << "Unregistering a student\n";
	string courseNumber;
	cout << "Course Number: "; cin >> courseNumber;
	int course_index = UniCatalog->check_course(courseNumber);
	if (course_index < 0) { cout << "Course Number Not Found in the catalog"; return true; }
	course* s_course = UniCatalog->courses_list[course_index];
	int number;
	cout << "Section Number: "; cin >> number;
	int section_index = s_course->check_section(number);
	if (section_index < 0) { cout << "Section Number Not Found\n";  return true; }
	section* s_section = s_course->sections[section_index];
	cout << "Student ID: "; string student_id; cin >> student_id;
	return s_section->unregister_student(student_id);
}
//----------------------------------------------------

int section::check_student(string studentID)
{
	int size = student_list.size();
	for (int i = 0; i < size; i++) {
		if (student_list[i]->id == studentID) return i;
	}
	return -1;
}
//----------------------------------------------------

bool section::list_students() {
	int size = student_list.size();
	for (int i = 0; i < size; i++) {
		cout << student_list[i]->id << "  " << student_list[i]->name << endl;
	}
	return true;
}
//----------------------------------------------------

bool LIST_STUDENTS(catalog* UniCatalog) {
	system("CLS");
	string courseNumber;
	cout << "Course Number: "; cin >> courseNumber;
	int course_index = UniCatalog->check_course(courseNumber);
	if (course_index < 0) { cout << "Course Number Not Found in the catalog\n"; return true; }
	course* s_course = UniCatalog->courses_list[course_index];
	int number;
	cout << "Section Number: "; cin >> number;
	int section_index = s_course->check_section(number);
	if (section_index < 0) { cout << "Section Number Not Found\n";  return true; }
	section* s_section = s_course->sections[section_index];
	return s_section->list_students();
}
//----------------------------------------------------

section::~section()
{
	student_list.clear();
}


//------------------------ADDITIONAL FUNCTIONS------------------------------------------
void welcome() {
	system("CLS");
	cout << "Welcome to AUC Menu" << endl
		<< "1. Course Menu" << endl
		<< "2. Section Menu" << endl
		<< "3. Professor Menu" << endl
		<< "4. Student Menu" << endl
		<< "5. List all courses (list all courses in the catalog)" << endl
		<< "6. Exit" << endl;
}
//----------------------------------------------------

void CourseMenu() {
	system("CLS");
	cout << "Course Menu" << endl
		<< "1. Add course(make sure no two duplicate course numbers exist)" << endl
		<< "2. Modify course(selected by the course number)" << endl
		<< "3. Delete course(selected by the course number)" << endl
		<< "4. List all sections(selected by the course number)" << endl
		<< "5. Back" << endl;
}
//----------------------------------------------------

void SectionMenu() {
	system("CLS");
	cout << "Section Menu" << endl
		<< "1. Create section" << endl
		<< "2. Modify section(selected by the course number and section number)" << endl
		<< "3. Delete section(selected by the course number and section number)" << endl
		<< "4. Register student(for a course number, section number, and student id)" << endl
		<< "5. Unregister student(for a course number, section number, and student id)" << endl
		<< "6. List all students(for a course number, section number)" << endl
		<< "7. Back" << endl;
}
//----------------------------------------------------

void ProfessorMenu() {
	system("CLS");
	cout << "Professor Menu" << endl
		<< "1. New Professor(make sure the id is unique)" << endl
		<< "2. Delete Professor(by professor id)" << endl
		<< "3. List Professors(by professor id)" << endl
		<< "4. Back" << endl; 
}
//----------------------------------------------------

void StudentMenu() {
	system("CLS");
	cout << "Student Menu" << endl
		<< "1. New Student(make sure student id is unique)" << endl
		<< "2. Delete Student(by student id)" << endl
		<< "3. List Students(by student id)" << endl
		<< "4. Back" << endl;
}
//----------------------------------------------------

void modify_course_display(course* Tcourse) {
	system("CLS");
	cout << "Course no. " << Tcourse->number << endl
		<< "Choose what you want to edit\n"
		<< "1. Number" << endl
		<< "2. Name" << endl
		<< "3. Number of Credit Hours" << endl
		<< "4. Description" << endl
		<< "5. Back" << endl;
}
//----------------------------------------------------

void modify_section_display(section* Tsection) {
	system("CLS");
	cout << "Course no. " << Tsection->s_course->number << " Section no. " << Tsection->number << endl
		<< "Choose what you want to edit\n"
		<< "1. Number" << endl
		<< "2. offering days" << endl
		<< "3. Professor" << endl
		<< "4. Start time" << endl
		<< "5. Back" << endl;
}
//----------------------------------------------------

int menu_input(int lower, int upper) {
	int input;
	cout << "Open: "; cin >> input;
	while (input<lower || input>upper) {
		cout << "Enter a number between " << to_string(lower) << " and " << to_string(upper) << endl;
		cin >> input;
	}
	return input;
}
//----------------------------------------------------

bool return_menu() {
	int exit;
	cout << "-------------------------------------------------\n" 
		<< "1. Return to the previous menu\n"
		<< "2. Exit\n";
	exit = menu_input(1, 2);
	if (exit == 1) return true;
	return false;
}
//----------------------------------------------------

professor::professor()
{
	name = "Professor";
	id = "0000";
}
//----------------------------------------------------

student::student()
{
	name = "Student";
	id = "00";
	gpa = 4.00;
}
//----------------------------------------------------

void catalog::load_courses(string text_file) {
	ifstream courses_file;
	courses_file.open(text_file);
	char f;
}
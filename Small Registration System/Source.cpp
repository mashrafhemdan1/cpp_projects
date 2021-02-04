#include "common.h"

int main() 
{
	bool go_back = false;
	int input;
	//some declarations
	catalog* catalog20 = new catalog();
	university* AUC = new university(catalog20);
	catalog20->academic_year = "2020";
	catalog20->c_university = AUC;
	do {
		welcome(); //(1) course (2) section (3) professor (4) student (5)list courses (6)exit
		input = menu_input(1, 6);
		if (input == 6) break;
		switch (input) {
		case (1): //Course Menu
			do {
				CourseMenu(); //(1) add course (2) modify course (3) delete course (4) list all sections (5) back
				input = menu_input(1, 5);
				if (input == 5) { go_back = true; break; }
				switch (input) {
				case (1):
					catalog20->add_course();
					go_back = return_menu();
					break;

				case (2):
					go_back = catalog20->modify_course();
					if(go_back == true) go_back = return_menu();
					break;

				case (3):
					catalog20->delete_course();
					go_back = return_menu();
					break;

				case (4):
					go_back = LIST_SECTIONS(catalog20);
					if (go_back == true) go_back = return_menu();
					break;

				}
			} while (go_back);
			break;

		case (2): //Section Menu
			do {
				SectionMenu(); //(1)create section  (2)modify section  (3)delete section  (4)register student  (5)unregister studetn  (6)list students  (7)back
				input = menu_input(1, 7);
				if (input == 7) { go_back = true; break; }
				switch (input) {
				case(1): //create section
					go_back = ADD_SECTION(catalog20);
					if (go_back == true) go_back = return_menu();
					break;

				case(2): //modify section
					go_back = MODIFY_SECTION(catalog20);
					if (go_back == true) go_back = return_menu();
					break;

				case(3): //delete section
					go_back = DELETE_SECTION(catalog20);
					if (go_back == true) go_back = return_menu();
					break;

				case(4): //register a student
					go_back = REGISTER_STUDENT(catalog20);
					if (go_back == true) go_back = return_menu();
					break;

				case(5): //unregister a student
					go_back = UNREGISTER_STUDENT(catalog20);
					if (go_back == true) go_back = return_menu();
					break;

				case(6): //lists students by section
					go_back = LIST_STUDENTS(catalog20);
					if (go_back == true) go_back = return_menu();
					break;

				}
			} while (go_back);
			break;

		case (3): //Professor Menu
			do {
				ProfessorMenu(); //(1)new professor  (2)delete prof  (3)list profs  (4)back
				input = menu_input(1, 4);
				if (input == 4) { go_back = true; break; }
				switch (input) {
				case(1): //new professor
					go_back = ADD_PROFESSOR(AUC);
					if (go_back == true) go_back = return_menu();
					break;

				case(2):
					go_back = DELETE_PROFESSOR(AUC);
					if (go_back == true) go_back = return_menu();
					break;

				case(3):
					AUC->list_professors();
					go_back = return_menu();
					break;
				}
			} while (go_back);
			break;

		case (4):  //Student Menu
			do {
				StudentMenu(); //(1)new student  (2)delete student  (3)list students  (4)back
				input = menu_input(1, 4);
				if (input == 4) { go_back = true; break; }
				switch (input) {
				case(1)://new Student
					go_back = ADD_STUDENT(AUC);
					if (go_back == true) go_back = return_menu();
					break;

				case(2): //delete student
					go_back = DELETE_STUDENT(AUC);
					if (go_back == true) go_back = return_menu();
					break;

				case(3):
					AUC->list_students();
					go_back = return_menu();
					break;
				}
			} while (go_back);
			break;

		case (5):  //List Courses
			catalog20->list_courses();
			go_back = return_menu();
			break;
		}
	} while (go_back);
	cout << "Thank you for using SHORBA registration system\n";
	return 0;
}
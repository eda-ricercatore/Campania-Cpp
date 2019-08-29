/**
 * Zhiyang Ong
 *
 * Assume that phone numbers can be duplicated since students can be siblings,
 * relatives, or friends living in the same house, where the same line phone
 * is shared between them
 *
 * @acknowledgement - code samples/examples from the web page
 *	<http://www-scf.usc.edu/~csci455/>; they are written by
 *	Dr. K. Narayanaswamy
 * @reference: D.S. Malik, "C++ Programming: Program Design Including Data
 *	Structures", Second Edition, Thomson Technology, USA, 2004, pp. 1167.
 */

// Including header files
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <climits>
#include <cfloat>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
using namespace std;
//#include "Student.h"
#include "StudentDB.h"
#include "Undergraduate.h"
#include "Graduate.h"
#ifndef __STUDENTDB
#define __STUDENTDB
// ==========================================================================

// Declaring constants...
// Maximum number of students that can be placed in the table
const int MAXIMUM_NUMBER_OF_STUDENTS=50;
// Number of delimiter characters to be deleted
const int NUMBER_OF_DELIMITER_CHARACTERS=1;
// Indices of the delimiters (dashes) in the US social security numbers
const int INDEX_FIRST_DELIMITER=3;
const int INDEX_SECOND_DELIMITER=6;
// Maximum number of characters in the any field
const int MAXIMUM_NUMBER_OF_CHARACTERS=20;
// Maximum number of characters for the thesis
const int MAXIMUM_CHARACTERS_OF_MAJOR=5;
// Maximum number of characters for the name of the Undergraduate student's advisor
const int MAXIMUM_CHARACTERS_OF_MINOR=5;
// Maximum number of characters for the thesis
const int MAXIMUM_CHARACTERS_OF_THESIS=20;
// Maximum number of characters for the name of the graduate student's advisor
const int MAXIMUM_CHARACTERS_OF_ADVISOR=15;
// Graduate student status
const string GRADUATE_STATUS="GRADUATE";
// Undergraduate student status
const string UNDERGRADUATE_STATUS="UNDERGRADUATE";

// Declare and nitialize variables...
// Database that stores the correct student records
Student student_records[MAXIMUM_NUMBER_OF_STUDENTS];

// ------------------------------------------------------------------

// Default constructor
StudentDB::StudentDB() {
	number_correct_records=0;
	index_of_last_element=-1;
}

// ------------------------------------------------------------------

/**
 * Fuunction to read input from a file and process it
 * #Read the particulars of each student in a line with the following format:
 *	Last_name	First_name	Social_Security_Number	Telephone	Age
 * Assume that the input file will contain data in this format
 * @param inputfilename is the name of the input file
 */
bool StudentDB::import_database(string inputfilename) {
	
	// Create input file stream
	ifstream inputfile;
	// Open the input file
	inputfile.open(inputfilename.c_str());
	// Assertion to check if the input file exist
	if(inputfile == NULL) {
		cout << "Input file, with the filename " << inputfilename
			<< ", does not exist!" << endl;
		return false;
	}
	
	
	/**
	 * Declare and instantiate some variables to temporarily store data
	 * before processing them
	 */
	// Last name of the student
	string lastname="";
	// First name of the student
	string firstname="";
	// Student's social security number
	string socialsecuritynumber="";
	// Student's phone number in the united states
	string phonenumber="";
	// Student's age
	int studentage=0;
	// Undergraduate's minor
	string minor_title;
	// Undergraduate's major
	string major_title;
	// Name of graduate's advisor
	string advisor_name;
	// Title of graduate's thesis
	string thesis_title;
	// Status of the student - undergraduate or graduate
	string student_status;
	// Number of errors found in the student record
	int errors=0;
	// Current index in which correct student record should be stored
	int correct_index;
	/**
	 * Temporary store the social security number so that it's dashes can be
	 * removed without modifying the social_security_number field of the
	 * student
	 */
	string temp_ssn="";
	
	Student *tempStudent = new Student();
	
	/**
	 * Current index of the record of student particulars
	 * that is being enumerated
	 */
	int i=0;
	// Start processing the data in the table
	while(inputfile != NULL) {
		/**
		 * Stop processing the input file once its end has been reached
		 * Assume that all students are undergraduates by default
		 */
		if ( (inputfile >> student_status >> lastname	>> firstname
			>> socialsecuritynumber >> phonenumber >> studentage
			>> major_title >> minor_title) == NULL) {
			break;
		}

		i++;
		
		uppercase(student_status);
		
		/**
		 * Check if the student particulars are valid...
		 * If any of the student particulars is invalid,
		 * ignore this current line in the input file and
		 * skip to the next
		 */
		if(student_status == GRADUATE_STATUS) {
			advisor_name = major_title;
			thesis_title = minor_title;

if(advisor_name == thesis_title) {
cout << "Wrong thesis-advisor assignment" << endl;
}

			major_title="";
			minor_title="";
		}else if((student_status == UNDERGRADUATE_STATUS)
			&& (!check_major(major_title))) {
			cout << "\t Ignoring Record Number " << i <<
				" - invalid major" << endl;
			cout << "\t\t Major should contain no more than 5 "
				<< "characters, and no whitespace" << endl;
			// I guess that's 2 more years in college of poor/no income for you
			errors++;
			continue;
		}else if((student_status == UNDERGRADUATE_STATUS)
			&& (!check_minor(minor_title))) {
			cout << "\t Ignoring Record Number " << i <<
				" - invalid minor" << endl;
			cout << "\t\t Minor should contain no more than 5 "
				<< "characters, and no whitespace" << endl;
			// One more semester of cheap food in college, I guess
			errors++;
			continue;
		}else if((student_status != UNDERGRADUATE_STATUS)
			&& (student_status != GRADUATE_STATUS)) {
			cout << "\t Ignoring Record Number " << i <<
				" - poor student status" << endl;
//cout << "student_status is: " << student_status << endl;
//cout << check_major(minor_title) << endl;
//cout << check_minor(major_title) << endl;
//cout << (student_status == UNDERGRADUATE_STATUS) << endl;
			cout << "\t\t A student must either be a graduate"
				<< " or undergraduate student" << endl;
			errors++;
			continue;
		}
		
		if((student_status == GRADUATE_STATUS) && (!check_thesis(thesis_title))) {
			cout << "\t Ignoring Record Number " << i <<
				" - poor thesis title" << endl;
			cout << "\t\t Thesis title should contain no more than 20 "
				<< "characters, and no whitespace" << endl;
			// How did you pass Quals???
			errors++;
			continue;
		}
		
		if((student_status == GRADUATE_STATUS) && (!check_advisor(advisor_name))) {
			cout << "\t Ignoring Record Number " << i <<
				" - invalid advisor name" << endl;
			cout << "\t\t Name of the graduate student's advisor should "
				<< "only contain alphabets, and be less than 15 characters"
				<< endl;
			// You should retake Quals...
			errors++;
			continue;
		}
		
		if(!check_lastname(lastname)) {
			cout << "\t Ignoring Record Number " << i <<
				" - bad last name" << endl;
			cout << "\t\t Last name of the student should only contain "
				<< "alphabets" << endl;
			errors++;
			continue;
		}else if(!check_firstname(firstname)) {
			cout << "\t Ignoring Record Number " << i <<
				" - bad first name" << endl;
			cout << "\t\t First name of the student should only contain "
				<< "alphabets" << endl;
			errors++;
			continue;
		}else if(!check_socialsecuritynumber(socialsecuritynumber)) {
			cout << "\t Ignoring Record Number " << i <<
				" - bad social security number" << endl;
			cout << "\t\t Security numbers should contain dashes at the "
				<< "4th and 7th characters, and digits otherwise" << endl;
			errors++;
			continue;
		}else if(!check_phonenumber(phonenumber)) {
			cout << "\t Ignoring Record Number " << i 
				<< " - bad phone number" << endl;
			cout << "\t\t Phone numbers should be given in this format: "
				<< "(XXX)XXX-XXXX, where each X is a digit" << endl;
			errors++;
			continue;
		}else if(!check_studentage(studentage)) {
			cout << "\t Ignoring Record Number " << i << " - bad age" << endl;
			cout << "\t\t Age of the student should be between 1 and 120, "
				<< "inclusive" << endl;
			errors++;
			continue;

		}else if(!check_duplicate_social_security_number(socialsecuritynumber)) {
			cout << "\t Ignoring Record Number " << i <<
				" - duplicate social security number" << endl;
			cout << "\t\t A student with the social security number, "
				<< socialsecuritynumber << ", already exists in the database"
				<< endl;
			errors++;
			continue;
		}

		/**
		 * Student's first and last names, social security number, phone
		 * number, and age are valid...
		 * Enter these details into the appropriate place in the records
		 */
		correct_index=i-errors-1;
		// Creating a student record
		
		if(student_status == GRADUATE_STATUS) {
/*
			tempStudent = new Graduate();
			tempStudent->set_thesis(thesis_title);
			tempStudent->set_advisor(advisor_name);
*/
Graduate *ngrad = new Graduate();
ngrad->set_thesis(thesis_title);
ngrad->set_advisor(advisor_name);
ngrad->set_lastname(lastname);
ngrad->set_firstname(firstname);
ngrad->set_ssn(socialsecuritynumber);
ngrad->set_phone(phonenumber);
ngrad->set_age(studentage);
if(!add_student(ngrad)) {
			cout << "Error in adding graduate student!" << endl;
			continue;
}
		}else{
/*
			tempStudent = new Undergraduate();
			tempStudent->set_minor(minor_title);
			tempStudent->set_major(major_title);
*/
Undergraduate *nugrad = new Undergraduate();
nugrad->set_minor(minor_title);
nugrad->set_major(major_title);
nugrad->set_lastname(lastname);
nugrad->set_firstname(firstname);
nugrad->set_ssn(socialsecuritynumber);
nugrad->set_phone(phonenumber);
nugrad->set_age(studentage);
if(!add_student(nugrad)) {
			cout << "Error in adding undergraduate student!" << endl;
			continue;
}
		}
/*
		tempStudent->set_lastname(lastname);
		tempStudent->set_firstname(firstname);
		tempStudent->set_ssn(socialsecuritynumber);
		tempStudent->set_phone(phonenumber);
		tempStudent->set_age(studentage);

		if(!add_student(tempStudent)) {
			cout << "Error in adding student!" << endl;
			continue;
		}
*/
	}
	
	cout << endl;
	cout << "Processed " << i << " student records" << endl;
	cout << (errors) << " errors were found" << endl;
	cout << endl;
	// Determine the number of correct student records
	number_correct_records=i-errors;
	
	// Close the input filestream
	inputfile.close();
	
	return true;
}


/**
 * Function to write output to a file
 * #Print the particulars of each student in a line with the following format:
 *	Last_name	First_name	Social_Security_Number	Telephone	Age
 * @param outputfilename is the name of the output file
 */
bool StudentDB::export_database(string outputfilename) {
	
	// Create output file stream
	ofstream outputfile;
	/**
	 * Convert outputfilename to string in C so that the file I/O function
	 * in the C++ library can be utilised
	 */
	outputfile.open(outputfilename.c_str());
	// Assertion to check if the output file was opened properly
	if(outputfile == NULL) {
		cout << "Output file, with the filename " << outputfilename
			<< ", does not exist!" << endl;
		return false;
	}
	
	
	// Left align the data
	outputfile.setf(ios::left);
	// Print the student records...
	
	// Enurmerate the list and print the students' details to the file
	Student_list_pointer p = database.begin();
	while(p != database.end()) {
		(*p) -> write_to_stream(outputfile);

		p++;
	}

	outputfile << endl;
	
	// Close the output filestream
	outputfile.close();
	return true;
}


/**
 * Function to convert all letters in the string s to uppercase
 * @param s is the string to be converted to uppercase
 */
void StudentDB::uppercase (string & s) {
	// For all characters in s
	for (int i=0; i < s.size(); i++) {
		// change it to uppercase
		s[i] = toupper(s[i]);
	}
}


/**
 * Function to check it the student's last name is valid
 * @param lastname is the last name of the student
 * @return true if the last name includes only alphabetic characters;
 *	else, return false.
 *	Hence, names of people that include non-alphabetic characters
 *	will be considered invalid. This is a current program limitation
 *	given the assignment's specification. It should allow names with
 *	special characters to be valid, e.g. some European names with
 *	accented characters
 */
bool StudentDB::check_lastname(string lastname) {
//cout<<"ln pre for"<<endl;
	for (int i=0; i < lastname.size(); i++) {
		// Are there any non-alphabetic characters?
		if (!isalpha(lastname[i])) {
			// Yes, ths last name is invalid

			return false;
		}

	}
	return true;
}


/**
 * Function to check it the student's first name is valid
 * @param firstname is the first name of the student
 * @return true if the first name includes only alphabetic characters;
 *	else, return false.
 *	Hence, names of people that include non-alphabetic characters
 *	will be considered invalid. This is a current program limitation
 *	given the assignment's specification. It should allow names with
 *	special characters to be valid, e.g. some European names with
 *	accented characters
 */
bool StudentDB::check_firstname(string firstname) {

	for (int i=0; i < firstname.size(); i++) {
		// Are there any non-alphabetic characters?

		if (!isalpha(firstname[i])) {
			// Yes, the last name is invalid

			return false;
		}
	}
	return true;
}


/**
 * Function to check if the social security number is valid
 * @param ssn is a possible valid social security number of a
 *	student; ssn must contain only digits in all characters except
 *	the 4th and 7th, which are dashes
 * @return true if ssn is valid; else, return false
 */
bool StudentDB::check_socialsecuritynumber(string ssn) {
	for (int i=0; i < ssn.size(); i++) {
		/**
		 * Are there any non-digits in characters that are supposed
		 * to be digits?
		 */
		if ((i != 3) && (i != 6) && (!isdigit(ssn[i]))) {
			// Yes, the ssn is invalid
			return false;
		}else if(((i == 3) || (i == 6)) && (ssn[i]!='-')) {
			return false;
		}
	}
	return true;
}


/**
 * Function to check if the phone number is valid
 * @param phonenumber is a possible valid phone number of a
 *	student; phonenumber must contain only digits in all characters
 *	 except the 1st ('('), 5th (')'), and 9th ('-')
 * @return true if phonenumber is valid; else, return false
 */
bool StudentDB::check_phonenumber(string phonenumber) {
	for (int i=0; i < phonenumber.size(); i++) {
		/**
		 * Are there any non-digits in characters that are supposed
		 * to be digits?
		 */
		if ((i == 0) && (phonenumber[i] != '(')) {
			// Yes, the phonenumber is invalid
			return false;
		}else if((i == 4) && (phonenumber[i]!=')')) {
			return false;
		}else if ((i == 8) && (phonenumber[i]!='-')) {
			// Yes, the phonenumber is invalid
			return false;
		}else if((!isdigit(phonenumber[i])) && (i!=0) && (i!=4) &&(i!=8)) {
			// Yes, the phonenumber is invalid
			return false;
		}
	}
	return true;
}


/**
 * Function to check if the student's age is valid
 * @param age is the age of the student; it should not be over 120,
 *	and it must be greater than 0.
 *	Needs more information since it makes no sense to have a toddler
 *	pursuing a Ph.D. in Computer Engineering or Biochemistry;
 *	assertions for this method implementation suffice according to
 *	the requirements of the assignment
 * @return true if age is valid; else, return false
 */
bool StudentDB::check_studentage(int age) {
	if((age<1) || (age>120)) {
		return false;
	}else{
		return true;
	}
}


/**
 * Function to check if the student's social security number is a duplicate
 * Social security numbers are uniquely assigned to each individual;
 * hence, there shall be no duplicates
 * @param ssn is the social security number
 * @param student_particulars is the student database
 * @param current_index is the current index of the student in the database
 * @return true if social security number is not a duplicate;
 *	else, return false
 */
bool StudentDB::check_duplicate_social_security_number(string ssn) {

	Student_list_pointer p = database.begin();
	
	while(p != database.end()) {
		if(((*p)->get_ssn()) == ssn) {
			return false;
		}
		p++;
	}

	return true;
}


/**
 * Function to determine if the minor title of the Undergraduate student
 * is valid
 * Assume that all Undergraduate students have to select a major
 * and minor each
 * Minor title can contain any character; number of characters must be
 * less than 6 (<= 5), and no white space is allowed.
 * @param minor_title is the minor of the Undergraduate student
 * @return true if minor title is valid; else, return false
 */
bool StudentDB::check_minor(string minor_title) {
	if (minor_title.size() > MAXIMUM_CHARACTERS_OF_MINOR) {
		// Minor title is too long
		return false;
	}else{
		return true;
	}
}


/**
 * Function to determine if the major of the Undergraduate student
 * is valid
 * Assume that all Undergraduate students have to select a major
 * and minor each
 * Major title can contain any character; number of characters must be
 * less than 6 (<= 5), and no white space is allowed.
 * @param major_title is the major title of the Undergraduate student
 * @return true if major title is valid; else, return false
 */
bool StudentDB::check_major(string major_title) {
	if (major_title.size() > MAXIMUM_CHARACTERS_OF_MAJOR) {
		// Major title is too long
		return false;
	}else{
		return true;
	}
}


/**
 * Function to determine if the title of the graduate student's thesis
 * is valid
 * Assume that all graduate students have to write a thesis each
 * Thesis title can contain any character; number of characters must be
 * less than 21 (<= 20), and no white space is allowed.
 * @param thesis_title is the title of the graduate student's thesis
 * @return true if thesis title is valid; else, return false
 */
bool StudentDB::check_thesis(string thesis_title) {
	if (thesis_title.size() > MAXIMUM_CHARACTERS_OF_THESIS) {
		// Thesis title is too long
		return false;
	}else{
		return true;
	}
}


/**
 * Function to determine if the name of the graduate student's advisor
 * is valid
 * Assume that all graduate students have to undertake a research project each
 * Advisor's name can contain only alphabetic characters of a length
 * less than or equal to 15
 * Assume that no advisor's name will exceed 20 characters
 * @param advisor_name is the name of the graduate student's advisor
 * @precondition advisor_name must be a valid name
 * @return nothing
 */
bool StudentDB::check_advisor(string advisor_name) {
	if(advisor_name.size() > MAXIMUM_CHARACTERS_OF_ADVISOR) {
		return false;
	}

	for (int i=0; i < advisor_name.size(); i++) {
		// Are there any non-alphabetic characters?
		if (!isalpha(advisor_name[i])) {
			// Yes, the advisor name is invalid
			return false;
		}
	}
	return true;
}


/**
 * Function to display the particulars of a students
 * @param index is the index of the student, whose details are to be displayed
 */
bool StudentDB::display_student(string ssn) {
	cout.setf(ios::left);

	Student_list_pointer p = database.begin();
	while(p != database.end()) {
		if(strcmp((*p)->get_ssn().c_str(),
			ssn.c_str()) == 0) {
/*			
			cout.width(16);
			if((*p)->get_graduate()) {
				cout << "Graduate";
			}else{
				cout << "Undergraduate";
			}

			cout.width(16);
			cout << (*p) -> get_lastname();
			cout.width(16);
			cout << (*p) -> get_firstname();
			cout.width(16);
			cout << (*p) -> get_ssn();
			cout.width(16);
			cout << (*p) -> get_phone();
			cout.width(16);
			cout << (*p) -> get_age();
			
			if((*p)->get_graduate()) {
				cout.width(16);
				cout << (*p) -> get_advisor();
				cout.width(16);
				cout << (*p) -> get_thesis();
			}else{
				cout.width(16);
				cout << (*p) -> get_major();
				cout.width(16);
				cout << (*p) -> get_minor();
			}
			cout << endl;
*/			
			(*p) -> display();
			return true;
		}
		p++;
	}

	return false;
}


/**
 * Function to add a student's particulars to the database
 * @param student_details contain the student's particulars
 * @param student student_particulars contain the database
 * If this student's social security number is not found in the database,
 * then the student is added to the database
 * Else, the user is informed that another student has the same social security
 * number as this student. Hence, this student's record cnnot be added to the
 * database.
 */
bool StudentDB::add_student(Student * student_details) {

	// List is empty and uninitialized
	Student_list_pointer p = database.begin();
	
	if(get_number_correct_records()==0) {
		database.push_back(student_details);
		increment_index_of_last_element();
		set_number_correct_records(get_index_of_last_element()+1);

		return true;
	}
	
	while(p != database.end()) {
		if(strcmp((*p)->get_ssn().c_str(),
			student_details->get_ssn().c_str()) >0) {
			
			database.insert(p, student_details);

			return true;
		}else if(strcmp((*p)->get_ssn().c_str(),
			student_details->get_ssn().c_str()) == 0) {
			
			cout << "A student with the social security number, "
				<< (*p)->get_ssn()
				<< ", already exists in the database"
				<< endl;
			return false;
		}
		p++;

	}

	database.push_back(student_details);
	increment_index_of_last_element();
	set_number_correct_records(get_index_of_last_element()+1);
	return true;
}


/**
 * Function to delete a student's details from the database
 * @param student_details contain the student's social security number
 * @param student student_particulars contain the database
 * If this student's social security number is not found in the database,
 * then this student's details cannot be removed from the database
 * Else, this student's record is removed from the database.
 */
bool StudentDB::delete_student(string ssn) {
	if(!check_socialsecuritynumber(ssn)) {
		cout << "Social security number entered is invalid" << endl;
		return false;
	}else{
		Student_list_pointer p = find_student(ssn);
		
		if(p != database.end()) {
			delete *p;
			database.erase(p);
			decrement_index_of_last_element();
			set_number_correct_records(get_index_of_last_element()+1);
			cout << "Student with the social security number, "
				<< ssn << ", is removed from the database." << endl;
			return true;
		}else{
			cout << "No student in the database has the social"
				<< " security number, "
				<< ssn << "." << endl;
			return false;
		}
	}
}


/**
 * Function to print the header of the terminal session
 */
void StudentDB::print_grad_header() {
	cout << "Graduate Student:" << endl;
	cout.setf(ios::left);
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Last Name";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "First Name";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Social Security #";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Phone #";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Age";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Advisor";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Thesis";
	cout << endl;
}

/**
 * Function to print the header of the terminal session
 */
void StudentDB::print_ugrad_header() {
	cout << "Undergraduate Student:" << endl;
	cout.setf(ios::left);
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Last Name";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "First Name";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Social Security #";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Phone #";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Age";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Major";
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << "Minor";
	cout << endl;
}


/**
 * Function to display the particulars of all students
 */
void StudentDB::display_all() {
	cout.setf(ios::left);

	// Print the grad header...
	print_grad_header();
	Student_list_pointer p =database.begin();
	while(p != database.end()) {
		if((*p)->get_graduate()) {
			(*p) -> display();
		}
		p++;
	}
	
	// Print the undergrad header...
	print_ugrad_header();
	p =database.begin();
	while(p != database.end()) {
		if(!((*p)->get_graduate())) {
			(*p) -> display();
		}
		p++;
	}
}


/**
 * Function to assign the number of correct records in the database
 */
void StudentDB::set_number_correct_records(int num_correct) {
	number_correct_records=num_correct;
}


/**
 * Function to increment the index of the last element
 */
void StudentDB::increment_index_of_last_element() {
	index_of_last_element++;
}


/**
 * Function to decrement the index of the last element
 */
void StudentDB::decrement_index_of_last_element() {
	index_of_last_element--;
}


/**
 * Function to get the number of correct records
 * @return the number of correct records
 */
int StudentDB::get_number_correct_records() {
	return number_correct_records;
}

/**
 * Function to get the index of the last element
 * @return the index of the last element
 */
int StudentDB::get_index_of_last_element() {
	return index_of_last_element;
}


/**
 * Function to find the pointer to a student with the social security
 * number of ssn
 * @param ssn is the social security number of the student you want to
 *	search for.
 * @return the pointer to the student, if that student is found.
 *	Else, return a pointer pointing to the end of the list
 */
Student_list_pointer StudentDB::find_student(string ssn) {
	if(!check_socialsecuritynumber(ssn)) {
		cout << "Social security number entered is invalid" << endl;
		return database.end();
	}else{
		Student_list_pointer p = database.begin();
int j=0;
		while(p != database.end()) {
			if(((*p)->get_ssn()) == ssn) {
//cout<<"p is: "<<j<<endl;
				return p;
			}else{
int j=0;
				p++;
			}
		}
		return database.end();
	}
}
#endif

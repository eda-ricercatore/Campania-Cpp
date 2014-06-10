/**
 * Zhiyang Ong, student number 6004-9194-12,
 * Assignment 7, Introduction to Programming Systems Design
 * CSCI 455, Fall 2005
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

// Declare and nitialize variables...
// Database that stores the correct student records
Student student_records[MAXIMUM_NUMBER_OF_STUDENTS];

// ------------------------------------------------------------------

// Default constructor
StudentDB::StudentDB() {
	number_correct_records=0;
	index_of_last_element=-1;
	
	//database = NULL;
	//last = NULL;
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
	/**
	 * Current index of the record of student particulars
	 * that is being enumerated
	 */
	int i=0;
	// Start processing the data in the table
	while((inputfile != NULL) && (i<MAXIMUM_NUMBER_OF_STUDENTS)) {
//cout << "process me" <<endl;
		// Stop processing the input file once its end has been reached
		if ( (inputfile >> lastname	>> firstname >> socialsecuritynumber
			>> phonenumber >> studentage) == NULL) {
			break;
		}
//cout << "checking" <<endl;
		i++;		
		/**
		 * Check if the student particulars are valid...
		 * If any of the student particulars is invalid,
		 * ignore this current line in the input file and
		 * skip to the next
		 */
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
/*
		}else if(!check_duplicate_social_security_number(socialsecuritynumber)) {
			cout << "\t Ignoring Record Number " << i
				<< " - duplicate social security number" << endl;
			errors++;
			continue;
*/
		}
//cout << "Checks passed" << endl;		
		/**
		 * Student's first and last names, social security number, phone
		 * number, and age are valid...
		 * Enter these details into the appropriate place in the records
		 */
		correct_index=i-errors-1;
		// Creating a student record
		Student *tempStudent = new Student();
		tempStudent->set_lastname(lastname);
//cout << "Modify last name of temp student" << endl;
		tempStudent->set_firstname(firstname);
		tempStudent->set_ssn(socialsecuritynumber);
		tempStudent->set_phone(phonenumber);
		tempStudent->set_age(studentage);
//cout << "End Modification" << endl;
		if(!add_student(tempStudent)) {
//cout << "Error adding student from input file" << endl;
			continue;
		}
//cout << "Next" << endl;
	}
	
	cout << endl;
	cout << "Processed " << i << " student records" << endl;
	cout << (errors+1) << " errors were found" << endl;
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
	
	// Pointer to traverse the list
	//student_element *current;
	// Pointer just before current
	//student_element *trail_current;

	Student_list_pointer p = database.begin();
	while(p != database.end()) {
		outputfile.width(16);
		outputfile << (*p) -> get_lastname();
		outputfile.width(16);
		outputfile << (*p) -> get_firstname();
		outputfile.width(16);
		outputfile << (*p) -> get_ssn();
		outputfile.width(16);
		outputfile << (*p) -> get_phone();
		outputfile.width(16);
		outputfile << (*p) -> get_age();
		outputfile << endl;

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
//cout<<"ln if"<<endl;
			return false;
		}
//cout<<"ln for"<<endl;
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
//cout<<"fn pre for"<<endl;
	for (int i=0; i < firstname.size(); i++) {
		// Are there any non-alphabetic characters?
//cout<<"fn for"<<endl;
		if (!isalpha(firstname[i])) {
			// Yes, the last name is invalid
//cout<<"fn if"<<endl;
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
	
	// Pointer to traverse the list
	//student_element *current;
	// Pointer just before current
	//student_element *trail_current;

	Student_list_pointer p = database.begin();
	
	while(p != database.end()) {
		if(((*p)->get_ssn()) == ssn) {
			return false;
		}
		p++;
	}

//	if(database==NULL) {
/*
		cout << "Student database is empty." << endl;
		cout << "This social security number is not duplicated." << endl;
*/
/*
		return true;
	}else{
		current = database;

		while(current != NULL) {
			if(strcmp(current->value->get_ssn().c_str(),
				ssn.c_str()) == 0) {

				return false;
			}else{
				trail_current = current;
				current = current -> next;
			}
		}
	}
*/
	return true;
}


/**
 * Function to sort the student database according to the students'
 * social security numbers - Insertion sort
 */
/*
void StudentDB::insertion_sort() {
	// Index of the first element that is not in sorting order
	int firstOutOfOrder=0;
	// Index of the linear collection/array to insert the student's particulars
	int location=0;
	// The student's particulars...
	Student current_student;
	
	for(firstOutOfOrder=1; firstOutOfOrder<get_number_correct_records();
		firstOutOfOrder++) {
		
		if(strcmp(student_records[firstOutOfOrder].get_ssn().c_str(),
		student_records[firstOutOfOrder-1].get_ssn().c_str()) < 0) {

			current_student=student_records[firstOutOfOrder];
			location=firstOutOfOrder;
			do {
				student_records[location]=student_records[location-1];
				location--;
			}while((location>0) && (strcmp(student_records[location-1].
				get_ssn().c_str(), current_student.get_ssn().c_str()) > 0));
			
			student_records[location]=current_student;
		}
	}
}
*/


/**
 * Function to search for a particular social security number in the
 * student database - use binary search with recursion implementation
 * @param lowerindex is the lower limt where the search will "start" from
 * @param upperindex is the upper limt where the search will "end"
 * @param ssn is the social security number that is used as a search key
 * @return -1 if no student has a social security number with ssn;
 *	else, return the index of the student in the array with that social
 *	security number
 */
/*
int StudentDB::binary_search(string ssn, int lowerindex, int upperindex) {
	if(!check_socialsecuritynumber(ssn)) {
		cout << "Social security number entered is invalid" << endl;
		return -1;
	}
	
	// Have the indices cross each other?
	if(lowerindex > upperindex) {
		// Yes, no student has this social security number
		return -1;
	// Are the indices equal?
	}else if(lowerindex == upperindex) {
*/
		/**
		 * Yes. Does currently enumerated student have ssn as the social
		 * sequrity number?
		 */
/*
		if(student_records[lowerindex].get_ssn()==ssn) {
			// Yes, current student has this social security number.
			return lowerindex;
		}else{
			// No; no student has this social security number
			return -1;
		}
	}else{
		// lowerindex < upperindex
		// Half the search space and perform recursive search
		int midpoint=(lowerindex + upperindex)/2;
		// Is the search key greater than current value?
		if(strcmp(ssn.c_str(),
			student_records[midpoint].get_ssn().c_str())>0) {
			// Yes, keep on searching recursively
			return binary_search(ssn, midpoint + 1, upperindex);
		// Is the search key less than current value?
		}else if(strcmp(ssn.c_str(),
			student_records[midpoint].get_ssn().c_str())<0) {
			// Yes, keep on searching recursively
			return binary_search(ssn, lowerindex, midpoint - 1);
		}else{
			// No, current student has this social security number.
			return midpoint;
		}
	}
}
*/


/**
 * Function to display the particulars of a students
 * @param index is the index of the student, whose details are to be displayed
 */
bool StudentDB::display_student(string ssn) {
	cout.setf(ios::left);
	
	// Pointer to traverse the list
	//student_element *current;
	// Pointer just before current
	//student_element *trail_current;

	Student_list_pointer p = database.begin();
	while(p != database.end()) {
		if(strcmp((*p)->get_ssn().c_str(),
			ssn.c_str()) == 0) {
			cout.width(16);
			cout << (*p) -> get_lastname();
			cout.width(16);
			cout << (*p) -> get_firstname();
			cout.width(16);
			cout << (*p) -> get_ssn();
			cout.width(16);
			cout << (*p) -> get_phone();
			cout.width(16);
			cout << (*p) -> get_age() << endl;
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
	// Pointer to traverse the list
	//student_element *current;
	// Pointer just before current
	//student_element *trail_current;
		
	// Allocate a new student_element
	//student_element *newelement = new student_element();
	// Place the student pointer into "value" and hook up the pointers
	//newelement->value = student_details;
	//newelement->next = NULL;

	// List is empty and uninitialized
	Student_list_pointer p = database.begin();
	
	if(get_number_correct_records()==0) {
		database.push_back(student_details);
		increment_index_of_last_element();
		set_number_correct_records(get_index_of_last_element()+1);
//cout<<"if statement"<<endl;
		return true;
	}
	
	while(p != database.end()) {
		if(strcmp((*p)->get_ssn().c_str(),
			student_details->get_ssn().c_str()) >0) {
			
			database.insert(p, student_details);
//cout<<"while-if statement"<<endl;
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
//cout<<"while-p++"<<endl;
	}
//cout<<"end while loop"<<endl;
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
void StudentDB::print_header() {
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
	cout << "Age" << endl;
}


/**
 * Function to display the particulars of all students
 */
void StudentDB::display_all() {
	// Print the header...
	print_header();

	cout.setf(ios::left);
	
	// Pointer to traverse the list
	//student_element *current;
	// Pointer just before current
	//student_element *trail_current;

	Student_list_pointer p =database.begin();
	while(p != database.end()) {
		cout.width(16);
		cout << (*p) -> get_lastname();
		cout.width(16);
		cout << (*p) -> get_firstname();
		cout.width(16);
		cout << (*p) -> get_ssn();
		cout.width(16);
		cout << (*p) -> get_phone();
		cout.width(16);
		cout << (*p) -> get_age() << endl;
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
cout<<"p is: "<<j<<endl;
				return p;
			}else{
int j=0;
				p++;
			}
		}
		return database.end();
	}
}

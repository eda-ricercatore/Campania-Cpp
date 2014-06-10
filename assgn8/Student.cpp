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
using namespace std;
#include "Student.h"
// ==========================================================================

// Declaring constants...
// Number of delimiter characters to be deleted
const int NUMBER_OF_DELIMITER_CHARACTERS=1;
// Indices of the delimiters (dashes) in the US social security numbers
const int INDEX_FIRST_DELIMITER=3;
const int INDEX_SECOND_DELIMITER=6;
// Maximum number of characters in the any field
const int MAXIMUM_NUMBER_OF_CHARACTERS=20;

// ------------------------------------------------------------------

// Constructors...
// Default constructor
Student::Student( ) {
	// Fill up the parameters of the Student with default values
	first_name="Firstname";
	last_name="Lastname";
	social_security_number="999-99-9999";
	phone_number="(999)999-9999";
	student_age=120;
};

// Standard constructor - provide 3 parameters
Student::Student(string ssn, string lastname, int age) {
	// Fill up the parameters of the Student with values that are passed in
	last_name=lastname;
	social_security_number=ssn;
	student_age=age;
	// Fill up the remaining parameters with default values
	first_name="Firstname";
	phone_number="(999)999-9999";
};

// Standard constructor - provide all parameters
Student::Student(string firstname, string lastname, string ssn,
	string phone_num, int age) {

	// Fill up the parameters of the Student with values that are passed in
	first_name=firstname;
	last_name=lastname;
	social_security_number=ssn;
	phone_number=phone_num;
	student_age=age;
};

// ------------------------------------------------------------------

// Modifier/accessor functions...

/**
 * Function to assign the US Social Security number of the student
 * It must contain digits in all places, except dashes '-' in positions
 * 4 and 7
 * @param ssn is the assigned US Social Security number
 * @pre ssn must be a valid US Social Security number
 * @return true if ssn is valid and assigned; return false otherwise
 */
bool Student::set_ssn(string ssn) {
	// Precondition...
	social_security_number=ssn;
	return true;
}

/**
 * Function to assign the last name of the student
 * It should only contain alphabetic characters
 * @param lastname is the assigned last name of the student
 * @pre lastname must be a valid last name
 * @return true if lastname is valid and assigned; return false otherwise
 */
bool Student::set_lastname(string lastname) {
	// Precondition...
	last_name=lastname;
	return true;
}

/**
 * Function to assign the first name of the student
 * It should only contain alphabetic characters
 * @param firstname is the assigned first name of the student
 * @pre firstname must be a valid first name
 * @return true if firstname is valid and assigned; return false otherwise
 */
bool Student::set_firstname(string firstname) {
	// Precondition...
	first_name=firstname;
	return true;
}

/**
 * Function to assign the US phone number of the student
 * It should only contain '(' as the first character, ')' as the 5th character,
 * and '-' as the 9th character
 * @param phone_num is the assigned phone number of the student
 * @pre phone_num must be a valid phone number
 * @return true if phone_num is valid and assigned; return false otherwise
 */
bool Student::set_phone(string phone_num) {
	// Precondition...
	phone_number=phone_num;
	return true;
}

/**
 * Function to assign the age of the student
 * It should be non-negative (a baby can be 0 years of age)
 * and less than 120 (nobody lives for more than 120 years)
 * @param age is the assigned phone number of the student
 * @pre age must be a valid age
 * @return true if age is valid and assigned; return false otherwise
 */
bool Student::set_age(int age) {
	// Precondition...
	student_age=age;
	return true;
}


// Accessor functions...

/**
 * Function to access the US Social Security number of the student
 * @return the Social Security number of the student
 */
string Student::get_ssn() {
	return social_security_number;
}

/**
 * Function to access the last name of the student
 * @return the last name of the student
 */
string Student::get_lastname() {
	return last_name;
}

/**
 * Function to access the first name of the student
 * @return the first name of the student
 */
string Student::get_firstname() {
	return first_name;
}

/**
 * Function to access the phone number of the student
 * @return the phone number of the student
 */
string Student::get_phone() {
	return phone_number;
}

/**
 * Function to access the age of the student
 * @return the age of the student
 */
int Student::get_age() {
	return student_age;
}
               
// Query functions...

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
bool Student::check_last_name(string lastname) {
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
bool Student::check_first_name(string firstname) {
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
bool Student::check_social_security_number(string ssn) {
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
bool Student::check_phone_number(string phonenumber) {
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
bool Student::check_age(int age) {
	if((age<1) || (age>120)) {
		return false;
	}else{
		return true;
	}
}
		   
/**
 * Function to display student data to the terminal
 */
void Student::display() {
	cout.setf(ios::left);
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_lastname();
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_firstname();
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_ssn();
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_phone();
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_age() << endl;
}

// write student data to an output file stream that has been opened
void Student::write_to_stream(ofstream & outputfile) {
	// Left align the data
	outputfile.setf(ios::left);
	outputfile.width(16);
	outputfile << Student::get_lastname();
	outputfile.width(16);
	outputfile << get_firstname();
	outputfile.width(16);
	outputfile << get_ssn();
	outputfile.width(16);
	outputfile << get_phone();
	outputfile.width(16);
	outputfile << get_age() << endl;
	outputfile << endl;
}

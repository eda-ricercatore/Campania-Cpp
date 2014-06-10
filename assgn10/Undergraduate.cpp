// Importing header files...
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Undergraduate.h"
// ==========================================================================

// Declaring constants...
// Maximum number of characters for the thesis
const int MAXIMUM_CHARACTERS_OF_MAJOR=5;
// Maximum number of characters for the name of the Undergraduate student's advisor
const int MAXIMUM_CHARACTERS_OF_MINOR=5;
// Maximum number of characters in the any field
const int MAXIMUM_NUMBER_OF_CHARACTERS=20;

// ------------------------------------------------------------------

// Constructors...
// Default constructor
Undergraduate::Undergraduate()
{
	/**
	 * Automatically initialize the Student Attributes by default
	 * Student constructor
	 */
	if(set_ssn("999-99-9999") &&
		set_lastname("Lastname") &&
		set_firstname("Firstname") &&
		set_phone("(999)999-9999") &&
		set_age(120)) {
		
		// Do nothing...
	}else{
		cout << "Default constructor of the Undergraduate student has errors"
			<< endl;
	}
	major = "BME";
	minor = "PHIL";
}

// Standard constructor - provide 3 parameters
Undergraduate::Undergraduate(string ssn, string lastname, int age)
{
	/**
	 * Automatically initialize the Student Attributes by default
	 * Student constructor
	 */
	if(set_ssn(ssn) &&
		set_lastname(lastname) &&
		set_firstname("Firstname") &&
		set_phone("(999)999-9999") &&
		set_age(age)) {
		
		// Do nothing...
	}else{
		cout << "Default constructor of the Undergraduate student has errors"
			<< endl;
	}
	
	major = "BME";
	minor = "PHIL";
}

// Standard constructor - provide 5 parameters
Undergraduate::Undergraduate(string firstname, string lastname, string ssn,
	string phone_num, int age)
{
	/**
	 * Automatically initialize the Student Attributes by default
	 * Student constructor
	 */
	if(set_ssn(ssn) &&
		set_lastname(lastname) &&
		set_firstname(firstname) &&
		set_phone(phone_num) &&
		set_age(age)) {
		
		// Do nothing...
	}else{
		cout << "Default constructor of the Undergraduate student has errors"
			<< endl;
	}
	
	major = "BME";
	minor = "PHIL";
}


// Standard constructor - provide all parameters
Undergraduate::Undergraduate(string firstname, string lastname, string ssn,
	string phone_num, int age, string major_title, string minor_title)
{
	/**
	 * Automatically initialize the Student Attributes by default
	 * Student constructor
	 */
	if(set_ssn(ssn) &&
		set_lastname(lastname) &&
		set_firstname(firstname) &&
		set_phone(phone_num) &&
		set_age(age)) {
		
		set_major(major_title);
		set_minor(minor_title);
	}else{
		cout << "Default constructor of the Undergraduate student has errors"
			<< endl;
	}
}
// ------------------------------------------------------------------

// Modifier/accessor functions...
/**
 * Function to assign/update the major of the undergraduate student
 * Assume that all Undergraduate students have to select a major
 * and minor each
 * @param major_title is the title of the Undergraduate student's major
 * @precondition major_title must be a valid major title;
 *	it must contain no whitespace and be less than 6 characters
 * @return nothing
 */
void Undergraduate::set_major (string major_title) {
	if(check_major(major_title)) {
		major = major_title;
	}else{
		major = major_title.substr(0,MAXIMUM_CHARACTERS_OF_MAJOR);
	}
}

/**
 * Function to assign/update the minor of the undergraduate student
 * Assume that all Undergraduate students have to select a major
 * and minor each
 * @param minor_title is the title of the Undergraduate student's minor
 * @precondition minor_title must be a valid minor title;
 *	it must contain no whitespace and be less than 6 characters
 * @return nothing
 */
void Undergraduate::set_minor (string minor_title) {
	if(check_minor(minor_title)) {
		minor = minor_title;
	}else{
		minor = minor_title.substr(0,MAXIMUM_CHARACTERS_OF_MINOR);
	}
}
		
// Accessor functions
/**
 * Function to obtain the major of the Undergraduate student
 * Assume that all Undergraduate students have to select a major
 * and minor each
 * @return major of Undergraduate student
 */
string Undergraduate::get_major ( ) {
	return major;
}


/**
 * Function to access the minor of the Undergraduate student
 * Assume that all Undergraduate students have to select a major
 * and minor each
 * @return minor of the Undergraduate student
 */
string Undergraduate::get_minor( ) {
	return minor;
}


// Query Functions

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
bool Undergraduate::check_minor(string minor_title) {
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
bool Undergraduate::check_major(string major_title) {
	if (major_title.size() > MAXIMUM_CHARACTERS_OF_MAJOR) {
		// Major title is too long
		return false;
	}else{
		return true;
	}
}

// Other functions...

/**
 * Function to display the Undergraduate student's data to the terminal
 */
void Undergraduate::display() {
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
	cout << get_age();
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_major();
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_minor() << endl;
}


/**
 * Function to write Undergraduate student's data to an output file
 * stream that has been opened
 */
void Undergraduate::write_to_stream (ofstream & outputfile) {
	// Left align the data
	outputfile.setf(ios::left);
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << "Undergraduate";
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << Student::get_lastname();
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << get_firstname();
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << get_ssn();
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << get_phone();
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << get_age();
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << get_major();
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << get_minor() << endl;
	//outputfile << endl;
}

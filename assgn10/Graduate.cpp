// Importing header files...
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Graduate.h"
// ==========================================================================

// Declaring constants...
// Maximum number of characters for the thesis
const int MAXIMUM_CHARACTERS_OF_THESIS=20;
// Maximum number of characters for the name of the graduate student's advisor
const int MAXIMUM_CHARACTERS_OF_ADVISOR=15;
// Maximum number of characters in the any field
const int MAXIMUM_NUMBER_OF_CHARACTERS=20;

// ------------------------------------------------------------------

// Constructors...
// Default constructor
Graduate::Graduate()
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
		cout << "Default constructor of the Graduate student has errors"
			<< endl;
	}
	advisor = "GradAdvisor";
	thesis = "Complex-Systems";
	set_graduate();
}

// Standard constructor - provide 3 parameters
Graduate::Graduate(string ssn, string lastname, int age)
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
		cout << "Default constructor of the Graduate student has errors"
			<< endl;
	}
	
	advisor = "GradAdvisor";
	thesis = "Complex-Systems";
	set_graduate();
}

// Standard constructor - provide 5 parameters
Graduate::Graduate(string firstname, string lastname, string ssn,
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
		cout << "Default constructor of the Graduate student has errors"
			<< endl;
	}
	
	advisor = "GradAdvisor";
	thesis = "Complex-Systems";
	set_graduate();
}


// Standard constructor - provide all parameters
Graduate::Graduate(string firstname, string lastname, string ssn,
	string phone_num, int age, string grad_advisor, string thesis_title)
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
		
		set_advisor(grad_advisor);
		set_thesis(thesis_title);
		set_graduate();
	}else{
		cout << "Default constructor of the Graduate student has errors"
			<< endl;
	}
}
// ------------------------------------------------------------------

// Modifier/accessor functions...
/**
 * Function to assign/update the title of the graduate student's thesis
 * Assume that all graduate students have to write a thesis each
 * Thesis title can contain any character; number of characters must be
 * less than 21 (<= 20).
 * @param thesis_title is the title of the graduate student's thesis
 * @precondition thesis_title must be a valid thesis title
 * @return nothing
 */
void Graduate::set_thesis (string thesis_title) {
	if(check_thesis(thesis_title)) {
		thesis = thesis_title;
	}
}

/**
 * Function to assign/update the name of the graduate student's advisor
 * Assume that all graduate students have to undertake a research project each
 * Advisor's name can contain only alphabetic characters of a length
 * less than or equal to 15
 * Assume that no advisor's name will exceed 20 characters
 * @param advisor_name is the name of the graduate student's advisor
 * @precondition advisor_name must be a valid name
 * @return nothing
 */
void Graduate::set_advisor (string advisor_name) {
	if(check_advisor(advisor_name)) {
		advisor = advisor_name;
	}
}
		
// Accessor functions
/**
 * Function to obtain the name of the graduate student's advisor
 * Assume that all graduate students have to undertake a research project each
 * @return name of graduate student's advisor
 */
string Graduate::get_advisor ( ) {
	return advisor;
}


/**
 * Function to access the title of the graduate student's thesis
 * Assume that all graduate students have to write a thesis each
 * @return title of the graduate student's thesis
 */
string Graduate::get_thesis( ) {
	return thesis;
}


// Query Functions

/**
 * Function to determine if the title of the graduate student's thesis
 * is valid
 * Assume that all graduate students have to write a thesis each
 * Thesis title can contain any character; number of characters must be
 * less than 21 (<= 20), and no white space is allowed.
 * @param thesis_title is the title of the graduate student's thesis
 * @return true if thesis title is valid; else, return false
 */
bool Graduate::check_thesis(string thesis_title) {
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
bool Graduate::check_advisor(string advisor_name) {
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

// Other functions...

/**
 * Function to display the graduate student's data to the terminal
 */
void Graduate::display() {
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
	cout << get_advisor();
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << get_thesis() << endl;
}


/**
 * Function to write graduate student's data to an output file
 * stream that has been opened
 */
void Graduate::write_to_stream (ofstream & outputfile) {
	// Left align the data
	outputfile.setf(ios::left);
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << "Graduate";
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
	outputfile << get_advisor();
	outputfile.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	outputfile << get_thesis() << endl;
	//outputfile << endl;
}

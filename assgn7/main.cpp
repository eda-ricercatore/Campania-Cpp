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
using namespace std;
//#include "Student.h"
#include "StudentDB.h"
// ==========================================================================

// Declare and initialize global variables
//int number_correct_records=0;
//int index_of_last_element=-1;

// --------------------------------------------------------------------------

// Main function...
main() {
	cout << "STUDENT DATABASE PROGRAM" << endl;
	cout << endl;
	cout << "Keys:" << endl;
	cout << "A <== Add a student's particulars to the current datatbase" << endl;
	cout << "D <== Display a student's particulars" << endl;
	cout << "E <== Export database of students' paticulars" << endl;
	cout << "I <== Import student data from an input file" << endl;
	cout << "R <== Remove a student's particulars from the database" << endl;
	cout << "S <== Show all the particulars of students in the database" << endl;
	cout << "Q <== Exit program" << endl;
	cout << endl;
	
	// Names for input and output file streams
	string inputfilename, outputfilename;
	// Input character that will be processed as a menu option
	char input_character;
	// Boolean flag to exit the program
	bool exit_flag=false;
	// Flag to indicate that student database exist
	bool database_flag=false;
	// Flag for overwriting the input file
	bool overwrite=false;
	/**
	 * Social security number entered by the user to indicate that an operation
	 * will be performed on the database using this
	 */
	string input_ssn="";
	// Database that stores the correct student records
	StudentDB database;
	
	// Temporary variables to contain details of the student
	string fname;
	string lname;
	string ssnum;
	string phoneno;
	int age;
	Student newStudent;
	
	// User menu options and processing
	while(!exit_flag) {
		cout << "Enter command (A, D, E, I, R, S - or Q to quit) : ";
		if((cin >> input_character) != NULL) {
			input_character=toupper(input_character);
		
			switch(input_character) {
				case 'Q':
					cout << "Exiting the database program..." << endl;
					return 0;
				case 'A':
					if(!database_flag) {
						cout << "Database is empty. "
							<< "Please import data before processing it."
							<< endl;
						continue;
					}
					
					// Prompt user for input
					cout << "Enter the following details of the student that "
						<< "be added to the database" << endl;
					cout << "First name: ";
					cin >> fname;
					cout << "Last name: ";
					cin >> lname;
					cout << "Social Security Number: ";
					cin >> ssnum;
					cout << "Phone number: ";
					cin >> phoneno;
					cout << "Age: ";
					cin >> age;
					/**
					 * Check if the student particulars are valid...
					 * If any of the student particulars is invalid,
					 * ignore this current line in the input file and
					 * skip to the next
					 */
					if(!database.check_lastname(lname)) {
						cout << "\t\t Last name of the student should only contain "
							<< "alphabets" << endl;
					}else if(!database.check_firstname(fname)) {
						cout << "\t\t First name of the student should only contain "
							<< "alphabets" << endl;
					}else if(!database.check_socialsecuritynumber(ssnum)) {
						cout << "\t\t Security numbers should contain dashes at the "
							<< "4th and 7th characters, and digits otherwise" << endl;
					}else if(!database.check_phonenumber(phoneno)) {
						cout << "\t\t Phone numbers should be given in this format: "
							<< "(XXX)XXX-XXXX, where each X is a digit" << endl;
					}else if(!database.check_studentage(age)) {
						cout << "\t\t Age of the student should be between 1 and 120, "
							<< "inclusive" << endl;
					}else if(!database.check_duplicate_social_security_number(ssnum,
						(database.get_index_of_last_element()-1))) {
						cout << "\t Duplicate social security number" << endl;
					}else{
						newStudent.set_lastname(lname);
						newStudent.set_firstname(fname);
						newStudent.set_ssn(ssnum);
						newStudent.set_phone(phoneno);
						newStudent.set_age(age);
						database.add_single_student(newStudent);
					}
					break;
				case 'D':
					if(!database_flag) {
						cout << "Database is empty. "
							<< "Please import data before processing it."
							<< endl;
						continue;
					}
					// Prompt user for input
					cout << "Please enter a social security number "
						<< "to search for: ";
					cin >> input_ssn;
					if(database.check_socialsecuritynumber(input_ssn)) {
						database.print_header();
						int index = database.binary_search(
							 input_ssn, 0, database.get_index_of_last_element());
						if(index != (-1)) {
							database.display_single_student_details(index);
						}else{
							cout << "The social security number you "
							<< "have entered is not found in the database." << endl;
						}
					}else{
						cout << "The social security number you have entered "
							<< "is invalid." << endl;
					}
					break;
				case 'E':
					if(!database_flag) {
						cout << "Database is empty. "
							<< "Please import data before processing it."
							<< endl;
						continue;
					}else{
						// Prompt user for input
						while(!overwrite) {
							cout << "Please enter output filename, "
								<< "and press the return key: ";
							cin >> outputfilename;
							cout << endl;
							if(outputfilename == inputfilename) {
								do{
									cout << "Do you want to overwrite "
										<< "the input file? Y/N?";
									cin >> input_character;
									input_character=toupper(input_character);
									if(input_character == 'Y') {
										overwrite=true;
										break;
									}else if(input_character == 'N') {
										break;
									}else{
										cout << "Enter Y or N: ";
									}
								}while((cin >> input_character) !=NULL);
							}else{
								break;
							}
						}
						database.write_output(outputfilename);
					}
					break;
				case 'I':
					// Prompt user for input
					cout << "Please enter input filename, "
						<< "and press the return key: ";
					cin >> inputfilename;
					cout << '\t' << "Processing the input file: "
						<< inputfilename << endl;
					cout << endl;
					// Read the input file
    				if(!database.read_input(inputfilename)) {
						return -1;
					}
					database_flag=true;
					break;
				case 'R':
					if(!database_flag) {
						cout << "Database is empty. "
							<< "Please import data before processing it."
							<< endl;
						continue;
					}
					// Prompt user for input
					cout << "Please enter a social security number "
						<< "to search for: ";
					cin >> input_ssn;
					database.remove_selected_student(input_ssn);
					break;
				case 'S':
					if(!database_flag) {
						cout << "Database is empty. "
							<< "Please import data before processing it."
							<< endl;
						continue;
					}
					database.display_all_student_details();
					break;
				default:
					cout << "Invalid command entered. Please re-enter command..."
						<< endl;
					cout << endl;
					continue;
			}
		}else{
			return -1;
		}
		
		cout << endl;
	}
	
	// Write to output file...
	database.write_output(outputfilename);
	cout << "Output is written to the file: " << outputfilename << endl;
}

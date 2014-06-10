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
#include "Student.h"
// ==========================================================================
typedef list<Student *> Student_list;
typedef list<Student *>::iterator Student_list_pointer;
class StudentDB {
public:



	// Declare and initialize global variables
	private:
	// Number of correct records in the database
	int number_correct_records;
	// Index of the last student/element in the array
	int index_of_last_element;
	// The database is a pointer to the first Student element
	list<Student *>database;

	// --------------------------------------------------------------------------

	public:
	// Default constructor
	StudentDB();
	
	// ---------------------------------------------------------------------
	
	// Declaring function prototypes

	// Update/modifier functions	
	/**
	 * Add the student if that social security number is not a duplicate
	 * return true if added and false otherwise
	 */
	bool add_student (Student *);
	bool delete_student (string ssn);
	void set_number_correct_records(int num_correct);
	void increment_index_of_last_element();
	void decrement_index_of_last_element();
	
	// Accessor methods
	int get_number_correct_records();
	int get_index_of_last_element();
	Student_list_pointer find_student(string ssn);
	
	// Query functions...
	bool check_lastname(string lastname);
	bool check_firstname(string firstname);
	bool check_socialsecuritynumber(string ssn);
	bool check_phonenumber(string phonenumber);
	bool check_studentage(int age);
	bool check_duplicate_social_security_number(string ssn);
	bool check_thesis(string thesis_title);
	bool check_advisor(string advisor_name);
	bool check_major(string major_title);
	bool check_minor(string minor_title);
			
	// Input/Output functions...
	/**
	 * Opens filename and initializes the database to the data in that file
	 * returns true if everything works, and false otherwise
	 */
	bool import_database (string filename);
	/**
	 * Opens filename and exports the database to that file in a format
	 * that is compatible to the input file;
	 * returns true if everything works, and false otherwise
	 */
	bool export_database(string filename);
	
	// Other functions...	
	void uppercase(string & s);
	bool display_student (string ssn);
	void display_all ();
	
	void print_grad_header();
	void print_ugrad_header();
};

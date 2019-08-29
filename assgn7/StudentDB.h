/**
 * Zhiyang Ong.
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
class StudentDB {
	// Declare and initialize global variables
	private:
	// Number of correct records in the database
	int number_correct_records;
	// Index of the last student/element in the array
	int index_of_last_element;

	// --------------------------------------------------------------------------

	public:
	// Default constructor
	StudentDB();
	
	// ---------------------------------------------------------------------
	
	// Declaring function prototypes

	// Update/modifier functions
	void add_single_student(Student student_details);
	void remove_selected_student(string ssn);
	void set_number_correct_records(int num_correct);
	void increment_index_of_last_element();
	void decrement_index_of_last_element();
	
	// Accessor methods
	int get_number_correct_records();
	int get_index_of_last_element();
	
	// Query functions...
	bool check_lastname(string lastname);
	bool check_firstname(string firstname);
	bool check_socialsecuritynumber(string ssn);
	bool check_phonenumber(string phonenumber);
	bool check_studentage(int age);
	bool check_duplicate_social_security_number(string ssn, int current_index);
			
	// Input/Output functions...
	bool read_input(string inputfilename);
	void write_output(string outputfilename);
		
	// Other functions...	
	void uppercase(string & s);
	void insertion_sort();
	int binary_search(string ssn, int lowerindex, int upperindex);
	void display_single_student_details(int index);
	void display_all_student_details();
	void print_header();
};

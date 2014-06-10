/*
 * Zhiyang Ong, student number 6004-9194-12
 * Assignment 7, Introduction to Programming Systems Design
 * CSCI 455, Fall 2005
 *
 * Assume that phone numbers can be duplicated since students can be siblings,
 * relatives, or friends living in the same house, where the same line phone
 * is shared between them
 *
 * @acknowledgement - code samples/examples from the web page
 *	<http://www-scf.usc.edu/~csci455/>; they are written by Dr. K. Narayanaswamy
 * @reference: D.S. Malik, "C++ Programming: Program Design Including Data
 *      Structures", Second Edition, Thomson Technology, USA, 2004.
 */

#ifndef __STUDENT
#define __STUDENT

// ==========================================================================

class Student {
	public:
		// Constructors...
		Student();		// Student default constructor
		// Standard constructor - provide 3 parameters
		Student(string ssn, string lastname, int age);
		// Standard constructor - provide all parameters
		Student(string firstname, string lastname, string ssn,
			string phone_num, int age);
		
		// ------------------------------------------------------------------
		
		/**
		 * Modifier/accessor functions...
		 * All the modifier/update functions return true if the update is
		 * successful, and false otherwise
		 */
		bool set_ssn(string);
		bool set_lastname(string); 
		bool set_firstname(string); 
		bool set_phone(string); 
		bool set_age(int);
		void set_graduate();
		
		// ------------------------------------------------------------------
		
		// Accessor functions...
		string get_ssn();
		string get_lastname();
		string get_firstname();
		string get_phone();
		int get_age();
		bool get_graduate();
		
		// ------------------------------------------------------------------
		
		// Query functions...
		bool check_last_name(string lastname);
		bool check_first_name(string firstname);
		bool check_social_security_number(string ssn);
		bool check_phone_number(string phonenumber);
		bool check_age(int age);
		
		// ------------------------------------------------------------------
		
		// Other functions...
		// display student data to the terminal
		virtual void display();
		// write student data to an output file stream that has been opened
		virtual void write_to_stream(ofstream &);
		// Convert all letters in a string to Uppercase
		void uppercase (string & s);

	// ----------------------------------------------------------------------

	private:
		

		// Declaring variables
		/**
		 * Assume that all names of students can be written using English alphabets
		 * That is, no characters outside the English language may be used
		 */
		// Last name should only contain alphabetic characters
		string last_name;
		// First name should only contain alphabetic characters
		string first_name;
		/**
		 * Digits in all places, except characters in position 4 and 7
		 * - they should be dashes '-'
		 * US security social numbers only.
		 */
		string social_security_number;
		/**
		 * US Phone numbers only...
		 * 13 characters: '(', character 1; ')', character 5; '-', character 9;
		 * remaining characters are digits
		 */
		string phone_number;
		/**
		 * Should be non-negative (a baby can be 0 years of age)
		 * and less than 120 (nobody lives for more than 120 years)
		 */
		int student_age;
		// Boolean flag to indicate if student is a graduate student
		bool graduate;
};
#endif

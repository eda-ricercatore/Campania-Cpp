/**
 * Zhiyang Ong, student number 6004-9194-12,
 * Assignment 6, Introduction to Programming Systems Design
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

// --------------------------------------------------------------------------

// Declaration of the struct data type to represent each student's particulars
struct student {
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
	 * Integer representation of the US social security number,
	 * without the dashes
	 * It is used for to determine compare 2 strings in order to sort the
	 * collection of student records, based on their US social security number,
	 * in ascending order.
	 */
	int ssn;
	/**
	 * US Phone numbers only...
	 * 13 characters: '(', character 1; ')', character 5; '-', character 9;
	 * remaining characters are digits
	 */
	string phone_number;
	/**
	 * Should be non-negative (a baby can be 0 years of age)
	 * and less than 150 (nobody lives for more than 150 years)
	 */
	int age;
};

// --------------------------------------------------------------------------

// Declare and initialize global variables
int number_correct_records=0;
int index_of_last_element=-1;

// --------------------------------------------------------------------------

// Declaring function prototypes
bool check_last_name(string lastname);
bool check_first_name(string firstname);
bool check_social_security_number(string ssn);
bool check_phone_number(string phonenumber);
bool check_age(int age);
bool read_input(string inputfilename,
	student correct_student_records[]);
void uppercase (string & s);
void write_output(string outputfilename, student student_particulars[]);
bool check_duplicate_social_security_number(string ssn,
	student student_particulars[], int current_index);
void insertion_sort(student student_particulars[]);
int binary_search(student student_particulars[], string ssn,
	int lowerindex, int upperindex);
void display_single_student_details(int index, student student_particulars[]);
void add_single_student(student student_details, student student_particulars[]);
void remove_selected_student(string ssn, student student_particulars[]);
void print_header();


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
	student correct_student_records[MAXIMUM_NUMBER_OF_STUDENTS];
	// Initialize database values to NULL
	for(int i=0; i<MAXIMUM_NUMBER_OF_STUDENTS; i++) {
		correct_student_records[i].last_name="";
		correct_student_records[i].first_name="";
		/**
		 * Assume that no body has a social security number 999-99-9999
		 * This is used to facilitate sorting; if empty strings are used,
		 * they will appear before valid social security numbers
		 */
		correct_student_records[i].social_security_number="999-99-9999";
		correct_student_records[i].age=999999999;
		correct_student_records[i].phone_number="";
		correct_student_records[i].age=0;
	}
	
	// Temporary variables to contain details of the student
	string fname;
	string lname;
	string ssnum;
	string phoneno;
	int age;
	student newStudent;
	
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
					if(!check_last_name(lname)) {
						cout << "\t\t Last name of the student should only contain "
							<< "alphabets" << endl;
					}else if(!check_first_name(fname)) {
						cout << "\t\t First name of the student should only contain "
							<< "alphabets" << endl;
					}else if(!check_social_security_number(ssnum)) {
						cout << "\t\t Security numbers should contain dashes at the "
							<< "4th and 7th characters, and digits otherwise" << endl;
					}else if(!check_phone_number(phoneno)) {
						cout << "\t\t Phone numbers should be given in this format: "
							<< "(XXX)XXX-XXXX, where each X is a digit" << endl;
					}else if(!check_age(age)) {
						cout << "\t\t Age of the student should be between 1 and 120, "
							<< "inclusive" << endl;
					}else if(!check_duplicate_social_security_number(ssnum,
						correct_student_records, (index_of_last_element-1))) {
						cout << "\t Duplicate social security number" << endl;
					}else{
						newStudent.last_name=lname;
						newStudent.first_name=fname;
						newStudent.social_security_number=ssnum;
						newStudent.phone_number=phoneno;
						newStudent.age=age;
						add_single_student(newStudent, correct_student_records);
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
					if(check_social_security_number(input_ssn)) {
						print_header();
						int index = binary_search(correct_student_records,
							 input_ssn, 0, index_of_last_element);
						if(index != (-1)) {
//cout << "index is: " << index << endl;
							display_single_student_details(index,
								correct_student_records);
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
						write_output(outputfilename, correct_student_records);
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
    				if(!read_input(inputfilename, correct_student_records)) {
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
					remove_selected_student(input_ssn, correct_student_records);
					break;
				case 'S':
					if(!database_flag) {
						cout << "Database is empty. "
							<< "Please import data before processing it."
							<< endl;
						continue;
					}
					print_header();
					for(int i=0; i<(index_of_last_element+1);i++) {
						display_single_student_details(i, correct_student_records);
					}
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
	write_output(outputfilename, correct_student_records);
	cout << "Output is written to the file: " << outputfilename << endl;
}

// --------------------------------------------------------------------------

/**
 * Fuunction to read input from a file and process it
 * #Read the particulars of each student in a line with the following format:
 *	Last_name	First_name	Social_Security_Number	Telephone	Age
 * Assume that the input file will contain data in this format
 * @param inputfilename is the name of the input file
 * @param student correct_student_records contains a table of correct
 *	students' particulars
 */
bool read_input(string inputfilename,
	student correct_student_records[]) {
	
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
	 * Current index of the record of student paticulars
	 * that is being enumerated
	 */
	int i=0;
	// Start processing the data in the table
	while((inputfile != NULL) && (i<MAXIMUM_NUMBER_OF_STUDENTS)) {
		// Stop processing the input file once its end has been reached
		if ( (inputfile >> lastname	>> firstname >> socialsecuritynumber
			>> phonenumber >> studentage) == NULL) {
			break;
		}

		i++;
		
		/**
		 * Check if the student particulars are valid...
		 * If any of the student particulars is invalid,
		 * ignore this current line in the input file and
		 * skip to the next
		 */
		if(!check_last_name(lastname)) {
			cout << "\t Ignoring Record Number " << i <<
				" - bad last name" << endl;
			cout << "\t\t Last name of the student should only contain "
				<< "alphabets" << endl;
			errors++;
			continue;
		}else if(!check_first_name(firstname)) {
			cout << "\t Ignoring Record Number " << i <<
				" - bad first name" << endl;
			cout << "\t\t First name of the student should only contain "
				<< "alphabets" << endl;
			errors++;
			continue;
		}else if(!check_social_security_number(socialsecuritynumber)) {
			cout << "\t Ignoring Record Number " << i <<
				" - bad social security number" << endl;
			cout << "\t\t Security numbers should contain dashes at the "
				<< "4th and 7th characters, and digits otherwise" << endl;
			errors++;
			continue;
		}else if(!check_phone_number(phonenumber)) {
			cout << "\t Ignoring Record Number " << i 
				<< " - bad phone number" << endl;
			cout << "\t\t Phone numbers should be given in this format: "
				<< "(XXX)XXX-XXXX, where each X is a digit" << endl;
			errors++;
			continue;
		}else if(!check_age(studentage)) {
			cout << "\t Ignoring Record Number " << i << " - bad age" << endl;
			cout << "\t\t Age of the student should be between 1 and 120, "
				<< "inclusive" << endl;
			errors++;
			continue;
		}else if(!check_duplicate_social_security_number(socialsecuritynumber,
			correct_student_records, (i-1))) {
			cout << "\t Ignoring Record Number " << i
				<< " - duplicate social security number" << endl;
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
		student tempStudent;
		tempStudent.last_name = lastname;
		tempStudent.first_name = firstname;
		tempStudent.social_security_number = socialsecuritynumber;
		tempStudent.phone_number = phonenumber;
		tempStudent.age = studentage;
		//cout << "tempStudent name: " << firstname << " " << lastname << endl;
		/**
		 * Convert the social security number to an integer
		 * for sorting purposes
		 * Make a temporary copy of the social security number so that it
		 * is not modified
		 */
		temp_ssn=socialsecuritynumber;
		// Remove the delimiters (dashes) in the social security number
		temp_ssn.erase(INDEX_FIRST_DELIMITER,NUMBER_OF_DELIMITER_CHARACTERS);
		temp_ssn.erase(INDEX_SECOND_DELIMITER,NUMBER_OF_DELIMITER_CHARACTERS);
		/**
		 * Assign the integer value of the social security number to the
		 * student's particulars
		 */
		tempStudent.ssn=atoi(temp_ssn.c_str());
//cout << "ssn is: " << tempStudent.ssn << endl;
//cout << "ssn is: " << temp_ssn << endl;
//cout << "age is: " << tempStudent.age << endl;
		add_single_student(tempStudent, correct_student_records);
		
		//display_single_student_details(correct_index, correct_student_records);
	}
	
	cout << endl;
	cout << "Processed " << i << " student records" << endl;
	cout << errors << " errors were found" << endl;
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
 * @param student student_particulars contains a table of students' particulars
 */
void write_output(string outputfilename, student student_particulars[]) {
	
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
	}
	
	
	// Left align the data
	outputfile.setf(ios::left);
	// Print the student records
	for(int i=0; i<number_correct_records; i++) {
		outputfile.width(16);
		outputfile << student_particulars[i].last_name;
		outputfile.width(16);
		outputfile << student_particulars[i].first_name;
		outputfile.width(16);
		outputfile << student_particulars[i].social_security_number;
		outputfile.width(16);
		outputfile << student_particulars[i].phone_number;
		outputfile.width(16);
		outputfile << student_particulars[i].age;
		outputfile << endl;
	}
	outputfile << endl;
	
	// Close the output filestream
	outputfile.close();
}


/**
 * Function to convert all letters in the string s to uppercase
 * @param s is the string to be converted to uppercase
 */
void uppercase (string & s) {
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
bool check_last_name(string lastname) {
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
bool check_first_name(string firstname) {
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
bool check_social_security_number(string ssn) {
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
bool check_phone_number(string phonenumber) {
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
bool check_age(int age) {
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
bool check_duplicate_social_security_number(string ssn,
	student student_particulars[], int current_index) {
	for(int i=0; i<MAXIMUM_NUMBER_OF_STUDENTS; i++) {
		if(i==current_index) {
			continue;
		}else if(student_particulars[i].social_security_number == ssn) {
			return false;
		}
	}
	return true;
}


/**
 * Function to sort the student database according to the students'
 * social security numbers - Insertion sort
 * @param student_particulars is the collection of students' particulars
 */
void insertion_sort(student student_particulars[]) {
	// Index of the first element that is not in sorting order
	int firstOutOfOrder=0;
	// Index of the linear collection/array to insert the student's particulars
	int location=0;
	// The student's particulars...
	student current_student;
	
	for(firstOutOfOrder=1; firstOutOfOrder<MAXIMUM_NUMBER_OF_STUDENTS;
		firstOutOfOrder++) {
		
		if(strcmp(student_particulars[firstOutOfOrder].social_security_number.c_str(),
			student_particulars[firstOutOfOrder-1].social_security_number.c_str()) < 0) {
/*
			cout << student_particulars[firstOutOfOrder].social_security_number <<"  %%  "
				<< student_particulars[firstOutOfOrder-1].social_security_number
				<< "+++" << firstOutOfOrder << endl;
*/	
			current_student=student_particulars[firstOutOfOrder];
			location=firstOutOfOrder;
			do {
/*
cout << student_particulars[firstOutOfOrder].social_security_number <<"  &&  "
	<< student_particulars[firstOutOfOrder-1].social_security_number << endl;
*/
				student_particulars[location]=student_particulars[location-1];
				location--;
			}while((location>0) &&
				(strcmp(student_particulars[location-1].social_security_number.c_str(),
			current_student.social_security_number.c_str()) > 0));
			
			student_particulars[location]=current_student;
		}
	}
}


/**
 * Function to search for a particular social security number in the
 * student database - use binary search with recursion implementation
 * @param student_particulars is the collection of students' particulars
 * @param lowerindex is the lower limt where the search will "start" from
 * @param upperindex is the upper limt where the search will "end"
 * @param ssn is the social security number that is used as a search key
 * @return -1 if no student has a social security number with ssn;
 *	else, return the index of the student in the array with that social
 *	security number
 */
int binary_search(student student_particulars[], string ssn,
	int lowerindex, int upperindex) {
	if(!check_social_security_number(ssn)) {
		cout << "Social security number entered is invalid" << endl;
		return -1;
	}
	
	// Temporary store the social security number
	string temp_ssn=ssn;
	// Remove the delimiters (dashes) in the social security number
	temp_ssn.erase(INDEX_FIRST_DELIMITER,NUMBER_OF_DELIMITER_CHARACTERS);
	temp_ssn.erase(INDEX_SECOND_DELIMITER,NUMBER_OF_DELIMITER_CHARACTERS);
	/**
	 * Assign the integer value of the social security number to be
	 * an integer search key
	 */
	int ssn_key=atoi(temp_ssn.c_str());

	// Have the indices cross each other?
	if(lowerindex > upperindex) {
		// Yes, no student has this social security number
		return -1;
	// Are the indices equal?
	}else if(lowerindex == upperindex) {
		/**
		 * Yes. Does currently enumerated student have ssn as the social
		 * sequrity number?
		 */
		if(student_particulars[lowerindex].social_security_number==ssn) {
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
			student_particulars[midpoint].social_security_number.c_str())>0) {
			// Yes, keep on searching recursively
			return binary_search(student_particulars, ssn, midpoint + 1, upperindex);
		// Is the search key less than current value?
		}else if(strcmp(ssn.c_str(),
			student_particulars[midpoint].social_security_number.c_str())<0) {
			// Yes, keep on searching recursively
			return binary_search(student_particulars, ssn, lowerindex, midpoint - 1);
		}else{
			// No, current student has this social security number.
			return midpoint;
		}
	}
}


/**
 * Function to display the particulars of a students
 * @param index is the index of the student, whose details are to be displayed
 */
void display_single_student_details(int index, student student_particulars[]) {
	cout.setf(ios::left);
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << student_particulars[index].last_name;
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << student_particulars[index].first_name;
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << student_particulars[index].social_security_number;
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << student_particulars[index].phone_number;
	cout.width(MAXIMUM_NUMBER_OF_CHARACTERS);
	cout << student_particulars[index].age << endl;
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
void add_single_student(student student_details, student student_particulars[]) {
	// Value of the binary search results
	int result = binary_search(student_particulars, student_details.social_security_number,
		0,(MAXIMUM_NUMBER_OF_STUDENTS-1));
	/**
	 * If a student with the same social security number as this person's
	 * exist in the database, don't add this student's details
	 */
	if(result != (-1)) {
		// Don't add this student's details...
		cout << "A student with the social security number, "
			<< student_particulars[result].social_security_number
			<< ", already exists in the database" << endl;
	}else{
		// Is the database full?
		if(index_of_last_element >= (MAXIMUM_NUMBER_OF_STUDENTS-1)) {
			// Yes, don't add this student to the database
			cout << "The database is full. "
				<< "No more students can be added to it" << endl;
		}else{
			// No, add this student to the database
			student_particulars[index_of_last_element+1].last_name
				=student_details.last_name;
			student_particulars[index_of_last_element+1].first_name
				=student_details.first_name;
			student_particulars[index_of_last_element+1].social_security_number
				=student_details.social_security_number;
			student_particulars[index_of_last_element+1].ssn
				=student_details.ssn;
			student_particulars[index_of_last_element+1].phone_number
				=student_details.phone_number;
//cout << "Print1: " << student_particulars[index_of_last_element+1].phone_number << endl;
//cout << "Print2: " << student_details.phone_number << endl;
//cout << "Print3: " << student_particulars[index_of_last_element+1].ssn << endl;
			student_particulars[index_of_last_element+1].age
				=student_details.age;
//cout << "age1 " << student_particulars[index_of_last_element+1].age << endl;
//cout << "age1 " << student_details.age << endl;
			index_of_last_element++;
/*
for(int i=0; i<(index_of_last_element+1);i++) {
						display_single_student_details(i, student_particulars);
					}
*/
//cout << "sorting" << endl;
			insertion_sort(student_particulars);
//cout << "Printing: ";
//display_single_student_details(index_of_last_element, student_particulars);
		}
	}
}


/**
 * Function to delete a student's details from the database
 * @param student_details contain the student's social security number
 * @param student student_particulars contain the database
 * If this student's social security number is not found in the database,
 * then this student's details cannot be removed from the database
 * Else, this student's record is removed from the database.
 */
void remove_selected_student(string ssn, student student_particulars[]) {
	if(!check_social_security_number(ssn)) {
		cout << "Social security number entered is invalid" << endl;
	}else{
		// Value of the binary search results
		int result = binary_search(student_particulars, ssn,
			0,(MAXIMUM_NUMBER_OF_STUDENTS-1));
		/**
		 * If a student with the same social security number as this person's
		 * exist in the database, remove this student's details
		 */
		if(result != (-1)) {
			// remove this student's details...
			for(int i=result; i<(MAXIMUM_NUMBER_OF_STUDENTS-1);i++) {
				student_particulars[i]=student_particulars[i+1];
			}
			index_of_last_element--;
			cout << "Student with the social security number, "
				<< ssn << ", is removed from the database." << endl;
		}else{
			// Don't remove this student's details...
			cout << "No student in the database has the social security number, "
				<< ssn << "." << endl;
		}
	}
}


/**
 * Function to print the header of the terminal session
 */
void print_header() {
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

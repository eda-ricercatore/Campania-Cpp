/**
 * Zhiyang Ong
 *
 * @acknowledgement - code samples/examples from the web page
 *	<http://www-scf.usc.edu/~csci455/>; they are written by
 *	Dr. K. Narayanaswamy
 */

// Including header files
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>
#include <cfloat>
#include <ctype.h>
using namespace std;

// Declaring constants...
// Maximum number of students that can be placed in the table
const int MAXIMUM_NUMBER_OF_STUDENTS=50;


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


// Declare and initialize global variables
int number_correct_records=0;
// Store the correct student records
student correct_student_records[MAXIMUM_NUMBER_OF_STUDENTS];
// Initialize table values to NULL
for(int i=0; i<MAXIMUM_NUMBER_OF_STUDENTS; i++) {
	correct_student_records[i].last_name="";
	correct_student_records[i].first_name="";
	correct_student_records[i].social_security_number="";
	correct_student_records[i].phone_number="";
	correct_student_records[i].age=0;
}


// Declaring function prototypes
bool check_last_name(string lastname);
bool check_first_name(string firstname);
bool check_social_security_number(string ssn);
bool check_phone_number(string phonenumber);
bool check_age(int age);
bool read_input(string inputfilename,
	student student_particulars[MAXIMUM_NUMBER_OF_STUDENTS]);
void uppercase (string & s);
void write_output(string outputfilename, student student_particulars[]);


// Main function...
main() {
	cout << "STUDENT DATABASE PROGRAM" << endl;
	
	// Names for input and output file streams
	string inputfilename, outputfilename;
	
	// Prompt user for input
	cout << "Please enter input filename, and press the return key" << endl;
	cin >> inputfilename;
	cout << endl;
	cout << "Please enter output filename, and press the return key" << endl;
	cin >> outputfilename;
	cout << endl;
	
		
	cout << '\t' << "Processing the input file: " << inputfilename << endl;
	cout << endl;
	
	// Process the input file...
	// Store the particulars of students in the table
	student student_particulars[MAXIMUM_NUMBER_OF_STUDENTS];
	// Initialize table values to NULL
	for(int i=0; i<MAXIMUM_NUMBER_OF_STUDENTS; i++) {
		student_particulars[i].last_name="";
		student_particulars[i].first_name="";
		student_particulars[i].social_security_number="";
		student_particulars[i].phone_number="";
		student_particulars[i].age=0;
	}
	
	// Read the input file
    if(!read_input(inputfilename, student_particulars)) {
		return -1;
	}
	
	
	// Processing of input file is completed...
	cout << endl;
	cout << '\t' << "All input is processed" << endl;

	// Write to output file...
	write_output(outputfilename, correct_student_records);
	cout << "Output is written to the file: " << outputfilename << endl;
}


/**
 * Fuunction to read input from a file and process it
 * #Read the particulars of each student in a line with the following format:
 *	Last_name	First_name	Social_Security_Number	Telephone	Age
 * Assume that the input file will contain data in this format
 * @param inputfilename is the name of the input file
 * @param student student_particulars contains a table of students' particulars
 */
bool read_input(string inputfilename,
	student student_particulars[MAXIMUM_NUMBER_OF_STUDENTS]) {
	
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
			cout << "\t\t Security numbers should contain dashes at the"
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
		}
		
		/**
		 * Student's first and last names, social security number, phone
		 * number, and age are valid...
		 * Enter these details into the appropriate place in the records
		 */
		correct_index=i-errors;
		correct_student_records[correct_index].last_name = lastname;
		correct_student_records[correct_index].first_name = firstname;
		correct_student_records[correct_index].social_security_number
			= socialsecuritynumber;
		correct_student_records[correct_index].phone_number = phonenumber;
		correct_student_records[correct_index].age = studentage;
		
		i++;
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
		}else if(!isdigit(phonenumber[i])) {
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

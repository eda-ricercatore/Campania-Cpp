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
using namespace std;

main() {

	// Names for input and output file streams
	string inputfilename, outputfilename;
	
	// Prompt user for input
	cout << "Please enter input filename, and press the return key" << endl;
	cin >> inputfilename;
	cout << endl;
	cout << "Please enter output filename, and press the return key" << endl;
	cin >> outputfilename;
	cout << endl;
	
	// Create input file stream
	ifstream inputfile;
	// Open the input file
	inputfile.open(inputfilename.c_str());
	// Assertion to check if the input file exist
	if(inputfile == NULL) {
		cout << "Input file, with the filename " << inputfilename
		<< ", does not exist!" << endl;
		return 1;
	}
	
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
		return 1;
	}
	
	cout << '\t' << "Processing the input file: " << inputfilename << endl;
	cout << endl;
	
	// Process the input file...
	// Size of the class - number of students
	const int size = 10;
	// Number of assignments/tests that each student should have taken
	const int numAssignOffered = 5;
	// string array to contain the names of 10 students in the class
	string names[size];
	// Array to contain the total/average scores of each student
	double scores[size] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	// Array to contain the number of assignments of each student
	int numAssignTakened[size] = {0,0,0,0,0,0,0,0,0,0};
	// Counter to indicate the number of the current assignment
	int currentAssign = 0;
	// Current score being processed
	double currentScore=0;
	// Index of current student traversed
	int currentStudentIndex = 0;
	
	
	// Process each token read from the input file stream
	
	// Read the names of the students...
	for(int i=0; i<size; i++) {
		/**
		 * Assertion to check that the correct number of names in the
		 * class are read
		 */
		if((inputfile >> names[i]) == NULL) {
		//}else{
			cout << "Error with Input file format" << endl;
			cout << "Input file should begin with, and"
				<< " contain at least 10 names" << endl;
		}
		//cout << "Current name is: " << names[i] << endl;
	}
	
	// For every student, read the scores for each assignment
	for(int j=0; j<(numAssignOffered*size); j++) {
		/**
		 * Assertion to check that the correct number of scores 
		 * for students in the class are read
		 */
		if((inputfile >> currentScore) != NULL) {
			/**
			 * Since there are 50 entries of assignments, each assignment
			 * number should be incremented by one when divided by the class size.
			 * This is because arrays stat from zero, and end at 50
			 * that is (numAssignOffered*size).
			 */
			currentAssign = 1 + j/(size);
			currentStudentIndex = j%size;
cout << "cur Score " << currentScore << "curass" << currentAssign << endl;
cout << "val j " << j << endl;
			if(currentScore > 100) {
				cout << "Assignment " << currentAssign << ": Student "
					<< names[currentStudentIndex]
					<< "'s score of " << currentScore 
					<< " is not within range" << endl;
				cout << "Assignment/test scores should not exceed 100 marks" << endl;
			}else if(currentScore < 0) {
				cout << "Assignment " << currentAssign << ": Student "
					<< names[currentStudentIndex]
					<< "'s score of " << currentScore 
					<< " is not within range" << endl;
				cout << "Assignment/test scores should not be negative" << endl;
			}else{
				scores[currentStudentIndex]= currentScore + scores[currentStudentIndex];
				int temp = numAssignTakened[currentStudentIndex];
				numAssignTakened[currentStudentIndex]=temp+1;
//				numAssignTakened[currentStudentIndex] =
//					numAssignTakened[currentStudentIndex] + 1;
cout << "\t cur Score " << scores[currentStudentIndex] << "DD"
	<< currentStudentIndex << endl;
cout << "num taken " << numAssignTakened[currentStudentIndex] << endl;
			}
		}else{
			cout << "Error with Input file format" << endl;
			cout << "Input file should contain " << numAssignOffered
				<< " assignment scores for each of the " << size
				<< "students" << endl;
		}
	}

	// For each student, calculate the student's average score
	for(int k=0; k<size; k++) {
		scores[k] = scores[k] / (double)numAssignTakened[k];
		
	}
	
	/**
	 * Write the names of the names and average scores of students
	 * to the output file
	 */
	for(int m=0; m<size; m++) {
		outputfile << names[m] << "\t";
	}
	outputfile << endl;
	outputfile << fixed << showpoint;
	outputfile << setprecision(2);
	for(int n=0; n<size; n++) {
		outputfile << scores[n] << "\t";
	}
	outputfile << endl;
	
	// Processing of input file is completed...
	cout << endl;
	cout << '\t' << "All input is processed" << endl;
	
	outputfile.close();
	inputfile.close();
}

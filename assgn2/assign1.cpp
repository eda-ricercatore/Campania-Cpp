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
	// Total number of input numbers in the input file
	int totalNumber=0;
	// Total number of valid input numbers in the input file
	double totalValid=0.0;
	// Number of errors in the input file
	int numberErrors=0;
	// Average of the valid input numbers in the input file
	double average=0.0;
	// The "ith" token that is read from the input file
	int i=0;
	
	/**
	 * Assume that the only tokens read from the input file are integers.
	 * That is, no floating point numbers, letters or special characters
	 * exist in the file.
	 * The integers can be positive, negative, or zero.
	 * Whitespace is used as delimiters for the file processing.
	 * At least one whitespace is used to separate tokens.
	 */
	
	// Process each token read from the input file stream
	while((inputfile >> i) != NULL) {
		// An additional token has been read
		totalNumber = totalNumber +1;
		// Fibonacci number that will result in overflow
		int overflow=48;
		if((i > 0) && (i<overflow)) {
			// Increment the sum of the valid input numbers
			average = average + i;
			// Increment the number of valid input numbers
			totalValid = totalValid + 1.0;
			
			// Print the first "i" Fibonacci numbers in the output file
			outputfile << "Number read: " << i << endl;
			// Fibonacci number for the number "k"
			long fibonacci = 0;
			// The number preceding "k"
			long prevNumber1 = 0;
			// The number preceding "k"'s previous number
			long prevNumber2 = 0;
			for(int j=0;j<i;j++) {
				if(j==1) {
					prevNumber1 = 1;
					fibonacci = prevNumber1 + prevNumber2;
				}else{
					fibonacci = prevNumber1 + prevNumber2;
					prevNumber2 = prevNumber1;
					prevNumber1 = fibonacci;
				}
				outputfile << fibonacci << " ";
			}
			outputfile << endl;
			outputfile << "----------------------------------------" << endl;
		}else if(i>=overflow) {
			/**
			 * The token read will result in a Fibonacci number that will
			 * overflow the range of values in the data type long
			 */
			numberErrors = numberErrors + 1;
			cout << '\t' << '\t'
				<< "Skipping input number "<< i << " because of data overflow"
				<< endl;
			cout << endl;
		}else{
			// A negative token or number zero has been read
			numberErrors = numberErrors + 1;
			cout << '\t' << '\t'
				<< "Skipping input number "<< i << " because no Fibonacci"
				<< " number is possible" << endl;
			cout << endl;
		}
	}
	// Average of the valid input numbers
	if(totalValid > 0) {
		average = average / totalValid;
	}
	
	// Processing of input file is completed...
	cout << endl;
	cout << '\t' << "All input is processed" << endl;
	// Print out the statistics of the processed input file
	cout << endl;
	cout << '\t' <<'\t' << "Total number of input numbers in the input file: "
		<< totalNumber << endl;
	cout << endl;
	cout << '\t' <<'\t' << "Number of errors in input: "
		<< numberErrors << endl;
	cout << endl;
	cout << '\t' <<'\t'
		<< "Average of the valid input numbers in the input file: "
		<< average << endl;
	cout << endl;
	cout << '\t' << "Output file \"" << outputfilename 
		<< "\" has been sucessfully written..." << endl;
	
	outputfile.close();
	inputfile.close();
}

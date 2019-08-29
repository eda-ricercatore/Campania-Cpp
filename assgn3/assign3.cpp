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
using namespace std;

// Declaring funuction prototypes
double fibonacci(int i);
double factorial (int i);
bool is_fibonacci(int i);
void mystery(int a, int b, double & c, double & d);

/**
 * Declare a constant that has a Fibonacci number greater than 100
 */
const int FIBONACCI_GREATER_THAN_100=13;
// Maximum number that can appear in the input
const int MAX_NUMBER=100;

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
	// The "nth" token that is read from the input file
	int n=0;
	// First integer/token of the pair of numbers/tokens
	int a=0;
	// Second integer/token of the pair of numbers/tokens
	int b=0;
	// Results of input processing...
	double c=0;
	double d=0;
	// Holders for results less than maximum number of int data type
	int tempC=0;
	int tempD=0;
	
	/**
	 * Assume that the only tokens read from the input file are integers.
	 * That is, no floating point numbers, letters or special characters
	 * exist in the file.
	 * The integers can be positive, negative, or zero.
	 * Whitespace is used as delimiters for the file processing.
	 * At least one whitespace is used to separate tokens.
	 */
	
	// Process each token read from the input file stream
	while((inputfile >> n) != NULL) {
		// Obtain the first number of the pair
		a=n;
		// Get the second number, if there is any token left
		if((inputfile >> b) == NULL) {
			cout << "Oops, the numbers should come in pairs!" << endl;
			break;
		}
		if((a > 0) && (a <= MAX_NUMBER) && (b > 0) && (b <= MAX_NUMBER)) {
			mystery(a,b,c,d);
			if(c < (double)INT_MAX) {
				tempC = (int)c;
			}
			if(d < (double)INT_MAX) {
				tempD = (int)d;
			}
			if ((tempC == 0) && (tempD > 0)) {
				outputfile << "When mystery is applied to "
					<< a << " and " << b << ": results are "
					<< c << ", " << tempD << endl;
			}else if ((tempD == 0) && (tempC > 0)) {
				outputfile << "When mystery is applied to "
					<< a << " and " << b << ": results are "
					<< tempC << ", " << d << endl;
			}else if ((tempC > 0) && (tempD > 0)) {
				outputfile << "When mystery is applied to "
					<< a << " and " << b << ": results are "
					<< tempC << ", " << tempD << endl;
			}else{
				outputfile << "When mystery is applied to "
					<< a << " and " << b << ": results are " 
					<< c << ", " << d << endl;
			}
			tempC=0;
			tempD=0;
		}else if(a > MAX_NUMBER) {
			cout << "Skipping row that has "<< a << " as input, "
				<< "maximum is "<< MAX_NUMBER << endl;
			cout << endl;
		}else if(b > MAX_NUMBER) {
			cout << "Skipping row that has "<< b << " as input, "
				<< "maximum is "<< MAX_NUMBER << endl;
			cout << endl;
		}else if (a <= 0) {
			cout << "Skipping row that has "<< a << " as input, "
				<< "which is illegal" << endl;
			cout << endl;
		}else{
			cout << "Skipping row that has "<< b << " as input, "
				<< "which is illegal" << endl;
			cout << endl;
		}
	}
	
	// Processing of input file is completed...
	cout << endl;
	cout << '\t' << "All input is processed" << endl;

	
	outputfile.close();
	inputfile.close();
}


/**
 * Function to calculate the factorial of i
 * @returns the factorial of i,
 *  returns 0 if i<=0, or -1 if i>100
 *  since input numbers should be less than 100
 *
 * NOTE: 0! = 0 is a assignment specification
 * 0! should be 1 since 0 elements has 1 permutation
 * See references: D Wells, "The Penguin Dictionary of
 * Curious and Interesting Numbers", Penguin Books,
 * Middlesex, England, pp. 31, 1986.
 * AND <http://mathworld.wolfram.com/Zero.html>
 */
double factorial (int i) {
    if(i <= 0) {
        return 0.0;
        // Note again, 0! should be 1
        // 0! = 0 is an assignment specification
    }else if(i>100) {
        cout << "ERROR: Token is greater than 100!" << endl;
        return -1.0;
    }else if(i==1) {
        return 1.0;
    }else{
        // Recursive algorithm
        return i*factorial(i-1);
    }
}


/**
 * Function to determine if this number is a Fibonacci number.
 * @returns a boolean true if it is; else, false is returned.
 */
bool is_fibonacci(int i) {
	/**
	 * Checking if i matches a Fibonacci number ranging
	 * from 0 to FIBONACCI_GREATER_THAN_100.
	 * Since no integer in the input file should be greater
	 * than 100, and the Fibonacci of numbers above 13 exceeds
	 * 100, 13 is used to compare the Fibonacci numbers to the
	 * input tokens.
	 */
	for(int j=0; j<FIBONACCI_GREATER_THAN_100; j++) {
		if(fibonacci(j)==i) {
			// A match is found
			return true;
		}
	}
	return false;
}


/**
 * Function to determine if a and b are Fibonacci numbers and
 * determine the output appropriately, as a result of this comparison
 */
void mystery(int a, int b, double &c, double & d) {
	// If a and b are Fibonacci numbers...
	if(is_fibonacci(a) && is_fibonacci(b)) {
		c=a+b;
		d=factorial((int)c);
	}else{
	// Else, do otherwise...
		d=a+b;
		c=factorial((int)d);
	}
}


/**
 * Function to calculate the ith Fibonacci of the number i
 * @returns the ith Fibonacci of the number i if 0 <i<48
 *  else, -1 is returned if i<=0, or INT_MAX is returned if
 *  i>=48 since an overflow will result
 */
double fibonacci(int i) {
	// Fibonacci number that will result in overflow
	if((i > 0)) {
		// Fibonacci number for the number "k"
		double fibonacci = 0;
		// The number preceding "k"
		double prevNumber1 = 0;
		// The number preceding "k"'s previous number
		double prevNumber2 = 0;
		for(int j=0;j<i;j++) {
			if(j==1) {
				prevNumber1 = 1;
				fibonacci = prevNumber1 + prevNumber2;
			}else{
				fibonacci = prevNumber1 + prevNumber2;
				prevNumber2 = prevNumber1;
				prevNumber1 = fibonacci;
			}
		}
		return fibonacci;
	}else{
		// A negative token or number zero has been read
		/*
		cout << endl << '\t'
			<< "The input number "<< i << " is negative or zero" << endl;
        cout << '\t'
			<< "Fibonacci numbers do not exist for negative numbers or zero"
			<< endl;
		cout << endl;
		*/
		return -1.0;
	}
}

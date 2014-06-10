/**
 * Zhiyang Ong, student number 6004-9194-12,
 * Assignment 4, Introduction to Programming Systems Design
 * CSCI 455, Fall 2005
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
// Number of candidates running for the election
const int NUMBER_OF_CANDIDATES=5;
// Number of cities involved in the election
const int NUMBER_OF_CITIES=10;

// Declaring function prototypes
void read_input(string inputfilename, string cities[],
	string candidate_names[],
	int number_of_votes_per_city_per_candidate[NUMBER_OF_CANDIDATES][NUMBER_OF_CITIES]);
int candidate_index(string name, string candidate[]);
int city_index(string name, string cities[]);
void uppercase (string & s);
void write_output(string outputfilename, string cities[],
	string candidate_names[],
	int number_of_votes_per_city_per_candidate[NUMBER_OF_CANDIDATES][NUMBER_OF_CITIES]);

// Main function...
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
	
		
	cout << '\t' << "Processing the input file: " << inputfilename << endl;
	cout << endl;
	
	// Process the input file...
	// Store the names of the cities involved in the election
	string cities[NUMBER_OF_CITIES];
	// Store the names of candidates running for the elections
	string candidate_names[NUMBER_OF_CANDIDATES];
	// Store the number of votes per candidate per city
	int number_of_votes_per_city_per_candidate
		[NUMBER_OF_CANDIDATES][NUMBER_OF_CITIES];
	// Initialize table values to zero
	for(int i=0; i<NUMBER_OF_CANDIDATES; i++) {
		for(int j=0; j<NUMBER_OF_CITIES; j++) {
			number_of_votes_per_city_per_candidate[i][j]=0;
		}
	}
	// Read the input file
    read_input(inputfilename, cities, candidate_names,
	   number_of_votes_per_city_per_candidate);
	
	
	// Processing of input file is completed...
	cout << endl;
	cout << '\t' << "All input is processed" << endl;

	// Write to output file...
	write_output(outputfilename, cities, candidate_names, number_of_votes_per_city_per_candidate);
}


/**
 * Fuunction to read input from a file and process it
 * @param ifs is the input file stream used to read data
 *	from a file
 * @param cities is the list of cities where people
 *	polls are held
 * @param candidate_names is the list of the candidates'
 *	names
 * @param number_of_votes_per_city_per_candidate is the
 *	amount of votes tallied for each candidate in each
 *	city
 * @returns nothing; however, the number of votes per
 *	candidate per city, and the candidate's total number
 *	of votes are counted.
 */
void read_input(string inputfilename, string cities[],
	string candidate_names[],
	int number_of_votes_per_city_per_candidate
		[NUMBER_OF_CANDIDATES][NUMBER_OF_CITIES]) {
	
	// Create input file stream
	ifstream inputfile;
	// Open the input file
	inputfile.open(inputfilename.c_str());
	// Assertion to check if the input file exist
	if(inputfile == NULL) {
		cout << "Input file, with the filename " << inputfilename
		<< ", does not exist!" << endl;
	}
	
	// Read the list of cities involved in the election...
	for(int i=0; i<NUMBER_OF_CITIES; i++) {
		/**
		 * Assertion to check that the correct number of
		 * cities, where elections are held, are read
		 */
		if((inputfile >> cities[i]) == NULL) {
			cout << "Error with Input file format" << endl;
			cout << "Input file should begin with, and"
				<< " contain names of 10 cities" << endl;
		}
		//cout << "city: " << cities[i] << endl;
	}
	
	// Read the list of candidate names in the election...
	for(int i=0; i<NUMBER_OF_CANDIDATES; i++) {
		/**
		 * Assertion to check that the correct number of
		 * candidate names are read
		 */
		if((inputfile >> candidate_names[i]) == NULL) {
			cout << "Error with Input file format" << endl;
			cout << "Input file should begin with, and"
				<< " contain names of 5 candidates" << endl;
		}
		//cout << "names: " << candidate_names[i] << endl;
	}
	
	// Name of possible candidate
	string temp_name="";
	// Index of the candidate's name in the list
	int name_index=0;
	// Name of possible city involved in the elections
	string temp_city="";
	// Index of the city's name in the list
	int cityIndex=0;
	// Possible votes tally for this candidate in this city
	int votes_tally=0;
	// Start counting the votes per candidate per city
	while(inputfile != NULL) {
		/**
		 * Stop processing the input file once its end
		 * has been reached
		 */
		if ( (inputfile >> temp_name >> temp_city
			>> votes_tally) == NULL) {
			break;
		}
		
		// Check if names and cities of poll are valid
		name_index=candidate_index(temp_name, cities);
		cityIndex=city_index(temp_city, candidate_names);
		
		/**
		 * If either name, city, or vote tally is invalid,
		 * ignore this current line in the input file and
		 * skip to the next
		 */
		if(name_index<0) {
			cout << temp_name << " " << temp_city << " " << votes_tally
				<< "\t\t NOT PROCESSED - Candidate not recognized" << endl;
			continue;
		}else if(cityIndex<0) {
			cout << temp_name << " " << temp_city << " " << votes_tally
				<< "\t\t NOT PROCESSED - City not recognized" << endl;
			continue;
		}else if(votes_tally<0) {
			cout << temp_name << " " << temp_city << " " << votes_tally
				<< "\t NOT PROCESSED - Vote total is illegal" << endl;
			continue;
		}
		
		// Name, city, and vote tally are valid... 
		// enter vote tally into the appropriate table entry
		number_of_votes_per_city_per_candidate[name_index][cityIndex]=
			number_of_votes_per_city_per_candidate[name_index][cityIndex]
			+ votes_tally;
	}
	
	// Close the input filestream
	inputfile.close();
}


/**
 * Function to write output to a file
 * #Print the vote tally per candidate per city
 * #Determine the total vote of a candidate
 * #Determine the winner of the elections
 * @param outputfilename is the name of teh output file
 * @param number_of_votes_per_city_per_candidate contains the vote tally
 *	per candidate per city
 */
void write_output(string outputfilename, string cities[],
	string candidate_names[],
	int number_of_votes_per_city_per_candidate[NUMBER_OF_CANDIDATES][NUMBER_OF_CITIES]) {
	
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
	
	// Determine the total votes for all candidates across all cities...
	int total_tally[NUMBER_OF_CANDIDATES];
	for(int m=0; m<NUMBER_OF_CANDIDATES; m++) {
		total_tally[m]=0;
	}
	
	// Determine the index of the winning candidate...
	// Index of the winning candidate's name in the name list
	int winner_index=0;
	
	outputfile << "Report of Totals for Each Candidate and City:" << endl;
	// Left align the data...
	outputfile.setf(ios::left);
	outputfile.width(14);
	outputfile << "   ";
	// Print the list of cities
	for(int i=0; i<NUMBER_OF_CITIES; i++) {
		outputfile.width(14);
		outputfile << cities[i];
	}
	outputfile << endl;
	
	// Print the list of candidates and their vote tallies for each city
	for(int j=0; j<NUMBER_OF_CANDIDATES; j++) {
		outputfile.width(14);
		outputfile << candidate_names[j];
		for(int k=0; k<NUMBER_OF_CITIES; k++) {
			outputfile.width(14);
			outputfile << number_of_votes_per_city_per_candidate[j][k];
			total_tally[j] = total_tally[j]
				+ number_of_votes_per_city_per_candidate[j][k];
		}
		outputfile << endl;
		if(total_tally[j]>total_tally[winner_index]) {
			winner_index=j;
		}
	}
	
	outputfile << endl;
	outputfile << "Total Votes for Candidate across all Cities:" << endl;
	for(int n=0; n<NUMBER_OF_CANDIDATES; n++) {
		outputfile.width(14);
		outputfile << candidate_names[n];
		outputfile.width(14);
		outputfile << total_tally[n] << endl;
	}
	
	outputfile << endl;
	outputfile << "Winner of the election is: "
		<< candidate_names[winner_index] << endl;
	
	// Close the output filestream
	outputfile.close();
}


/**
 * Function to determine if the name "name" of a given candidate
 * is valid
 * @param name is the name of the candidate
 * @param candidates[] is the list of candidate names
 * @return the row number of the valid name in the list;
 *	otherwise, return -1;
 */
int candidate_index(string name, string candidate[]) {
	/** Convert name provided to uppercase for
	 * case-insensitive comparison
	 */
	uppercase(name);
	
	if(name == "BUSH") {
		return 0;
	}else if(name == "KERRY") {
		return 1;
	}else if(name == "NADER") {
		return 2;
	}else if(name == "ARMSTRONG") {
		return 3;
	}else if(name == "BUCHANAN") {
		return 4;
	}else{
		// Name provided is not one of the names of the candidates
		return -1;
	}
}


/**
 * Function to determine if the name "name" of a given city
 * is valid
 * @param name is the name of the city
 * @param candidates[] is the list of city names
 * @return the row number of the valid name in the list;
 *	otherwise, return -1;
 */
int city_index(string name, string cities[]) {
	/** Convert name provided to uppercase for
	 * case-insensitive comparison
	 */
	uppercase(name);
	
	if(name == "TOLEDO") {
		return 0;
	}else if(name == "BANGOR") {
		return 1;
	}else if(name == "PERRIS") {
		return 2;
	}else if(name == "IONA") {
		return 3;
	}else if(name == "JUHU") {
		return 4;
	}else if(name == "MALIBU") {
		return 5;
	}else if(name == "SIERRA") {
		return 6;
	}else if(name == "TAOS") {
		return 7;
	}else if(name == "PACOIMA") {
		return 8;
	}else if(name == "NAPA") {
		return 9;
	}else{
		// Name provided is not one of the names of the candidates
		return -1;
	}
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

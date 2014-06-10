#include "Student.h"
#ifndef __GRADUATE
#define __GRADUATE
class Graduate : public Student
{
	public:
		// Constructors...
		Graduate();
		Graduate(string ssn, string lastname, int age);
		Graduate(string firstname, string lastname, string ssn,
			string phone_num, int age);
		Graduate(string firstname, string lastname, string ssn,
			string phone_num, int age, string grad_advisor,
			string thesis_title);
		
		// Accessor functions
		string get_advisor ( );
		string get_thesis( );
		
		// Mutator functions
		void set_thesis (string);
		void set_advisor (string);
		
		// Query Functions
		bool check_thesis(string thesis_title);
		bool check_advisor(string advisor_name);
		
		// Other functions...
		void display();
		void write_to_stream (ofstream &);
	private:
		// Name of the graduate student's advisor
		string advisor;
		//Title of the graduate student's thesis
		string thesis;
};
#endif

#include "Student.h"
#ifndef __UNDERGRADUATE
#define __UNDERGRADUATE
class Undergraduate : public Student
{
	public:
		// Constructors...
		Undergraduate();
		Undergraduate(string ssn, string lastname, int age);
		Undergraduate(string firstname, string lastname, string ssn,
			string phone_num, int age);
		Undergraduate(string firstname, string lastname, string ssn,
			string phone_num, int age, string major_title,
			string minor_title);
	
		// Accessor functions
		string get_major ( );
		string get_minor( );
		
		// Mutator functions
		void set_minor (string);
		void set_major (string);
		
		// Other functions...
		bool check_major(string major_title);
		bool check_minor(string minor_title);
		void display();
		void write_to_stream (ofstream &);
	private:
		// Title of selected major
		string major;
		// Title of selected minor
		string minor;
};
#endif

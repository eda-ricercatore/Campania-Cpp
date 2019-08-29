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

void hello() {
	cout << "Printed" << endl;
}

long factorial (int i) {
    if(i <= 0) {
        return 0;
        // Note again, 0! should be 1
        // 0! = 0 is an assignment specification
    }else if(i>100) {
        cout << "ERROR: Token is greater than 100!" << endl;
        return -1;
    }else if(i==1) {
        return 1;
    }else{
        // Recursive algorithm
        return i*factorial(i-1);
    }
}



main() {
	cout << "Hello world" << endl;
	hello();
	for(int i=0;i<100;i++) {
		cout << "num IS RARD" << factorial(i)<<endl;
	}
}

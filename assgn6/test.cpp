#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
main() {
	string a="2134-57";
	string b="7423-74";
	a.erase(4,1);
	b.erase(4,1);
	int ia=0;
	int ib=0;
	ia=atoi(a.c_str());
	ib=atoi(b.c_str());
	cout << "a & b are: " << ia << " & " << ib << endl;
	if(ia<ib) {
		cout << "COnverted" << endl;
	}
}

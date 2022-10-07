#include <iostream>
using namespace std;

void myOtherFunction() {
        cout << endl << "And this is the result.";
}

void myFunction(const char parameter[80],(otherFunction)()) {
	cout << parameter;
	(*otherFunction)();
}

int main() {
	myFunction("I am calling a function with a function.",myOtherFunction);
	cin.ignore(80,'\n');
	return 0;
}

#include<iostream>
#include<string>
#include<fstream>
#include"other.h"

using namespace std; 


int main(int argc, char* argv[]) {

	ifstream in1;
	fstream out1, out2;

	in1.open(argv[1]);
	out1.open(argv[2]);
	out2.open(argv[3]);
	RadixSort *test = new RadixSort();
	LLStack S;
	test->firstReading(in1,out2);
	in1.clear();
	in1.seekg(0); //same as closing file
	S=test->loadStack(in1,out2);
	S.printStack(out2);
	test->RSort(&S, out1, out2);
	cout<<test->getDigit(1488, 5);
	
	in1.close();
	out1.close();
	out2.close();
	return 0;

}
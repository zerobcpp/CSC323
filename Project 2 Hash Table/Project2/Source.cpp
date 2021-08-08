#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

class listNode {
	friend class hashTable;
	string firstName;
	string lastName;
	listNode* next;
public:
	listNode() {
		firstName = "First";
		lastName = "Last";
	}
	listNode(string fn, string ln) {
		firstName = fn;
		lastName = ln;
		next = NULL;
	}
	void printNode(listNode *n,ofstream &out) {
		if (n->next == NULL)
			out<< '(' << n->firstName << ", "<<n->lastName<< " NULL" << ")-->NULL";
		
		else
			out << '(' << n->firstName << ", "<<n->lastName <<' '<< n->next->firstName << ")-->";
	}
};
const int bucketsize = 29; //??WORK AROUND
class hashTable{
	char op;
	int bucketSize = bucketsize;
	//listNode* hashTable = new listNode[bucketSize]();
	listNode * hashTable[bucketsize];
public:
	void createHashTable(){
		
		for (int i = 0; i < bucketSize;i++) {
			listNode* dummyfirst = new listNode("First", "Last");
			hashTable[i] = dummyfirst;
		}
	}
	int Doit(string lastName) {
		unsigned long int hash_value = 0;
		for (auto i = 0; i < lastName.size(); i++) {
			hash_value = hash_value * 32 + (int)(lastName[i]);
		}
		return (hash_value % bucketSize);
	}
	void informationProcessing(ifstream& inFile, ofstream& outFile2) {
		//Splits string
		vector<string> token;
		int index;
		string x;
		while (!inFile.eof()) {
			getline(inFile, x);
			stringstream get(x);
			string intermediate;
			while (getline(get, intermediate, '\t')) {
				token.push_back(intermediate);
			}
			index = Doit(token.at(2));
			outFile2 << "Tokenizing: First Name: " << token.at(1) << "\t Last Name: " << token.at(2) << "\t Operation: " << token.at(0);;
			outFile2 << "\t H(x) = " << index << endl; //S4
			if (token.at(0) == "+") {
				hashInsert(index, token.at(1), token.at(2), outFile2);
			}
			else if (token.at(0) == "-")
				hashDelete(index, token.at(1), token.at(2),outFile2);
			else
				hashRetrieval(index, token.at(1), token.at(2), outFile2);
			token.clear();
		}
	}
	int getBucketSize(ifstream &buck) {
		string bucket;
		getline(buck, bucket);
		cout << bucket;
		bucketSize = stoi(bucket);
		return bucketSize;
	}
	listNode* findSpot(int index, string fn, string ln) {
		listNode* current = hashTable[index];
		int i = 1; //0 being the dummynode
		while (current->next != NULL && current->next->lastName < ln) {
			current = current->next;
			i++;
		}
		while (current->next != NULL && current->next->lastName == ln && current->next->firstName < fn) {
			current = current->next;
			i++;
		}
		return current;
	}
	void hashInsert(int index, string fn, string ln, ofstream &out2) {
		out2 << "*** Performing hashInsert on" << fn << ", " << ln <<"\n\n";
		listNode* spot = findSpot(index, fn, ln);
		if (spot->next != NULL && spot->next->lastName == ln && spot->next->firstName == fn)
			out2 << "*** Warning, the record is already in the database!\n";
		else {
			listNode* n = new listNode(fn, ln);
			n->next = spot->next;
			spot->next = n;
			printList(index, out2);
		}
	}
	void hashDelete(int index, string fn, string ln, ofstream &out2) {
		out2 << "*** Performing hashDelete on "<<fn<<' '<<ln<<"\n\n";
		listNode* spot = findSpot(index, fn, ln);
		if (spot->next != NULL && spot->next->lastName == ln && spot->next->firstName == fn) {
			listNode* junk = spot->next;
			spot->next = spot->next->next;
			junk = NULL;
			delete junk;
			printList(index, out2);
			out2 << endl << "deleted\n";
		}
		else
			out2 << "*** Warning, the record is *not* in the database!\n";
	}
	void hashRetrieval(int index, string fn, string ln, ofstream &out2) {
		out2 << "*** Performing hashRetrieval on "<<fn<<' '<<ln<<"\n\n";
		listNode* spot = findSpot(index, fn, ln);
		if (spot->next != NULL && spot->next->lastName == ln && spot->next->firstName == fn) {
			out2 << "Yes, the record is in the database!: " << "\t" << fn << '\t' << ln << endl;
		}
		else
			out2 << "No, the record is not in the database!: " << "\t" << fn << '\t' << ln << endl;
	}
	void printList(int index, ofstream &out) {
		listNode* current = hashTable[index];
		while (current->next != NULL) {
			current->printNode(current, out);
			current = current->next;
		}
		current->printNode(current,out);
		out << endl;
	}
	void printHashTable(ofstream &out) {
		cout << "\n--PRINTING WHOLE HASH TABLE--\n--Bucket Size = " << bucketSize << endl;
		for (int i = 0; i < bucketSize; i++) {
			out << "hashTable[" << i << "]: ";
			printList(i, out);
			out << endl << endl;
		}
	}
};


int main(int argc, char* argv[]) {
	ifstream data, buckettxt;
	ofstream out1, out2;
	data.open(argv[1]);
	out2.open(argv[4]);
	out1.open(argv[3]);
	//buckettxt.open(argv[2]); BEING work arounded

	hashTable * testhashtable = new hashTable();
	testhashtable->createHashTable();
	testhashtable->informationProcessing(data,out2);
	testhashtable->printHashTable(out1);
	data.close();
	out2.close();
	out1.close();
	return 0;

}
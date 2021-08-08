#pragma once
#ifndef other_h
#define other_h
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;

class listNode {

	friend class LLStack;
	friend class LLQueue;
	friend class LLlist;
	friend class RadixSort;
public:
	int data;
	listNode* next;
	listNode(int data) {
		this->data = data;
		next = NULL;
	}
	void printNode(listNode* node, fstream& outFile) {
		if (node->next == NULL)
			outFile << '(' << node->data << ", " << "NULL" << ")-->";
		else
			outFile << '(' << node->data << ", " << node->next->data << ")-->";
	}
};
class LLStack {
	friend class RadixSort;
public:
	listNode* top;
	LLStack() {
		listNode* dummynode = new listNode(-9999);
		dummynode->next = NULL;
		top = dummynode;
	}
	void push(listNode* newNode) {
		listNode* current = newNode;
		if (isEmpty())
			top = current; //Maybe for later future.
		else {
			current->next = top;
			top = current;
		}
	}
	listNode pop() {
		if (isEmpty())
			return NULL;
		else {
			listNode* temp = top;
			top = top->next;
			return *temp;
		}
	}

	bool isEmpty() {
		if (top == NULL)
			return true;
		return false;
	}
	void buildStack(fstream& in, fstream& outFile1) {
		string raw;
		int data;
		while (!in.eof()) {
			getline(in, raw);
			if (raw[0] == '+') {
				data = stoi(raw.substr(2));
				listNode* x = new listNode(data);
				push(x);
			}
			else {
				listNode junk = pop();
				if (junk.data == NULL)
					outFile1 << "the Stack is empty" << endl;
				else {
					junk = NULL;
					delete& junk;
				}
			}
			printStack(outFile1);
		}
	}
	void printStack(fstream& outFile1) {
		outFile1 << "Top-->";
		listNode* current = top;
		while (current != NULL) {
			current->printNode(current, outFile1);
			current = current->next;
		}
		outFile1 << "NULL" << endl;
	}
};

class LLQueue {
	friend class RadixSort;
	listNode* head;
	listNode* tail;
public:
	LLQueue() {
		listNode* dummynode = new listNode(-9999);
		head = tail = dummynode;
	}
	
	void insertQ(listNode* newNode) {
		if (isEmpty()) {
			;
		}
		tail->next = newNode;
		tail = newNode;
	}
	listNode deleteQ() {
		if (isEmpty())
			return NULL;
		else {
			listNode* temp;
			temp = head->next;
			head->next = head->next->next;
			return *temp;
		}
	}
	bool isEmpty() {
		if (head->next == NULL)
			return true;
		return false;
	}
	void buildQueue(fstream& in, fstream& out) {
		string raw;
		int data;
		while (!in.eof()) {
			getline(in, raw);
			if (raw[0] == '+') {
				data = stoi(raw.substr(2));
				listNode* x = new listNode(data);
				insertQ(x);
			}
			else {
				listNode junk = deleteQ();
				if (junk.data == NULL)
					out << "the Queue is empty" << endl;
				else {
					junk = NULL;
					delete(&junk);
				}
			}
			printQ(out);
		}
	}
	void printQ(fstream& outFile2) {
		listNode* current = head;
		outFile2 << "Front -->";
		while (current != NULL) {
			current->printNode(current, outFile2);
			current = current->next;
		}
		outFile2 << "NULL" << endl;
	}
};

class LLlist {
	listNode* listHead;
public:
	LLlist() {
		listNode* dummynode = new listNode(-9999);
		listHead = dummynode;
	}
	void buildList(fstream& in, fstream& out) {
		string raw;
		int data;
		while (!in.eof()) {
			getline(in, raw);
			data = stoi(raw.substr(2));
			if (raw[0] == '+') {
				listNode* x = new listNode(data);
				listInsert(x);
			}
			else {
				listNode junk = deleteOneNode(data);
				if (junk.data == NULL)
					out << "the data is not in the list\n";
				else {
					junk = NULL;
					delete& junk;
				}
			}
			printList(out);
		}
	}
	void listInsert(listNode* newNode) {
		listNode* current = listHead;
		listNode* n = newNode;
		while (current->next != NULL)
			current = current->next;
		if (current->data == n->data) {
			listNode* temp = current->next;
			current->next = n;
			n->next = temp;
		}
		else {
			current->next = n;
			cout << current->next->data << endl;
		}
	}
	listNode deleteOneNode(int data) {
		listNode* current = listHead;
		listNode* prev = NULL;
		listNode* temp;
		while (current->next != NULL && current->next->data != data)
			current = current->next;
		if (current->next != NULL && current->next->data == data) {
			prev = current;
			current = current->next->next;
			temp = prev->next;
			prev->next = current;
			return *temp;
		}
		else
			return NULL;

	}
	void printList(fstream& outFile3) {
		outFile3 << "listHead-->";
		listNode* current = listHead;
		while (current != NULL) {
			current->printNode(current, outFile3);
			current = current->next;
		}
		outFile3 << "NULL\n";

	}
};

class RadixSort {

	int tableSize = 10,
		data, currentTable, previousTable, numDigits, offSet, currentPosition, currentDigit;
	LLQueue** hashTable;
public:
	RadixSort() {
		numDigits = 0;
		currentTable = 0;
		previousTable = 0;
		hashTable = new LLQueue*[2];
		for (int i = 0; i < 2; i++)
			hashTable[i] = new LLQueue[tableSize];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < tableSize; j++) {
				hashTable[i][j] = LLQueue();
			}
		}
	}
	void firstReading(ifstream& in,fstream &out) {
		int temp = 0, min = INT_MAX, max = INT_MIN;
		while (!in.eof()) {
			in >> temp;
			if (temp > max)
				max = temp;
			if (min>temp)
				min = temp;
			//printf("temp: %d \t min: %d \t max: %d \n", temp, min, max);
		}
		offSet = abs(min);
		max += offSet;
		numDigits = to_string(max).size();
		out << "Offset: " << offSet << endl;
		out << "Number of Digits: " << numDigits << endl;
		out << "Min: " << min << "\tMax: " << max << endl;
	}
	LLStack loadStack(ifstream &in, fstream &out) {
		cout << "***Performing loadStack***\n";
		int data;
		LLStack S;
		while (!in.eof()) {
			in >> data;
			data += offSet;
			listNode* n = new listNode(data);
			S.push(n);
		}
		return S;
	}
	void RSort(LLStack *S, fstream &out, fstream &out2) {
		cout << "***Performing RSort***\n";
		currentPosition = 0;
		currentTable = 0;
		moveStack(S, currentPosition, currentTable);
		printTable(currentTable, out);
		currentPosition++; //S4
		currentTable = 1;
		previousTable = 0;
		int currentQueue = 0;
		
		while (currentPosition < numDigits) {
			while (currentQueue <= tableSize - 1) {
				while (hashTable[previousTable][currentQueue].head->next != NULL) {
					listNode newNode = hashTable[previousTable][currentQueue].deleteQ();
					listNode *n = new listNode(newNode.data);
					int hashindex = getDigit(newNode.data, currentPosition);
					hashTable[currentTable][hashindex].insertQ(n);
				}
				currentQueue++;
			}
			printTable(currentTable, out2);
			previousTable = currentTable;
			currentTable = (currentTable + 1) % 2;
			currentQueue = 0;
			currentPosition++;
			//Placed here due to rigidity change due to ? reason
			for (int j = 0; j < tableSize; j++) {
				hashTable[currentTable][j] = LLQueue();
			}
		}
		printSortedData(previousTable, out);

		//while (currentPosition < numDigits) {
		//	for (currentQueue; currentQueue >= tableSize - 1;) { //currentQueue >= tablesize-1
 	//			while (hashTable[previousTable][currentQueue].head->next != NULL) {
		//			listNode n = hashTable[previousTable][currentQueue].deleteQ();
		//			if (n.data == -9999)
		//				break;
		//			listNode *newNode = new listNode(n.data);
		//			int raw = n.data;
		//			int hashindex = getDigit(raw, currentPosition);
		//			hashTable[currentTable][hashindex].insertQ(newNode);
		//		}
		//		cout << "Loop: " << currentQueue << '\t' << previousTable <<'\n';
		//		currentQueue++;
		//	}
		//	printTable(currentTable, out2);
		//	previousTable = currentTable;
		//	currentTable = (currentTable + 1) % 2;
		//	currentQueue = 0;
		//	currentPosition++;
		//}
		//printSortedData(previousTable, out);
	}
	void moveStack(LLStack *S, int position, int table) {
		cout << "***Performing Move Stack ***\n";  //original at 0
		while (!S->isEmpty()) {
			listNode* n = new listNode(S->pop().data);
			if (n->data == -9999)
				break;
			int hashIndex = getDigit(n->data, position);
			hashTable[table][hashIndex].insertQ(n);
		}
	}
	int getLength(int data) {
		return to_string(data).size();
	}
	//int getDigit(int data, int position) {
	//	string raw = to_string(data);
	//	int positionData, current = 0;
	//	for (int i = to_string(data).size() - 1; i >= 0; i--) {
	//		if (current == position)
	//			positionData = raw[i] - 48;
	//		current++;
	//	}
	//	if ((current < position || raw[position] == NULL) || data ==0 )
	//		return 0;
	//	return positionData;
	//}
	//int getDigit(int data, int position) {
	//	string raw = to_string(data);
	//	int positionData, current = 0;
	//	for (int i = 0; i < getLength(data) - 1; i++) {
	//		if (current == position)
	//			return raw[getLength(data) - (current+1)]-48;              
	//		else
	//			current++;
	//	}
	//}
	int getDigit(int data, int position) {
		string raw = to_string(data);
		int positionData, current = 0;
		positionData = stoi(raw);
		for (int i = 0; i < position; i++) {
			positionData /= 10;
		}
		if (positionData == 0)
			return 0;
		else
			return positionData % 10;


	}

	void printTable(int current, fstream &out) {
		cout << "--- Printing hash table ---\n";
		for (int i = 0; i < tableSize; i++) {
			hashTable[current][i].printQ(out);
				//cout << hashTable[current][i].tail->data;
		}
	}
	void printSortedData(int current, fstream& out) {
		cout << "--- Printing Sorted Data ---\n";
		for (int i = 0; i < tableSize; i++) {
			out << "hashTable[" << current << ']' << '[' << i << "]:";
			while (hashTable[current][i].head->next!=NULL) {
				listNode n = hashTable[current][i].deleteQ();
				if (n.data == -9999)
					out << "(" << n.data << ", " << ")-->";
				else
					out << "(" << n.data - offSet << ", " << ")-->";
					
			}
			out << endl;
		}
	}

};

#endif
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

static const int NULLPTR = 0;

class listNode {
	
	friend class LLStack;
	friend class LLqueue;
	friend class LLlist;
public:
	int data;
	listNode* next;
	listNode(int data) {
		this->data = data;
		next = NULL;
	}
	void printNode(listNode *node, fstream &outFile) {
		if(node->next==NULL)
			outFile << '(' << node->data << ", " << "NULL" << ")-->";
		else
			outFile << '(' << node->data << ", " << node->next->data << ")-->";
	}
};
class LLStack {
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
	void buildStack(fstream &in, fstream &outFile1) {
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
				listNode *junk = &pop();
				if (junk->data == NULL)
					outFile1 << "the Stack is empty" << endl;
				else {
					junk = NULL;
					delete junk;
					;
				}
			}
		}
		printStack(outFile1);
	}
	void printStack(fstream &outFile1) {
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
	listNode* head;
	listNode* tail;
public:
	LLQueue() {
		listNode* dummynode = new listNode(-9999);
		head = dummynode;
		tail = dummynode;
	}
	void buildQueue(fstream &in, fstream &out) {
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
				listNode* junk = &deleteQ();
				if (junk->data == NULL)
					out << "the Queue is empty" << endl;
				else {
					junk = NULL;
					delete(junk);
				}
			}
		}
		printQ(out);
		
	}
	void insertQ(listNode *newNode) {
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
	void printQ(fstream &outFile2){
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
	void buildList(fstream &in, fstream &out) {
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
				listNode* junk = &deleteOneNode(data);
				if (junk->data == NULL)
					out << "the data is not in the list\n";
				else {
					junk = NULL;
					delete junk;
				}
			}
		}
		printList(out);
	}
	void listInsert(listNode *newNode) {
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
		while (current->next!=NULL && current->next->data != data)
			current = current->next;
		if (current->next!=NULL && current->next->data == data) {
			prev = current;        
			current = current->next->next;
			temp = prev->next;
			prev->next = current;
			return *temp;
		}
		else
			return NULL;

	}
	void printList(fstream &outFile3) {
		outFile3 << "listHead-->";
		listNode* current = listHead;
		while (current != NULL) {
			current->printNode(current, outFile3);
			current = current->next;
		}
		outFile3 << "NULL";

	}
};
int main(int argc, char* argv[]) {
	fstream inFile, outFile1, outFile2, outFile3;
	inFile.open(argv[1]); //S1
	inFile.close();//S2
	inFile.open(argv[1]);//S3
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	outFile3.open(argv[4]);
	LLQueue* queue = new LLQueue();
	LLStack* stack = new LLStack();
	LLlist* list = new LLlist();

	stack->buildStack(inFile, outFile1);

	inFile.clear();
	inFile.seekg(0);
	queue->buildQueue(inFile, outFile2);

	inFile.clear();
	inFile.seekg(0);
	list->buildList(inFile, outFile3);

	inFile.close();
	outFile1.close();
	outFile2.close();
	outFile3.close();
	
	cout << "Project 1 : Implementation of Stack/Queue/List\n";
	return 0;

}
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class uEdge {
	int ni;
	int nj;
	int cost;
	uEdge* next;
public:
	uEdge(int ni, int nj, int cost) {
		this->ni = ni;
		this->nj = nj;
		this->cost = cost;
		this->next = NULL;
	}
	void printEdge(ofstream& out) {
		out << endl << cost << " Cost Edge has been deleted" << endl;
		out << "Info: <" << ni << "," << nj << ">" << endl;
	}
	int getCost() {
		return cost;
	}
	int getNi() {
		return ni;
	}
	int getNj() {
		return nj;
	}

	uEdge* getNext() {
		return next;
	}
	void setNext(uEdge* n) {
		next = n;
	}
};
class primMST {
public:
	int numNode;
	int nodeSetA;
	int* whichSet;
	uEdge* edgeListHead;
	uEdge* MSTListHead;
	int totalMSTCost;

	primMST() {
		numNode = 0;
		nodeSetA = 0;
		totalMSTCost = 0;
		whichSet = { 0 };
		edgeListHead = new uEdge(0, 0, 0);
		MSTListHead = new uEdge(0, 0, 0);
	}
	void listInsert(uEdge* n) {
		uEdge* current = edgeListHead;
		while (current->getNext() != NULL && current->getNext()->getCost() < n->getCost())
			current = current->getNext();
		if (current->getCost() == n->getCost()) {
			n->setNext(current->getNext());
			current->setNext(n);
		}
		else {
			n->setNext(current->getNext());
			current->setNext(n);
		}


	}
	uEdge* edgeDelete() {
		uEdge* current = edgeListHead;
		while (current->getNext() != NULL) {
			if ((whichSet[current->getNext()->getNi()] != whichSet[current->getNext()->getNj()]) &&
				(whichSet[current->getNext()->getNi()] == 1 || whichSet[current->getNext()->getNj()] == 1)) {
				uEdge* e = current->getNext();
				current->setNext(current->getNext()->getNext());
				return e;
			}
			current = current->getNext();
		}
		return NULL;
	}
	void addEdge(uEdge* n) {
		uEdge* current = MSTListHead;
		while (current->getNext() != NULL)
			current = current->getNext();
		if (current->getNext() == NULL) {
			current->setNext(n);
		}
	}
	void printSet(ofstream& out) {
		for (int i = 0; i <= numNode; i++) {
			out << whichSet[i];
		}
		out << endl;
	}
	void printEdgeList(ofstream& out) {
		uEdge* current = edgeListHead;
		out << "edgeListHead --> <0,0,0,N1> --> ";
		current = current->getNext();
		int i = 1;
		string s;
		while (current != NULL) {
			s = "N" + to_string(i);
			out << "<" << s << ", " << s << ", " << current->getCost() << ", ";
			i += 1;
			s = "N" + to_string(i);
			out << s << ">--> ";
			current = current->getNext();
		}
		out << endl;
	}
	void printMSTList(ofstream& out) {
		out << "{ ";
		uEdge* current = MSTListHead->getNext();
		while (current != NULL) {
			out << "<" << current->getNi() << "," << current->getNj() << "," << current->getCost() << ">";
			current = current->getNext();
		}
		out << "}" << endl;

	}
	bool setB_Empty() {
		for (int i = 1; i <= numNode; i++) {
			if (whichSet[i] != 1)
				return false;
		}
		return true;
	}
	void updateMST(uEdge* n) {
		n->setNext(NULL);
		addEdge(n);
		totalMSTCost += n->getCost();
		if (whichSet[n->getNi()] == 1)
			whichSet[n->getNj()] = 1;
		else
			whichSet[n->getNi()] = 1;
	}
	void setNodeSetA(int a) {
		nodeSetA = a;
		cout << "Current node set A: " << nodeSetA << endl;
	}
	void setNumNode(int n) {
		numNode = n;
		cout << "Current Number of Node: " << numNode << endl;
		//update the whichSet
		whichSet = new int[numNode + 1];
		fill(whichSet, whichSet + numNode, 2);

	}
	int getwhichSet(int n) {
		return whichSet[n];
	}
};
int main(int argc, char* argv[]) {
	ifstream inf;
	ofstream outf, debug;
	inf.open(argv[1]);
	debug.open(argv[3]);
	outf.open(argv[4]);
	primMST test = primMST();
	test.setNodeSetA(stoi(argv[2]));
	int num, ni, nj;
	inf >> num;
	test.setNumNode(num);
	test.whichSet[test.nodeSetA] = 1;
	while (inf >> ni && inf >> nj && inf >> num) {
		uEdge* n = new uEdge(ni, nj, num);
		test.listInsert(n);
		test.printEdgeList(debug);
	}
	while (!test.setB_Empty()) {
		uEdge* nextEdge = test.edgeDelete();
		nextEdge->printEdge(debug);
		test.updateMST(nextEdge);
		test.printSet(debug);
		test.printEdgeList(debug);
		test.printMSTList(debug);
	}
	outf << "*** Prim's MST of the input graph G is: ***" << endl
		<< "Num Nodes: " << test.numNode << endl
		<< "*** MST Total Cost = " << test.totalMSTCost << endl;
	test.printMSTList(outf);
	inf.close();
	debug.close();
	outf.close();
	return 0;
}
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
class image {
	int nrows, ncols;
	int minVal, maxVal;
	int power2size;
public:
	int** imgarr;
	image() {
		//can be potentially use to set up the dynamic array
		//*imgarr = new int[nrows * ncols];
	}
	int computePower2(int row, int col) { //Loop is refrained for runtime optimization
		int size = row > col ? row : col;
		float expoenent = log2(size);
		power2size = pow(2, ceil(expoenent));
		return power2size;
	}
	void loadImage(ifstream& in) {
		int raw;
		int i = 0, j = 0;
		while (in >> raw) {
			if (j > ncols - 1) {
				j = 0;
				i++;
			}
			imgarr[i][j] = raw;
			j++;
		}
	}

	void zero2DArr(int** image) {
		//Code below are assumed from lectures and base on the method's name
		for (int i = 0; i < power2size; i++) {
			for (int j = 0; j < power2size; j++) {
				image[i][j] = 0;
				//cout << image[i][j] << " ";
			}
			//cout << endl;
		}
		imgarr = image;
	}
	void setRowCol(int row, int col) {
		nrows = row;
		ncols = col;
	}
	void displayImageArray(ofstream& out) {
		out << "Power 2 is: " << power2size << endl;
		for (int i = 0; i < power2size; i++) {
			for (int j = 0; j < power2size; j++)
				out << imgarr[i][j] << " ";
			out << endl;
		}
	}

};
class QtTreeNode {
public:
	int color;
	int upperR, upperC;
	int size;
	QtTreeNode* NWKid = NULL,
		* NEKid = NULL,
		* SWKid = NULL,
		* SEKid = NULL;
	QtTreeNode(int c, int row, int col, int n, QtTreeNode* nw, QtTreeNode* ne, QtTreeNode* sw, QtTreeNode* se) {
		color = c;
		upperR = row;
		upperC = col;
		size = n;
		NWKid = nw;
		NEKid = ne;
		SEKid = se;
		SWKid = sw;
	}
	void printQtNode(ofstream& out) {
		if (NWKid && NEKid && SEKid && SWKid) {
			out << "Color: " << color << " "
				<< "Upper Row: " << upperR << " "
				<< "Upper Cols: " << upperC << " "
				<< "Size: " << size << " "
				<< "NW's Color: " << NWKid->color << " "
				<< "NE's Color: " << NEKid->color << " "
				<< "SW's Color: " << SWKid->color << " "
				<< "SE's Color: " << SEKid->color << " " << endl;
		}
		else if (NWKid && NEKid && SWKid) {
			out << "Color: " << color << " "
				<< "Upper Row: " << upperR << " "
				<< "Upper Cols: " << upperC << " "
				<< "Size: " << size << " "
				<< "NW's Color: " << NWKid->color << " "
				<< "NE's Color: " << NEKid->color << " "
				<< "SW's Color: " << SWKid->color << " " << endl;
		}
		else if (NWKid && NEKid) {
			out << "Color: " << color << " "
				<< "Upper Row: " << upperR << " "
				<< "Upper Cols: " << upperC << " "
				<< "Size: " << size << " "
				<< "NW's Color: " << NWKid->color << " "
				<< "NE's Color: " << NEKid->color << " " << endl;
		}
		else if (NWKid) {
			out << "Color: " << color << " "
				<< "Upper Row: " << upperR << " "
				<< "Upper Cols: " << upperC << " "
				<< "Size: " << size << " "
				<< "NW's Color: " << NWKid->color << " " << endl;
		}
		else {
			out << "Color: " << color << " "
				<< "Upper Row: " << upperR << " "
				<< "Upper Cols: " << upperC << " "
				<< "Size: " << size << " " << endl;
		}
	}
	void setColor(int c) {
		color = c;
	}
};
class QuadTree {
public:
	QtTreeNode* TreeRoot;
	QtTreeNode* buildQuadTree(int** imgarr, int upR, int upC, int size, ofstream& out) {
		QtTreeNode* newNode = new QtTreeNode(-1, upR, upC, size, NULL, NULL, NULL, NULL);
		newNode->printQtNode(out);

		if (size == 1)
			newNode->color = imgarr[upR][upC];
		else {
			int halfsize = size / 2;
			newNode->NWKid = buildQuadTree(imgarr, upR, upC, halfsize, out);
			newNode->NEKid = buildQuadTree(imgarr, upR, upC + halfsize, halfsize, out);
			newNode->SWKid = buildQuadTree(imgarr, upR + halfsize, upC, halfsize, out);
			newNode->SEKid = buildQuadTree(imgarr, upR + halfsize, upC + halfsize, halfsize, out);
			int sumColor = newNode->NWKid->color + newNode->NEKid->color +
				newNode->SWKid->color + newNode->SEKid->color;
			if (sumColor == 0) {
				newNode->color = 0;
				newNode->NWKid = NULL;
				newNode->NEKid = NULL;
				newNode->SWKid = NULL;
				newNode->SEKid = NULL;
			}
			else if (sumColor == 4) {
				newNode->color = 1;
				newNode->NWKid = NULL;
				newNode->NEKid = NULL;
				newNode->SWKid = NULL;
				newNode->SEKid = NULL;
			}
			else
				newNode->color = 5;
		}
		return newNode;
	}

	bool isLeaf(QtTreeNode* n) {
		return !n->NWKid && !n->NEKid && !n->SWKid && !n->SEKid;
	}
	void preOrder(QtTreeNode* n, ofstream& out) {
		if (isLeaf(n))
			n->printQtNode(out);
		else {
			n->printQtNode(out);
			preOrder(n->NWKid, out);
			preOrder(n->NEKid, out);
			preOrder(n->SWKid, out);
			preOrder(n->NEKid, out);
		}
	}
	void postOrder(QtTreeNode* n, ofstream& out) {
		if (isLeaf(n))
			n->printQtNode(out);
		else {
			postOrder(n->NWKid, out);
			postOrder(n->NEKid, out);
			postOrder(n->SWKid, out);
			postOrder(n->NEKid, out);
			n->printQtNode(out);
		}

	}
};
int main(int argc, char* argv[]) {
	ifstream input;
	ofstream out, out2;
	input.open(argv[1]);
	out.open(argv[2]);
	out2.open(argv[3]);
	int  row, col, minval, maxval;
	input >> row >> col >> minval >> maxval; //Step 2
	//Debugging and Specification purposes
	image test;
	int pow2 = test.computePower2(row, col);
	out << "Original Row: " << row << ", Original Col: " << col << ", #POWER2# : " << pow2 << endl;;
	int** imagearray = new int* [pow2];
	for (int i = 0; i < pow2; i++) {
		imagearray[i] = new int[pow2];
	}
	test.setRowCol(row, col);
	test.zero2DArr(imagearray);
	test.loadImage(input);
	test.displayImageArray(out2);
	cout << "array\n";
	for (int i = 0; i < pow2; i++) {
		for (int j = 0; j < pow2; j++)
			cout << imagearray[i][j];
		cout << endl;
	}
	// ^^ Step 5 ^^ //
	QuadTree testTree;
	testTree.TreeRoot = testTree.buildQuadTree(test.imgarr, 0, 0, pow2, out2);
	out << "------------- Preorder ---------------" << endl;
	testTree.preOrder(testTree.TreeRoot, out);
	out << "------------- Postorder ---------------" << endl;
	testTree.postOrder(testTree.TreeRoot, out);

	input.close();
	out.close();
	out2.close();
	return 0;
}
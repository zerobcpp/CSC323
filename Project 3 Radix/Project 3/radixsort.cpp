#include <iostream>
#include <fstream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class listNode{
  friend class LLSTACK;
  friend class LLQ;
  friend class radixSort;
  int data;
  listNode *next;
  listNode(int d){
  	data =d;
  	next =NULL;
  }
  string tostring(){
  	string s ="";
  	if(next==NULL){
  		s= s+ " ( " + to_string(data)+ ", NULL)";
	  }else{
	  	s = s+ "( " +to_string(data) +", "+ to_string(next->data) +" )";
	  } 
	  return s;
  }
};
class LLSTACK{
   friend class radixSort;
	listNode * top;
	LLSTACK(){
		top =NULL;
	}
	bool isEmpty(){
		return (top==NULL);
	}
	void push(listNode * newNode){
		listNode* temp = newNode;
		temp->next =top;
		top=newNode;
	}
	listNode* pop(){
		listNode* temp;
		if(isEmpty()){
			return 0;
		}else{
			temp=top;
			top=top->next;
			return temp;
		}
	}
	void printStack(ofstream & out2){
		out2<<"Below is the stack: "<<endl;
	    cout<<"Below is the stack: "<<endl;
	    listNode* temp = top;
	    cout<<"Top:";
	    out2<<"Top:";
	    while(temp!=NULL){
	    	cout<<"->"<<temp->tostring();
	    	out2<<"->"<<temp->tostring();
	    	temp=temp->next;
		}
		out2<<" -> NULL"<<endl;
		cout<<" -> NULL"<<endl;
	    
	}
}; 
class LLQ{
 
	friend class radixSort;
	listNode * head,*tail;
	listNode* dummy;
	LLQ(){
       head=tail=dummy=NULL;
		
	}
	bool isEmpty(){
		return (head==NULL);
	}
	void addTail(listNode * newNode){
		if(isEmpty()){
			tail =newNode;
			head= tail;
		}else{
		
		tail->next =newNode;
		tail = newNode;
	}
	}
  listNode* deleteHead(){
        listNode* temp = head;
        if(head == tail) 
		{
		head = tail = NULL;
	}
        else {
		head = head->next;
    }
    temp->next=NULL;
    return temp;
    }
	void printQueue(ofstream & out2){
		listNode * temp = head;
		cout<<"Front ";
		out2<<"Front ";
		while(temp!=NULL){
			cout<<"--> "<<temp->tostring(); 
			out2<<"--> "<<temp->tostring(); 
			temp=temp->next;
		}
		cout<<"--> NULL"<<endl;
		out2<<"--> NULL"<<endl;
 		temp =tail;
		cout<<"Tail:";
		out2<<"Tail:";
	  while(temp!=NULL){
        	cout<<" ----> " << temp->tostring();
            out2<<" ----> " << temp->tostring();
            temp = temp->next;
        }
        cout<< " ----> NULL" << endl;
        out2<< " ----> NULL" << endl;
	}
};
class radixSort{
	friend class LLQ;
	public:
    int tableSize, currentTable, previousTable, maxDigits, offSet, currentDigit,data;
    LLSTACK *stack;
   LLQ** hashTable;

    radixSort(){
    	data =0;
        tableSize = 10;
        currentTable = 0;
        previousTable = 1;
        maxDigits = 0;
        offSet = 0;
        currentDigit = 1;
       	stack = new LLSTACK();
		hashTable = new LLQ*[2];
	  for(int i =0; i<2; i++) 
		{
		hashTable[i] = new LLQ[tableSize];
	}
        for(int i =0; i<2; i++)
            for(int j = 0; j <tableSize; j++)
                hashTable[i][j] = LLQ();
    }
      // - firstReading (inFile, int, int) // to determine the maxDigits and offSet
   void firstReading(ifstream & in){
   	   int temp=0;  int max=0; int min=0;
   	   while(in.good()){
   	   	   in>>temp;
   	     if(!in.eof())
   			if(temp>max)
   				max=temp;
   			if(min>temp)
   				min=temp;
   	   	  // cout<<temp<<endl;
		  }
		 //cout<<max<<"    "<<min<<endl;  find max and min is good
		 offSet = abs(min);
		 maxDigits = to_string(max).length();
	//	 cout<<maxDigits;good
   }

     void loadStack(ifstream & in, ofstream & out){
   	     listNode* temp;
   	     int data;
   	     while(in.good()){
   	        in>>data;
   	        if(!in.eof()){
   	       data+= offSet;
   	       temp = new listNode(data);
			stack->push(temp);
			 }
			}
		stack->printStack(out);

}
    int getDigit(int d){
    	return (d%(10*currentDigit));
	}

    void sort(ofstream &out1, ofstream &out2){
        dumpStack(out2);
        currentDigit++;
        while(currentDigit<=maxDigits){
            int temp = currentTable;
            currentTable = previousTable;
            previousTable = temp;
        
            for(int i =0; i<tableSize; i++){
                while(hashTable[previousTable][i].head!=NULL){
                    listNode *temp = hashTable[previousTable][i].deleteHead();
                    string str = to_string(temp->data);
                    int digit = str[str.length()-currentDigit] - '0';
                    if(str.length() < currentDigit) digit = 0;
                    hashTable[currentTable][digit].addTail(temp);
                }
            }
            printTable(out2);
            currentDigit++;
        }

        getSortedData(out1);
    }

    void dumpStack(ofstream & out){
		listNode * node;
		int oneDigit, hashIndex;
		while(!stack->isEmpty()){
		 node = stack->pop();
		 oneDigit =getDigit(node->data);
		 hashIndex =oneDigit;
		 hashTable[currentTable][hashIndex].addTail(node);
		}
		hashTable[currentTable][hashIndex].printQueue(out);

	}

    void printTable(ofstream &out){
        out <<"The hash table "<<endl;
        cout<<"The hash table "<<endl;
        for(int i = 0; i< tableSize; i++){
            if(hashTable[currentTable][i].head!=NULL){
                out << "Table index  [" << to_string(currentTable) << "][" << to_string(i) <<"]: ";
                cout<< "Table index [" << to_string(currentTable) << "][" << to_string(i) <<"]: ";
                hashTable[currentTable][i].printQueue(out);
            }
        }
    }

    void getSortedData(ofstream &out){
    	cout<<"The sorted result"<<endl;
    	out<<"The sorted result"<<endl;
        for(int i = 0; i<tableSize; i++){
            while(!hashTable[currentTable][i].isEmpty()){
                listNode *temp = hashTable[currentTable][i].deleteHead();
                out << temp->data - offSet << " >>> ";
                cout<<temp->data - offSet << " >>> ";
            }
        }
    }
};

int main(int argc, char** argv){
 	ifstream inFile;
	ofstream outFile1, outFile2;
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	radixSort *sort = new radixSort();
	sort->firstReading(inFile);
	inFile.close();
	inFile.open(argv[1]);
	sort->loadStack(inFile,outFile2);
	sort->sort(outFile1,outFile2);
	inFile.close();
	outFile1.close();
	outFile2.close();
		return 0;
}

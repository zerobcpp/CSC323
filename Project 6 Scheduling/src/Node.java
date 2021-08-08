
public class Node {
	int jobID;
	int jobTime;
	Node next;
	Node(){
		jobID = 0;
		jobTime = 0;
		next = null;
	}
	Node(int job, int time){
		jobID = job;
		jobTime = time;
		next = null;
	}
}

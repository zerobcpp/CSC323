public class stack {
	AstarNode top;
	
	stack(){
		top = new AstarNode(-1,-1,-1);
	}
	public void push(AstarNode n) {
		n.next = top;
		top = n;
	}
	AstarNode pop() {
		AstarNode temp = top;
		top = top.next;
		return temp;
	}
}

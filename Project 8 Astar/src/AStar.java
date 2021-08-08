import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Stack;

public class AStar {
	AstarNode startNode, goalNode, Open, Close, cList;
	Stack<AstarNode> childList;
	boolean[] check = new boolean[9];

	AStar() {
		startNode = new AstarNode();
		goalNode = new AstarNode();
		childList = new Stack<AstarNode>();
		Open = new AstarNode(-1, -1, -1);
		Close = new AstarNode(-99, -1, -1);
	}

	int computeGstar(AstarNode n) {
		int sum = 0;
		while (n.parent != null) {
			n = n.parent;
			sum += 1;
		}
		return sum;
	}

	int computeHstar() throws Exception {
		int h = 0;
		int i_x, i_y, j_x, j_y;
		for (int i = 0; i < goalNode.configuration.length; i++) {
			check[startNode.configuration[i]] = true;
			i_x = (i + 1) % 3;
			if (i_x == 0)
				i_x = 3;
			i_y = (int) Math.ceil((double) (i + 1) / 3);
			for (int j = 0; i < goalNode.configuration.length; j++) {
				if (startNode.configuration[i] == goalNode.configuration[j]) {
					j_x = (j + 1) % 3;
					if (j_x == 0)
						j_x = 3;
					j_y = (int) Math.ceil((double) (j + 1) / 3);
					int temp = Math.abs((j_y - i_y) + (j_x - i_x));
					// System.out.println(temp);
					h += temp;
					break;
				}
			}
		}
		if (!validConf())
			throw new Exception("The startNode has invalid configuration\n");
		return h;
	}

	boolean validConf() {
		for (boolean i : check) {
			if (!i)
				return false;
		}
		return true;
	}

	boolean isMatch(AstarNode n, AstarNode cmp) {
		return Arrays.equals(n.configuration, cmp.configuration);
	}

	boolean isGoal(AstarNode n) {
		return Arrays.equals(n.configuration, goalNode.configuration);
	}

	boolean checkAncestor(AstarNode n) {
		while (n.parent != null) {
			if (isMatch(n, n.parent))
				return true;
			n = n.parent;
		}
		return false;
	}

	void listInsert(AstarNode n) {
		AstarNode temp = Open;
		while (temp.next != null && temp.next.fStar < n.fStar)
			temp = temp.next;
		if (temp.fStar == n.fStar) {
			n.next = temp.next;
			temp.next = n;
		} else {
			n.next = temp.next;
			temp.next = n;
		}
	}

	AstarNode remove() {
		if (Open.next == null)
			return null;
		else {
			AstarNode n = Open.next;
			Open.next = Open.next.next;
			return n;
		}
	}

	AstarNode constructChildList(AstarNode n) throws Exception {

		int location = -1;
		for (int i = 0; i < n.configuration.length; i++)
			if (n.configuration[i] == 0) {
				location = i;
				break;
			}

		// 0 2 6 8 position is 0
		AstarNode c1 = new AstarNode();
		AstarNode c2 = new AstarNode();
		AstarNode c3 = new AstarNode();
		AstarNode c4 = new AstarNode();
		c1 = n.clone();
		c2 = n.clone();
		c3 = n.clone();
		c4 = n.clone();
		c1.configuration = n.configuration.clone();
		c2.configuration = n.configuration.clone();
		c3.configuration = n.configuration.clone();
		c4.configuration = n.configuration.clone();
		c1.next = null;
		c2.next = null;
		c3.next = null;
		c4.next = null;

		if (location == 0 || location == 2 || location == 6 || location == 8) {
			if (location == 0 || location == 2) { // side swap (y)
				int temp = n.configuration[location];
				c1.configuration[location] = c1.configuration[location + 3];
				c1.configuration[location + 3] = temp;
				if (location == 0) { // x swap
					c2.configuration[location] = c1.configuration[location + 1];
					c2.configuration[location + 1] = temp;
				}
				if (location == 2) { // x swap
					c2.configuration[location] = c2.configuration[location - 1];
					c2.configuration[location - 1] = temp;
				}
			} 
			else if (location == 6 || location == 8) {
				int temp = n.configuration[location];
				c1.configuration[location] = c1.configuration[location - 3];
				c1.configuration[location - 3] = temp;
				if (location == 6) {
					c2.configuration[location] = c2.configuration[location + 1];
					c2.configuration[location + 1] = temp;
				}
				if (location == 8) {
					c2.configuration[location] = c2.configuration[location - 1];
					c2.configuration[location - 1] = temp;
				}
			}
			if (checkAncestor(c1))
				c1 = null;
			else {
				c1.parent = n;
				c1.fStar = computeHstar() + computeGstar(c1);
				push(c1);
			}
			if (checkAncestor(c2))
				c2 = null;
			else {
				c2.parent = n;
				c2.fStar = computeHstar() + computeGstar(c2);
				push(c2);
			}

		}
		if (location % 2 == 1) { // all the side location but not corner and not mid.
			int temp = n.configuration[location];
			// swapping common
			c1.configuration[location] = c1.configuration[4];
			c1.configuration[4] = temp;

			if (location == 1 || location == 7) {
				c2.configuration[location] = c2.configuration[location - 1];
				c2.configuration[location - 1] = temp;
				c3.configuration[location] = c3.configuration[location + 1];
				c3.configuration[location + 1] = temp;
			}
			if (location == 3 || location == 5) {
				c2.configuration[location] = c2.configuration[location - 3];
				c2.configuration[location - 3] = temp;
				c3.configuration[location] = c3.configuration[location + 3];
				c3.configuration[location + 3] = temp;
			}
			if (checkAncestor(c1))
				c1 = null;
			else {
				c1.parent = n;
				c1.fStar = computeHstar() + computeGstar(c1);
				push(c1);
			}
			if (checkAncestor(c2))
				c2 = null;
			else {
				c2.parent = n;
				c2.fStar = computeHstar() + computeGstar(c2);
				push(c2);
			}
			if (checkAncestor(c3))
				c3 = null;
			else {
				c3.parent = n;
				c3.fStar = computeHstar() + computeGstar(c3);
				push(c3);
			}
		}
		if (location == 4) {
			int temp = n.configuration[location];
			c1.configuration[location] = c1.configuration[location - 1];
			c1.configuration[location - 1] = temp;
			c2.configuration[location] = c2.configuration[location + 1];
			c2.configuration[location + 1] = temp;
			c3.configuration[location] = c3.configuration[location + 3];
			c3.configuration[location + 3] = temp;
			c4.configuration[location] = c4.configuration[location - 3];
			c4.configuration[location - 3] = temp;
			if (checkAncestor(c1))
				c1 = null;
			else {
				c1.parent = n;
				c1.fStar = computeHstar() + computeGstar(c1);
				push(c1);
			}
			if (checkAncestor(c2))
				c2 = null;
			else {
				c2.parent = n;
				c2.fStar = computeHstar() + computeGstar(c2);
				push(c2);
			}
			if (checkAncestor(c3))
				c3 = null;
			else {
				c3.parent = n;
				c3.fStar = computeHstar() + computeGstar(c3);
				push(c3);
			}
			if (checkAncestor(c4))
				c4 = null;
			else {
				c4.parent = n;
				c4.fStar = computeHstar() + computeGstar(c4);
				push(c4);
			}
		}
		return n;
	}

	AstarNode pop() {
		AstarNode temp = cList;
		cList = cList.next;
		return temp;
	}

	void push(AstarNode n) {
		n.next = null;
		if (cList == null) {
			cList = n;
			return;
		} else {
			n.next = cList;
			cList = n;
		}
	}

	boolean listCheck(AstarNode list, AstarNode n) {
		AstarNode temp = list;
		while (temp.next != null) {
			if (isMatch(temp, n))
				return true;
			temp = temp.next;
		}
		return false;
	}

	void pushC(AstarNode n) {
		if (Close == null) {
			Close = n;
			return;
		}
		n.next = Close;
		Close = n;
	}

	void printList(AstarNode list, FileWriter out) throws IOException {
		int i = 0;
		String s = "";
		if (list == Close)
			out.write("This is Closed List: \n");
		else
			out.write("This is Open List: \n");
		list = list.next; // skipping dummy

		out.flush();
		while (list != null && i < 10) {
			s += "<" + String.valueOf(list.fStar) + "::";
			s += Arrays.toString(list.configuration).replace(',', ' ').replace("[", "").replace("]", "");
			if (list.parent != null)
				s += "::" + Arrays.toString(list.parent.configuration).replace(',', ' ').replace("[", "").replace("]",
						"");
			s += ">\n";
			out.write(s);
			out.flush();
			i += 1;
			list = list.next;
		}
	}

	void printSol(AstarNode n, FileWriter out) throws IOException {
		String s = "The Solution is: ";
		s += Arrays.toString(n.configuration);
		out.write(s);
		out.flush();
	}

}

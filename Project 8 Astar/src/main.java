
/*
 * Project 8 -- 8 Puzzle Problem using Graph algorithm
 */
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class main {
	public static void main(String args[]) throws Exception {
		File in1 = new File(args[0]);
		File in2 = new File(args[1]);
		File out = new File(args[2]);
		File out2 = new File(args[3]);
		Scanner inReader = new Scanner(in1);
		Scanner inReader2 = new Scanner(in2);
		FileWriter outW = new FileWriter(out);
		FileWriter out2W = new FileWriter(out2);
		int[] init = new int[9];
		int[] goal = new int[9];
		int i = 0;
		AStar test = new AStar();	
		AstarNode holder = new AstarNode();
		while (inReader.hasNextInt() && inReader2.hasNextInt()) {
			init[i] = inReader.nextInt();
			goal[i] = inReader2.nextInt();
			i += 1;
		}
		test.startNode.setConf(init);
		test.goalNode.setConf(goal);
		test.startNode.fStar = 0 + test.computeHstar();
		test.listInsert(test.startNode);
		int step = 1;
		do {
			AstarNode current = test.remove();
			if (test.isGoal(current)) {
				test.printSol(current, out2W);
				out2W.write("\nSolution Found at step: " + step);
				return;
			}
			test.constructChildList(current);
			do {
				AstarNode child = test.pop();
				if (!test.listCheck(test.Open, child) && !test.listCheck(test.Close, child)) {
					test.listInsert(child);
					child.parent = current;
				} 
				else if (test.listCheck(test.Open, child)) {
					AstarNode temp = test.Open.next;
					while (temp != null && test.isMatch(child, temp)) {
						temp = temp.next;
					}
					if (child.fStar < temp.fStar) {
						child.next = temp.next;
						temp = child;
						child.parent = current;
					}
				} 
				else if (test.listCheck(test.Close, child)) {
					AstarNode temp = test.Close.next;
					while (temp != null && test.isMatch(child, temp))
						temp = temp.next;
					if (child.fStar < temp.fStar) {
						child.next = temp.next;
						temp = child;
						child.parent = current;
					}
				}
			} while (test.cList != null);
			test.pushC(current);
			test.printList(test.Open, outW);
			test.printList(test.Close, outW);
			holder = current;
			System.out.println(Arrays.toString(holder.configuration));
			step += 1;
			System.out.println(step);
		} while (test.Open.next != null || test.isMatch(holder, test.goalNode));
		if (test.Open.next == null && !test.isMatch(test.goalNode, holder)) {
			outW.write("No Solution\n");
			outW.flush();
		}
		System.out.println("Goal\n" + Arrays.toString(goal));
		inReader.close();
		inReader2.close();
		outW.close();
		out2W.close();
		return;
	}
}

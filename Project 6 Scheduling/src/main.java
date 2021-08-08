
import java.io.*;
import java.util.Arrays;
import java.util.Scanner;

public class main {
	/**
	 * @param args
	 * @throws Exception
	 */
	public static void main(String args[]) throws Exception {
		Schedule test = new Schedule();
		File set_11 = new File(args[0]); // input1
		File set_12 = new File(args[1]); // input2
		File out_1 = new File(args[0].replaceAll(".txt", "output.txt"));
		File out_2 = new File(args[1].replaceAll(".txt", "output.txt"));
		out_1.createNewFile();
		out_2.createNewFile();
		FileWriter out_1writer = new FileWriter(out_1);
		FileWriter out_2writer = new FileWriter(out_2);
		Scanner reader_1 = new Scanner(set_11);
		Scanner reader_2 = new Scanner(set_12);
		int i1, i2;
		i1 = reader_1.nextInt();
		i2 = reader_2.nextInt();
		if (i2 <= 0)
			throw new Exception("Process number must be greater than 1\n");
		else if (i2 > i1)
			i2 = i1;
//		test.currentTime=0;
//		test.processUsed=0;
		test.numNodes = i1;
		test.numProcessor = 4; // Subjected to change.
		try {
			if (args[2].equals("u") || args[2].equals("unlimited")) {
				test.numProcessor = i1 + 2;
			}
			else if (args[2] != null) {
				test.numProcessor = Integer.parseInt(args[2]);
			} 

		} catch (Exception e) {
			System.out.println("Processor Number is not being input in the command, using default processor number\n");
		}
		test.adjMatrix = new int[test.numNodes + 1][test.numNodes + 1];
		test.OPEN = new Node();
		test.loadMatrix(set_11);
		test.loadJobTimeArr(set_12);
		test.setMatrix();
		test.PrintMatrix(out_2writer);
		while (!test.isEmpty() && test.currentTime < test.totalJobTime+1) {
			while (true) {
				int job = test.findOrphan();
				if (job > 0) {
					Node n = new Node(job, test.jobTimearr[job]);
					test.OpenInsert(n);
					System.out.println("inserted: "+ n.jobID);
					test.printOPEN(out_2writer);
				} else {
					// System.out.println("Job < 0");
					break;
				}
			}

			int onProcessor = test.getNextProcessor(test.currentTime);

			while (onProcessor > 0 && test.OPEN.next != null && test.processUsed <= test.numProcessor) {
//				if (onProcessor > 0) {
					//System.out.println(onProcessor);
					Node newJob = test.OPEN.next;
					System.out.println(newJob.jobID);
					test.OPEN.next = test.OPEN.next.next;
					test.putJobTable(onProcessor, test.currentTime, newJob.jobID, newJob.jobTime);

					test.processUsed += 1;
					onProcessor = test.getNextProcessor(test.currentTime);
//				}
			}
			test.printTable(out_1writer, test.currentTime);

			if (test.isCycle())
				throw new Exception("There is a cycle in the graph");
			test.currentTime+=1;
			int proc = 1;
			while (proc <= test.numProcessor) {
 				if (test.Table[proc][test.currentTime] <= 0 && test.Table[proc][test.currentTime - 1] > 0) {
					int jobID = test.Table[proc][test.currentTime - 1];
					test.deleteJobID(jobID);
				}
				test.PrintMatrix(out_2writer);
				proc+=1;
			}
		}

		System.out.println("****Debugging Purpose****");
		System.out.println(test.processUsed);
		System.out.println(Arrays.deepToString(test.adjMatrix));
		System.out.println(Arrays.deepToString(test.Table));
		System.out.println(Arrays.toString(test.jobTimearr));
	
		return;
	}
}
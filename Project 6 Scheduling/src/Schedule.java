import java.io.*;
import java.util.Scanner;

public class Schedule {
	int numNodes;
	int numProcessor;
	int processUsed;
	int currentTime;
	int totalJobTime;
	int jobTimearr[];
	int adjMatrix[][]; // numNodes + 1, numNodes+1
	int Table[][]; // numProc + 1, totalJobTime+1
	Node OPEN;

	Schedule() {
		numNodes = 0;
		numProcessor = 4; // Change your Processor Counts here or in driver
		processUsed = 0;
		currentTime = 0;
		totalJobTime = 0;
	}

	public void loadMatrix(File in) throws Exception {
		// Set the number of NumNodes and adjMatrix
		Scanner reader = new Scanner(in);
		reader.nextInt(); // Skip the first number
		while (reader.hasNextInt()) {
			int i = reader.nextInt();
			int j = reader.nextInt();
			adjMatrix[i][j] = 1;
			adjMatrix[i][i] = 1;
			adjMatrix[j][j] = 1;
		}
	}

	public int loadJobTimeArr(File in) throws Exception {
		jobTimearr = new int[numNodes + 1];
		Scanner reader = new Scanner(in);
		reader.nextInt();
		while (reader.hasNextInt()) {
			int i = reader.nextInt();
			int j = reader.nextInt();
			jobTimearr[i] = j;
			totalJobTime += j;

		}
		System.out.println("Total Time = " + totalJobTime);
		Table = new int[numProcessor + 1][totalJobTime + 1];
		return totalJobTime;
	}

	public void setMatrix() {
		// compute every column and store them at row 0
		for (int i = 1; i < numNodes + 1; i++) {
			int sum = 0;
			for (int j = 1; j < numNodes + 1; j++) {
				if (i == j) {
					continue;
				}
				sum += adjMatrix[j][i];
			}
			adjMatrix[0][i] = sum;
		}
		adjMatrix[0][0] = numNodes;
	}

	public void PrintMatrix(FileWriter out) throws Exception {
		for (int i = 0; i < numNodes + 1; i++) {
			for (int j = 0; j < numNodes + 1; j++) {
				out.write(String.valueOf(adjMatrix[i][j]));
			}
			out.write("\n");
			out.flush();
		}
		out.write("\n");
		out.flush();
	}

	public int findOrphan() {
		for (int i = 0; i < numNodes + 1; i++) {
			if (adjMatrix[0][i] == 0) {
				if (adjMatrix[i][i] == 1) {
					adjMatrix[i][i] = 2;
					return i;
				}
			}
		}
		return -1;
	}

	public void OpenInsert(Node n) {
		Node current = OPEN;
		while (current.next != null && adjMatrix[0][current.jobID] > adjMatrix[0][n.jobID])
			current = current.next;
		if (adjMatrix[0][current.jobID] == adjMatrix[0][n.jobID]) {
			n.next = current.next;
			current.next = n;
		} else {
			n.next = current.next;
			current.next = n;
		}
	}

	public void printOPEN(FileWriter out) throws Exception {
		Node current = OPEN;
		out.write("listHead-->");
		while (current.next != null) {
			out.write(String.valueOf(current.jobID));
			out.write(", " + current.next.jobID + "-->");
			out.flush();
			current = current.next;
		}
		out.write("END");
		out.write(System.lineSeparator());
		out.flush();
	}

	public int getNextProcessor(int time) {
		for (int i = 1; i <= numProcessor; i++)
			if (Table[i][time] == 0)
				return i;
		return -1;
	}

	public void putJobTable(int onProc, int currenTime, int jobI, int jobT) {
		int time = currenTime;
		int endTime = time + jobT;
		while (time < endTime) {
			Table[onProc][time] = jobI;
			time++;
		}

	}

	public void printTable(FileWriter out, int time) throws Exception {
		out.write("Processor Used:" + String.valueOf(processUsed) + "    Current Time:" + String.valueOf(time) + "\n");
		out.flush();
		out.write("       ");
		for (int i = 0; i <= time; i++)
			out.write(String.valueOf(i) + "   ");
		out.write(System.lineSeparator() + "_______________________________________\n");
		out.flush();
		for (int i = 1; i <= numProcessor; i++) {
			out.write("P(" + String.valueOf(i) + ")|");
			for (int j = 0; j <= time; j++) {

				if (Table[i][j] == 0) {
					out.write(" - |");
					out.flush();
				} else {
					out.write(' ' + String.valueOf(Table[i][j]) + " |");
					out.flush();
				}
				// out.write(" |");
				out.flush();

			}
			out.write(System.lineSeparator() + "_______________________________________\n");
			out.flush();
		}
	}

	public boolean isCycle() {
		if (OPEN.next == null)
			if (adjMatrix[0][0] != 0)
				if (processUsed == 0)
					return true;
		return false;
	}

	public boolean isEmpty() {
		return (adjMatrix[0][0] == 0);
	}

	public void deleteJobID(int ID) {
		System.out.println("deleted job "+ID);
		processUsed -= 1;
		adjMatrix[ID][ID] = 0;
		adjMatrix[0][0] -= 1;
		int j = 1;
		while (j < numNodes + 1) {
			if (adjMatrix[ID][j] > 0) {
				adjMatrix[0][j] -= 1;
				adjMatrix[ID][j] -= 1;
			}
			j++;
		}

	}
}


import java.io.*;
import java.util.Scanner;


public class main {
	public static void main(String[] args) throws Exception {
		Scanner Input = new Scanner(System.in);
		File sample = new File(args[0]);
		String DebugFileString = args[0].replaceAll(".txt", "")+"_DebugFile.txt";
		File DebugFile = new File(DebugFileString);
		FileWriter DebugFileWrite = new FileWriter(DebugFile);
		File Treeoutfile = new File(args[0].toString().replaceAll(".txt", "_treeoutput.txt"));
		Treeoutfile.createNewFile();
		FileWriter treeoutWriter = new FileWriter(Treeoutfile);
		HuffmanCoding test = new HuffmanCoding();
		test.computeCharCounts(sample, test.charCountArr);
		test.printCountArr(DebugFileWrite);
		test.constructHuffmanLList(test.charCountArr, DebugFileWrite);
		test.constructHuffmanBinTree(test.HuffmanLinkedList.listHead, DebugFileWrite);
		test.constructCharCode(test.HuffmanBinaryTree.root, "");
		test.HuffmanLinkedList.PrintList(test.HuffmanLinkedList.listHead, DebugFileWrite);
		treeoutWriter.append("Tree postorder traversal"+System.lineSeparator());
		treeoutWriter.flush();
		test.HuffmanBinaryTree.postOrderTraversal(test.HuffmanBinaryTree.root, treeoutWriter);
		treeoutWriter.append(System.lineSeparator()+"Tree inorder traversal"+System.lineSeparator());
		treeoutWriter.flush();
		test.HuffmanBinaryTree.inOrderTraversal(test.HuffmanBinaryTree.root, treeoutWriter);
		treeoutWriter.append(System.lineSeparator()+"Tree preorder traversal"+System.lineSeparator());
		treeoutWriter.flush();
		test.HuffmanBinaryTree.preOrderTraversal(test.HuffmanBinaryTree.root, treeoutWriter);
		test.UI();
		
		treeoutWriter.close();
		DebugFileWrite.close();
		System.out.println("End");
		return;
	}
}
